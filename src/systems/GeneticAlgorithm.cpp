#include "GeneticAlgorithm.h"
#include <iostream>
#include <cstdlib>

GeneticAlgorithm::GeneticAlgorithm(int populationSize, float mutationRate) 
    : populationSize(populationSize), 
      mutationRate(mutationRate),
      nextId(1) {
    TraceLog(LOG_INFO, "GeneticAlgorithm initialized with population size %d and mutation rate %.2f", 
             populationSize, mutationRate);
}

// Destructor - Agregar esta implementación
GeneticAlgorithm::~GeneticAlgorithm() {
    // Limpiar recursos si es necesario
    TraceLog(LOG_INFO, "GeneticAlgorithm destroyed");
}


// Agregar nuevo método para manejar los vectores por tipo
void GeneticAlgorithm::setEnemyVectors(
    const std::vector<Enemy*>& ogres,
    const std::vector<Enemy*>& harpies,
    const std::vector<Enemy*>& mercenaries, 
    const std::vector<Enemy*>& darkElves) {
    
    // Guardar referencias a los vectores
    this->ogres = ogres;
    this->harpies = harpies;
    this->mercenaries = mercenaries;
    this->darkElves = darkElves;
    
    // Log para debugging
    TraceLog(LOG_INFO, "GA received vectors: %zu Ogres, %zu Harpies, %zu Mercenaries, %zu DarkElves", 
         ogres.size(), harpies.size(), mercenaries.size(), darkElves.size());
}

// Método auxiliar para calcular estadísticas promedio de una lista de enemigos
void GeneticAlgorithm::calculateAverageStats(
    const std::vector<Enemy*>& enemies, 
    float& avgLife, float& avgSpeed, 
    float& avgArrowRes, float& avgMagicRes, 
    float& avgArtilleryRes) const {
    
    if (enemies.empty()) {
        avgLife = avgSpeed = avgArrowRes = avgMagicRes = avgArtilleryRes = 0;
        return;
    }
    
    float sumLife = 0, sumSpeed = 0, sumArrowRes = 0, sumMagicRes = 0, sumArtilleryRes = 0;
    
    for (const auto& enemy : enemies) {
        sumLife += enemy->GetHealth();
        sumSpeed += enemy->GetSpeed();
        sumArrowRes += enemy->GetArrowResistance();
        sumMagicRes += enemy->GetMagicResistance();
        sumArtilleryRes += enemy->GetArtilleryResistance();
    }
    
    int count = enemies.size();
    avgLife = sumLife / count;
    avgSpeed = sumSpeed / count;
    avgArrowRes = sumArrowRes / count;
    avgMagicRes = sumMagicRes / count;
    avgArtilleryRes = sumArtilleryRes / count;
}

// Actualizar el método para mostrar estadísticas para cada tipo de enemigo
void GeneticAlgorithm::printGenerationSummary(int generation) const {
    std::cout << "\n===== Generación " << generation << " =====\n";
    
    // Procesar cada tipo de enemigo por separado
    auto processEnemyType = [this](const std::vector<Enemy*>& enemies, const char* typeName) {
        if (!enemies.empty()) {
            float avgLife, avgSpeed, avgArrowRes, avgMagicRes, avgArtilleryRes;
            calculateAverageStats(enemies, avgLife, avgSpeed, avgArrowRes, avgMagicRes, avgArtilleryRes);
            
            std::cout << "\n== " << typeName << " (Gen " << enemies[0]->GetGeneration() << ") ==\n";
            std::cout << "Cantidad: " << enemies.size() << "\n";
            std::cout << "Promedios: Vida=" << avgLife << ", Vel=" << avgSpeed 
                      << ", ResF=" << avgArrowRes << ", ResM=" << avgMagicRes 
                      << ", ResA=" << avgArtilleryRes << "\n";
                      
            int mutatedCount = 0;
            for (const auto& enemy : enemies) {
                if (enemy->IsMutated()) mutatedCount++;
            }
            std::cout << "Mutaciones: " << mutatedCount << " (" 
                      << (enemies.empty() ? 0 : (mutatedCount * 100.0 / enemies.size())) 
                      << "%)\n";
        }
    };
    
    processEnemyType(ogres, "Ogre");
    processEnemyType(harpies, "Harpy");
    processEnemyType(mercenaries, "Mercenary");
    processEnemyType(darkElves, "Dark Elf");
    
    std::cout << "\n===========================\n";
}