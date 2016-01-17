#pragma once
#include "Leadwerks.h"

#include "AppCtrl.hpp"
#include "../App.h"

const bool AppCtrl::isFullScreen() const {
    return m_bFullScreen;
}

const Leadwerks::Vec2 AppCtrl::screen_upperLeft() const {

}

const Leadwerks::Vec2 AppCtrl::screen_lowerRight() const {

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

const bool AppCtrl::CreateWindowAndContext(std::string name, unsigned int nX, unsigned int nY, unsigned int nWidth,
                                           unsigned int nHeight, int windowFlags, int contextFlags) const { }

const bool AppCtrl::CreateWorld() const { }

const bool AppCtrl::CreateCamera() const { }

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
    , m_bExitAppThisFrame(false) {

}

AppCtrl::~AppCtrl(void) {
    SAFE_DELETE(m_pCamera);
    SAFE_DELETE(m_pWorld);
    SAFE_DELETE(m_pContext);
    SAFE_DELETE(m_pWindow);
}

const bool AppCtrl::Initialize(const std::string appName) const {

}

const bool AppCtrl::Shutdown() {

}

void AppCtrl::preUpdate() { }

void AppCtrl::postUpdate() { }

const bool AppCtrl::Update(float deltaTime) const { }

void AppCtrl::preRender() { }

void AppCtrl::postRender() { }

void AppCtrl::Render() { }

void AppCtrl::preDraw() { }

void AppCtrl::postDraw() { }

void AppCtrl::Draw() { }