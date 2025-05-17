#include "EconomySystem.h"

EconomySystem::EconomySystem() : balance(1000) {} // Inicializa el balance con 200

int EconomySystem::GetBalance() const {
    return balance; // Retorna el balance actual
}

void EconomySystem::AddToBalance(int amount) {
    balance += amount; // Incrementa el balance
}

bool EconomySystem::DecreaseFromBalance(int amount) {
    if (balance >= amount) {
        balance -= amount; // Disminuye el balance si hay suficiente
        return true;
    }
    return false; // Retorna false si no hay suficiente balance
}