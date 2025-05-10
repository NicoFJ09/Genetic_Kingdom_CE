#include "ScreenManager.h"

ScreenManager::ScreenManager() : currentScreen(nullptr) {}

ScreenManager::~ScreenManager() {
    // Liberar la pantalla actual si es necesario
    if (currentScreen) {
        delete currentScreen;
    }
}

void ScreenManager::SwitchToScreen(Screen* newScreen) {
    // Liberar la pantalla actual antes de cambiar
    if (currentScreen) {
        delete currentScreen;
    }
    currentScreen = newScreen;
}

void ScreenManager::Update() {
    if (currentScreen) {
        currentScreen->Update();
    }
}

void ScreenManager::Draw() {
    if (currentScreen) {
        currentScreen->Draw();
    }
}