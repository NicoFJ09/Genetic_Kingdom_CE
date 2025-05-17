#pragma once
#include "../entities/enemies/Enemy.h"
#include <vector>
#include <string>
#include <map>

// Estructura para almacenar genes de enemigos para la próxima generación
struct EnemyGenes {
    float health;
    float speed;
    float arrowResistance;
    float magicResistance;
    float artilleryResistance;
    bool mutated;
    int mutationChance;
};

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, float mutationRate);
    ~GeneticAlgorithm();

    // Cambia la declaración del método processEnemyType:
    void processEnemyType(const std::vector<Enemy*>& enemies, const std::string& typeName, bool updateMutationChance = true);
    void updateMutationChanceForType(const std::string& typeName);
    // Evolucionar la población actual
    void evolveCurrentType();
    
    // Obtener genes para la próxima generación
    std::vector<EnemyGenes> getNextGenGenes() const;
    
    // Imprimir estadísticas para el tipo actual
    void printTypeSummary(int generation) const;
    int getMutationChanceForType(const std::string& typeName);

private:
    int populationSize;
    float mutationRate;
    
    // El vector de enemigos actual que estamos procesando
    std::vector<Enemy*> currentEnemies;
    std::string currentEnemyType;
    
    // Almacenamiento para genes de la próxima generación
    std::vector<EnemyGenes> nextGenGenes;
    
    // Variables para estadísticas
    float avgLife;
    float avgSpeed;
    float avgArrowRes;
    float avgMagicRes;
    float avgArtilleryRes;
    
    // Métodos auxiliares
    void calculateAverageStats(
        const std::vector<Enemy*>& enemies, 
        float& avgLife, float& avgSpeed, 
        float& avgArrowRes, float& avgMagicRes, 
        float& avgArtilleryRes) const;
    
    int countAttributesAbove(const Enemy& e, float avgLife, float avgSpeed, 
                            float avgArrowRes, float avgMagicRes, float avgArtilleryRes) const;
    
    // Métodos para el algoritmo genético
    std::vector<Enemy*> selectParents();
    EnemyGenes crossover(const Enemy* parent1, const Enemy* parent2);
    bool mutate(EnemyGenes& genes);
    std::map<std::string, std::vector<EnemyGenes>> nextGenGenesByType;
    std::map<std::string, int> mutationChanceByType;
    float randFloat(float min, float max) const;
    int randomIndex(int max) const;

    // Nuevos métodos para gestionar la probabilidad de mutación
    float calculateFitness(const EnemyGenes& genes) const;

};