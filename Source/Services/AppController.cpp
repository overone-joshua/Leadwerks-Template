#pragma once
#include "Leadwerks.h"
#include "AppController.hpp"

#include "../Common.hpp"
#include "../Utilities/Container.hpp"
#include "../Utilities/Macros.hpp"
#include "../Utilities/WindowHandle.hpp"
#include "../Utilities/ContextHandle.hpp"
#include "../Utilities/WorldHandle.hpp"
#include "../Utilities/CameraHandle.hpp"

const bool AppController::isFullScreen() const {
	return (bool)(m_pWindow->getInst()->FullScreen);
}

const std::string AppController::getAppName() const {
    return m_appName;
}

const Leadwerks::Vec2 AppController::screen_upperLeft() const {
	return Leadwerks::Vec2(m_pWindow->getInst()->GetX(), m_pWindow->getInst()->GetY());
}

const Leadwerks::Vec2 AppController::screen_lowerRight() const {
	return Leadwerks::Vec2(m_pWindow->getInst()->GetX() + m_pWindow->getInst()->GetWidth(), m_pWindow->getInst()->GetY() + m_pWindow->getInst()->GetHeight());
}

const int AppController::getWindowFlags (void) const {
    return m_windowFlags;
}

const int AppController::getRenderingContextFlags(void) const {
    return m_renderingContextFlags;
}

const Leadwerks::Window& AppController::getWindow() const {
    return (*m_pWindow->getInst());
}

const Leadwerks::Context& AppController::getContext() const {
    return (*m_pContext->getInst());
}

const Leadwerks::World& AppController::getWorld() const {
    return (*m_pWorld->getInst());
}

const Leadwerks::Camera& AppController::getCamera() const {
    return (*m_pCamera->getInst());
}

const bool AppController::CreateWindowAndContext(std::string name, unsigned nX, unsigned nY, unsigned nWidth, unsigned nHeight, int windowFlags, int contextFlags) {
    ReleaseWindowAndContext();

	m_windowFlags = windowFlags;
	m_renderingContextFlags = contextFlags;

    m_pWindow = new WindowHandle(Leadwerks::Window::Create(name, nX, nY, nWidth, nHeight, windowFlags));
    if (m_pWindow->getInst()== nullptr) { std::cout << "Window creation was unsuccessful. \n"; return false; }

    m_pContext = new ContextHandle(Leadwerks::Context::Create(m_pWindow->getInst(), contextFlags));
    if (m_pContext->getInst() == nullptr) { std::cout << "Rendering context creation was unsuccessful. \n"; return false; }

    return true;
}

const bool AppController::CreateWorld() {
    ReleaseWorld();

    m_pWorld = new WorldHandle(Leadwerks::World::Create());
    if (m_pWorld == nullptr) { std::cout << "World creation was unsuccessful. \n"; return false; }

    return true;
}

const bool AppController::CreateCamera() {
    ReleaseCamera();

    m_pCamera = new CameraHandle(Leadwerks::Camera::Create());
    if (m_pCamera == nullptr) { std::cout << "Camera creation was unsuccessful. \n"; return false; }

    return true;
}

void AppController::ReleaseApplication(void) {
	m_pApp->Shutdown();

	std::cout << "Application shutdown completed successfully. \n";
}

void AppController::ReleaseWindowAndContext(void) {
    SAFE_DELETE(m_pContext);
    SAFE_DELETE(m_pWindow);
}

void AppController::ReleaseWorld(void) {
    SAFE_DELETE(m_pWorld);
}

void AppController::ReleaseCamera(void) {
    SAFE_DELETE(m_pCamera);
}

AppController::AppController(App *pApp)
    : m_pWindow(nullptr), m_pContext(nullptr), m_pWorld(nullptr), m_pCamera(nullptr), m_pApp(pApp)
    , m_bExitAppThisFrame(false), m_windowFlags(0), m_renderingContextFlags(0), m_pContainer(nullptr) { }

AppController::~AppController(void) { Shutdown(); }

const bool AppController::Initialize(const std::string& appName, unsigned int ulX, unsigned int ulY, unsigned int nWidth, unsigned int nHeight, int windowFlags, int contextFlags) {

	m_appName = appName;

    if (!CreateWindowAndContext(appName, ulX, ulY, nWidth, nHeight, windowFlags, contextFlags)) { return false; }

    if (!CreateWorld() || !CreateCamera()) { return false; }

	// < Create our DI Container.
	m_pContainer = new Container();

	// < Inject our application dependencies.
	m_pContainer->Register<WindowHandle, WindowHandle>(m_pWindow);
	m_pContainer->Register<ContextHandle, ContextHandle>(m_pContext);
	m_pContainer->Register<WorldHandle, WorldHandle>(m_pWorld);
	m_pContainer->Register<CameraHandle, CameraHandle>(m_pCamera);

	gApp->Configure(m_pContainer);

	if (!gApp->Start()) { return false; }

    std::cout << "Application Controller initialization completed successfully. \n";

    return true;
}

void AppController::Shutdown() {
	ReleaseApplication();

	SAFE_DELETE(m_pContainer);

    std::cout << "Application controller shutdown completed successfully. \n";
}

void AppController::preUpdate() {
    if (m_pWindow->getInst()->Closed()) { m_bExitAppThisFrame = true; }

    m_pApp->preUpdate();
}

void AppController::postUpdate() {
    m_pApp->postUpdate();
}

bool AppController::Update(float dt) {
	preUpdate();

    if (m_bExitAppThisFrame) { return false; }

    m_bExitAppThisFrame = !m_pApp->Update(dt);

    if (m_pWorld != nullptr) { m_pWorld->getInst()->Update(); }

	postUpdate();

	return true;
}

void AppController::preRender() {
	m_pContext->getInst()->SetColor(0.45f, 0.110f, 0.105f, 1.0f);
    m_pContext->getInst()->Clear();

    m_pApp->preRender();
}

void AppController::postRender() {
    if (m_pWorld != nullptr) { m_pWorld->getInst()->Render(); }

    m_pApp->postRender();
}

void AppController::Render() {
	preRender();

    m_pApp->Render();

	postRender();
}

void AppController::preDraw() {
    m_pContext->getInst()->SetBlendMode(Leadwerks::Blend::Alpha);

    m_pApp->preDraw();
}

void AppController::postDraw() {
    m_pApp->postDraw();

    m_pContext->getInst()->SetBlendMode(Leadwerks::Blend::Solid);
    m_pContext->getInst()->Sync(false);
}

void AppController::Draw() {
	preDraw();

    m_pApp->Draw();

	postDraw();
}