#ifndef ECONOMY_SYSTEM_H
#define ECONOMY_SYSTEM_H

class EconomySystem {
private:
    int balance; // Balance actual de la economía

public:
    EconomySystem(); // Constructor con balance inicial
    int GetBalance() const; // Obtener el balance actual
    void AddToBalance(int amount); // Agregar al balance
    bool DecreaseFromBalance(int amount); // Disminuir del balance (retorna false si no hay suficiente balance)
};

#endif // ECONOMY_SYSTEM_H