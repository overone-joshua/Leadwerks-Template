#pragma once
#include "Leadwerks.h"
#include "../Common.hpp"
#include "AppCtrl.hpp"


const bool AppCtrl::isFullScreen() const {
    return m_bFullScreen;
}

const std::string AppCtrl::getAppName() const {
    return m_appName;
}

const Leadwerks::Vec2 AppCtrl::screen_upperLeft() const {
    return m_vUpperLeft;
}

const Leadwerks::Vec2 AppCtrl::screen_lowerRight() const {
    return m_vLowerRight;
}

const int AppCtrl::getWindowFlags (void) const {
    return m_windowFlags;
}

const int AppCtrl::getRenderingContextFlags(void) const {
    return m_renderingContextFlags;
}

const Leadwerks::Window& AppCtrl::getWindow() const {
    return (*m_pWindow);
}

const Leadwerks::Context& AppCtrl::getContext() const {
    return (*m_pContext);
}

const Leadwerks::World& AppCtrl::getWorld() const {
    return (*m_pWorld);
}

const Leadwerks::Camera& AppCtrl::getCamera() const {
    return (*m_pCamera);
}

const bool AppCtrl::CreateWindowAndContext(std::string name, unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, int windowFlags, int contextFlags) {
    ReleaseWindowAndContext();

    int x = m_vUpperLeft.x;
    int y = m_vUpperLeft.y;
    int width = m_vLowerRight.x - x;
    int height = m_vLowerRight.y - y;

    m_pWindow = Leadwerks::Window::Create(m_appName, x, y, width, height, windowFlags);
    if (m_pWindow == nullptr) { std::cout << "Window creation was unsuccessful. \n"; return false; }

    m_pContext = Leadwerks::Context::Create(m_pWindow, contextFlags);
    if (m_pContext == nullptr) { std::cout << "Rendering context creation was unsuccessful. \n"; return false; }

    return true;
}

const bool AppCtrl::CreateWorld() {
    ReleaseWorld();

    m_pWorld = Leadwerks::World::Create();
    if (m_pWorld == nullptr) { std::cout << "World creation was unsuccessful. \n"; return false; }

    return true;
}

const bool AppCtrl::CreateCamera() {
    ReleaseCamera();

    m_pCamera = Leadwerks::Camera::Create();
    if (m_pCamera == nullptr) { std::cout << "Camera creation was unsuccessful. \n"; return false; }

    return true;
}

void AppCtrl::ReleaseApplication(void) {
	SAFE_DELETE(m_pApp);

	std::cout << "Application shutdown completed successfully. \n";
}

void AppCtrl::ReleaseWindowAndContext(void) {
    SAFE_RELEASE(m_pContext);
    SAFE_RELEASE(m_pWindow);
}

void AppCtrl::ReleaseWorld(void) {
    SAFE_RELEASE(m_pWorld);
}

void AppCtrl::ReleaseCamera(void) {
    SAFE_RELEASE(m_pCamera);
}

AppCtrl::AppCtrl(App *pApp)
    : m_pWindow(nullptr), m_pContext(nullptr), m_pWorld(nullptr), m_pCamera(nullptr), m_pApp(pApp), m_bFullScreen(false)
    , m_bExitAppThisFrame(false), m_windowFlags(0), m_renderingContextFlags(0), m_vUpperLeft(0, 0)
    , m_vLowerRight(1024, 768) {

}

AppCtrl::~AppCtrl(void) {
    SAFE_DELETE(m_pCamera);
    SAFE_DELETE(m_pWorld);
    SAFE_DELETE(m_pContext);
    SAFE_DELETE(m_pWindow);
}

const bool AppCtrl::Initialize(const std::string appName, unsigned int ulX, unsigned int ulY, unsigned int nWidth,
                                           unsigned int nHeight, int windowFlags, int contextFlags) {
    if (!CreateWindowAndContext(appName, ulX, ulY, nWidth, nHeight, windowFlags, contextFlags)) { return false; }

    if (!CreateWorld() || !CreateCamera()) { return false; }

    std::cout << "Application Controller initialization completed successfully. \n";

    return true;
}

void AppCtrl::Shutdown() {
	ReleaseApplication();
	
	ReleaseCamera();
    ReleaseWorld();
    ReleaseWindowAndContext();

    std::cout << "Application controller shutdown completed successfully. \n";    
}

void AppCtrl::preUpdate() {
    if (m_pWindow->Closed()) { m_bExitAppThisFrame = true; }

    m_pApp->preUpdate();
}

void AppCtrl::postUpdate() {
    m_pApp->postUpdate();
}

bool AppCtrl::Update(float dt) {
	preUpdate();

    if (m_bExitAppThisFrame) { return false; }

    m_bExitAppThisFrame = !m_pApp->Update(dt);

    if (m_pWorld != nullptr) { m_pWorld->Update(); }

	postUpdate();

	return true;
}

void AppCtrl::preRender() {
    m_pContext->SetColor(0.0f, 0.0f, 255.0f, 1.0f);
    m_pContext->Clear();

    m_pApp->preRender();
}

void AppCtrl::postRender() {
    if (m_pWorld != nullptr) { m_pWorld->Render(); }

    m_pApp->postRender();
}

void AppCtrl::Render() {
	preRender();

    m_pApp->Render();

	postRender();
}

void AppCtrl::preDraw() {
    m_pContext->SetBlendMode(Leadwerks::Blend::Alpha);

    m_pApp->preDraw();
}

void AppCtrl::postDraw() {
    m_pApp->postDraw();

    m_pContext->SetBlendMode(Leadwerks::Blend::Solid);
    m_pContext->Sync(false);
}

void AppCtrl::Draw() {
	preDraw();

    m_pApp->Draw();

	postDraw();
}