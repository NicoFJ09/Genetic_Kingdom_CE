#include "GeneticAlgorithm.h"
#include <iostream>
#include <cstdlib>
#include <random>  
#include <algorithm>

GeneticAlgorithm::GeneticAlgorithm(int populationSize, float mutationRate) 
    : populationSize(populationSize), 
      mutationRate(mutationRate) {
    TraceLog(LOG_INFO, "GeneticAlgorithm initialized with population size %d and mutation rate %.2f", 
             populationSize, mutationRate);
}

GeneticAlgorithm::~GeneticAlgorithm() {
    TraceLog(LOG_INFO, "GeneticAlgorithm destroyed");
}

// Método principal para procesar un tipo de enemigo
void GeneticAlgorithm::processEnemyType(const std::vector<Enemy*>& enemies, const std::string& typeName, bool updateMutationChance) {
    if (enemies.empty()) {
        TraceLog(LOG_WARNING, "No hay enemigos del tipo %s para procesar", typeName.c_str());
        return;
    }

    // Guardar referencia a estos enemigos
    currentEnemies = enemies;
    currentEnemyType = typeName;

    // Calcular estadísticas
    calculateAverageStats(enemies, avgLife, avgSpeed, avgArrowRes, avgMagicRes, avgArtilleryRes);

    TraceLog(LOG_INFO, "Procesando tipo %s: %zu enemigos, generación %d", 
             typeName.c_str(), enemies.size(), enemies[0]->GetGeneration());

    // Incrementar la probabilidad de mutación SOLO si se solicita explícitamente
    // (ahora se incrementa centralizadamente en CreateWaveEnemies)
    if (updateMutationChance) {
        updateMutationChanceForType(typeName);
    }
}

// Método para evolucionar la población actual
void GeneticAlgorithm::evolveCurrentType() {
    if (currentEnemies.empty()) {
        TraceLog(LOG_WARNING, "No hay enemigos para evolucionar");
        return;
    }
    
    // Limpiar solo los genes del tipo actual
    nextGenGenes.clear();
    
    // 1. Selección: Identificar los mejores individuos
    std::vector<Enemy*> parents = selectParents();
    
    if (parents.size() < 2) {
        TraceLog(LOG_WARNING, "No hay suficientes padres para la evolución, usando selección aleatoria");
        // Usar algunos enemigos aleatorios como respaldo
        int needed = 2 - static_cast<int>(parents.size());
        for (int i = 0; i < needed && i < static_cast<int>(currentEnemies.size()); i++) {
            parents.push_back(currentEnemies[i]);
        }
    }
    
    // 2. Cruce y mutación: Crear la próxima generación
    // Usar un número aleatorio entre 5 y 15 para determinar el tamaño de la población
    int targetPopSize = GetRandomValue(5, 15); // Aleatorio entre 5 y 15 por tipo
    
    TraceLog(LOG_INFO, "Generando %d individuos para la próxima generación de %s", 
             targetPopSize, currentEnemyType.c_str());
    
    for (int i = 0; i < targetPopSize; i++) {
        // Seleccionar dos padres aleatorios
        int parent1Idx = GetRandomValue(0, parents.size() - 1);
        int parent2Idx = GetRandomValue(0, parents.size() - 1);
        
        // Asegurarse de que son diferentes (si es posible)
        if (parents.size() > 1) {
            while (parent2Idx == parent1Idx) {
                parent2Idx = GetRandomValue(0, parents.size() - 1);
            }
        }
        
        // Cruzar los padres
        EnemyGenes offspring = crossover(parents[parent1Idx], parents[parent2Idx]);
        
        // Aplicar mutación
        bool wasMutated = mutate(offspring);
        
        if (wasMutated) {
            TraceLog(LOG_INFO, "¡%s %d MUTADO! Prob=%d%%, Vida=%.1f, Vel=%.1f, ResF=%.1f, ResM=%.1f, ResA=%.1f",
                     currentEnemyType.c_str(), i, offspring.mutationChance, offspring.health, 
                     offspring.speed, offspring.arrowResistance, offspring.magicResistance,
                     offspring.artilleryResistance);
        }
        
        // Guardar para la próxima generación
        nextGenGenes.push_back(offspring);
    }
    
    // Almacenar genes en el mapa por tipo
    nextGenGenesByType[currentEnemyType] = nextGenGenes;
    
    TraceLog(LOG_INFO, "Evolucionado tipo %s: %zu padres seleccionados, %zu genes para próxima generación", 
             currentEnemyType.c_str(), parents.size(), nextGenGenes.size());
}

// Método para obtener los genes de la próxima generación por tipo
std::vector<EnemyGenes> GeneticAlgorithm::getNextGenGenes() const {
    std::vector<EnemyGenes> result;
    
    // Comprobar si hay genes específicos para este tipo
    auto it = nextGenGenesByType.find(currentEnemyType);
    if (it != nextGenGenesByType.end()) {
        result = it->second;
    } else {
        // Si no hay genes específicos, devolver vector vacío
        return result;
    }
    
    // Ordenar los genes por fitness (de mayor a menor)
    std::sort(result.begin(), result.end(), [this](const EnemyGenes& a, const EnemyGenes& b) {
        return calculateFitness(a) > calculateFitness(b);
    });
    
    // Mostrar información de fitness para depuración
    TraceLog(LOG_INFO, "Genes ordenados por fitness para %s:", currentEnemyType.c_str());
    for (size_t i = 0; i < result.size() && i < 3; i++) {  // Mostrar los 3 mejores
        float fitness = calculateFitness(result[i]);
        TraceLog(LOG_INFO, "[%zu] Fitness: %.2f - Vida=%.1f, Vel=%.1f", 
                 i, fitness, result[i].health, result[i].speed);
    }
    
    return result;
}

// Método para imprimir estadísticas
void GeneticAlgorithm::printTypeSummary(int generation) const {
    if (currentEnemies.empty()) {
        std::cout << "\n== " << currentEnemyType << " (No hay datos disponibles) ==\n";
        return;
    }
    
    std::cout << "\n===== Generación " << generation << " =====\n";
    std::cout << "\n== " << currentEnemyType << " (Gen " << currentEnemies[0]->GetGeneration() << ") ==\n";
    std::cout << "Cantidad: " << currentEnemies.size() << "\n";
    std::cout << "Promedios: Vida=" << avgLife << ", Vel=" << avgSpeed 
              << ", ResF=" << avgArrowRes << ", ResM=" << avgMagicRes 
              << ", ResA=" << avgArtilleryRes << "\n";
              
    // Calcular la probabilidad de mutación promedio
    int totalMutationChance = 0;
    int mutatedCount = 0;
    
    for (const auto& enemy : currentEnemies) {
        totalMutationChance += enemy->GetMutationChance();
        if (enemy->IsMutated()) mutatedCount++;
    }
    
    float avgMutationChance = currentEnemies.empty() ? 0 : (float)totalMutationChance / currentEnemies.size();
    
    std::cout << "Prob. mutación promedio: " << avgMutationChance << "%\n";
    std::cout << "Mutaciones: " << mutatedCount << " (" 
              << (currentEnemies.empty() ? 0 : (mutatedCount * 100.0f / currentEnemies.size())) 
              << "%)\n";
              
    std::cout << "\n===========================\n";
}

float GeneticAlgorithm::calculateFitness(const EnemyGenes& genes) const {
    // Promedio ponderado simple: cada atributo tiene un peso
    const float healthWeight = 1.0f;
    const float speedWeight = 1.0f;
    const float arrowResWeight = 0.5f;
    const float magicResWeight = 0.5f;
    const float artilleryResWeight = 0.5f;
    
    // Calcular suma ponderada
    float fitnessValue = (genes.health * healthWeight + 
                          genes.speed * speedWeight + 
                          genes.arrowResistance * arrowResWeight +
                          genes.magicResistance * magicResWeight +
                          genes.artilleryResistance * artilleryResWeight) / 
                         (healthWeight + speedWeight + arrowResWeight + magicResWeight + artilleryResWeight);
    
    return fitnessValue;
}

// Método para calcular estadísticas promedio
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

// Método para contar atributos por encima del promedio
int GeneticAlgorithm::countAttributesAbove(const Enemy& e, float avgLife, float avgSpeed, 
                                          float avgArrowRes, float avgMagicRes, 
                                          float avgArtilleryRes) const {
    int count = 0;
    if (e.GetHealth() > avgLife) count++;
    if (e.GetSpeed() > avgSpeed) count++;
    if (e.GetArrowResistance() > avgArrowRes) count++;
    if (e.GetMagicResistance() > avgMagicRes) count++;
    if (e.GetArtilleryResistance() > avgArtilleryRes) count++;
    return count;
}

// Método para seleccionar padres
std::vector<Enemy*> GeneticAlgorithm::selectParents() {
    std::vector<Enemy*> selectedParents;
    
    // Seleccionar enemigos con al menos 2 atributos por encima del promedio
    for (auto enemy : currentEnemies) {
        // Verificar si está vivo o al menos tiene un porcentaje de vida bueno
        if (enemy->GetHealth() > 0) {
            int attributes = countAttributesAbove(*enemy, avgLife, avgSpeed, avgArrowRes, avgMagicRes, avgArtilleryRes);
            if (attributes >= 2) {
                selectedParents.push_back(enemy);
            }
        }
    }
    
    // Si no hay suficientes, incluir algunos al azar
    if (selectedParents.size() < 2 && currentEnemies.size() >= 2) {
        // Crear un vector con índices aleatorios
        std::vector<int> indices;
        for (int i = 0; i < static_cast<int>(currentEnemies.size()); i++) {
            indices.push_back(i);
        }
        
        // Mezclar los índices
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(indices.begin(), indices.end(), g);
        
        // Añadir hasta tener al menos 2 padres
        for (int i = 0; i < static_cast<int>(indices.size()) && selectedParents.size() < 2; i++) {
            Enemy* enemy = currentEnemies[indices[i]];
            if (std::find(selectedParents.begin(), selectedParents.end(), enemy) == selectedParents.end()) {
                selectedParents.push_back(enemy);
            }
        }
    }
    
    TraceLog(LOG_INFO, "Seleccionados %zu padres de %zu candidatos", 
             selectedParents.size(), currentEnemies.size());
    
    return selectedParents;
}

// Método para cruzar dos padres
EnemyGenes GeneticAlgorithm::crossover(const Enemy* parent1, const Enemy* parent2) {
    EnemyGenes offspring;
    
    // Cruzar atributos (50% de cada padre)
    offspring.health = (GetRandomValue(0, 1) == 0) ? parent1->GetHealth() : parent2->GetHealth();
    offspring.speed = (GetRandomValue(0, 1) == 0) ? parent1->GetSpeed() : parent2->GetSpeed();
    offspring.arrowResistance = (GetRandomValue(0, 1) == 0) ? parent1->GetArrowResistance() : parent2->GetArrowResistance();
    offspring.magicResistance = (GetRandomValue(0, 1) == 0) ? parent1->GetMagicResistance() : parent2->GetMagicResistance();
    offspring.artilleryResistance = (GetRandomValue(0, 1) == 0) ? parent1->GetArtilleryResistance() : parent2->GetArtilleryResistance();
    
    // Usar la probabilidad de mutación para el tipo actual (ya está actualizada por processEnemyType)
    int typeMutationChance = getMutationChanceForType(currentEnemyType);
    offspring.mutationChance = typeMutationChance;
    
    TraceLog(LOG_INFO, "Cruce para %s: Probabilidad mutación=%d%%", 
             currentEnemyType.c_str(), typeMutationChance);
    
    offspring.mutated = false;  // Inicialmente no está mutado
    
    return offspring;
}

// Nuevo método para obtener la probabilidad de mutación por tipo
int GeneticAlgorithm::getMutationChanceForType(const std::string& typeName) {
    // Solo inicializar si no existe
    if (mutationChanceByType.find(typeName) == mutationChanceByType.end()) {
        mutationChanceByType[typeName] = 5;
    }
    return mutationChanceByType[typeName];
}

// Nuevo método para actualizar la probabilidad de mutación por tipo
void GeneticAlgorithm::updateMutationChanceForType(const std::string& typeName) {
    int currentChance = getMutationChanceForType(typeName);
    
    // Definir incrementos basados en el tipo de enemigo
    int baseIncrease;
    if (typeName == "Ogre") {
        // Incremento menor para Ogros porque aparecen desde la primera oleada
        baseIncrease = GetRandomValue(3, 9);
    } else if (typeName == "Dark Elf") {
        // Incremento medio para Elfos Oscuros (aparecen en oleada 2)
        baseIncrease = GetRandomValue(6, 12);
    } else if (typeName == "Mercenary") {
        // Incremento mayor para Mercenarios (aparecen en oleada 3)
        baseIncrease = GetRandomValue(9, 15);
    } else if (typeName == "Harpy") {
        // Incremento mayor para Arpías (aparecen en oleada 4)
        baseIncrease = GetRandomValue(9, 18);
    } else {
        // Para cualquier otro tipo, incremento default
        baseIncrease = GetRandomValue(2, 5);
    }
    
    int newChance = std::min(100, currentChance + baseIncrease);
    
    mutationChanceByType[typeName] = newChance;
    
    TraceLog(LOG_INFO, "Probabilidad de mutación para %s actualizada: %d%% -> %d%% (+%d%%)",
             typeName.c_str(), currentChance, newChance, baseIncrease);
}
// Método para mutar genes
bool GeneticAlgorithm::mutate(EnemyGenes& genes) {
    bool wasMutated = false;
    
    // Usar la probabilidad de mutación almacenada en los genes
    int mutationProbability = genes.mutationChance;
    
    // Aplicar mutación a cada atributo según la probabilidad de mutación
    if (GetRandomValue(1, 100) <= mutationProbability) {
        float mod = randFloat(-0.2f, 0.3f);
        genes.health *= (1.0f + mod);  // -20% a +30%
        TraceLog(LOG_INFO, "Mutación de salud: %.1f%% (%.1f -> %.1f)", 
                 mod * 100.0f, genes.health / (1.0f + mod), genes.health);
        wasMutated = true;
    }
    
    if (GetRandomValue(1, 100) <= mutationProbability) {
        float mod = randFloat(-0.2f, 0.3f);
        genes.speed *= (1.0f + mod);
        TraceLog(LOG_INFO, "Mutación de velocidad: %.1f%% (%.1f -> %.1f)", 
                 mod * 100.0f, genes.speed / (1.0f + mod), genes.speed);
        wasMutated = true;
    }
    
    if (GetRandomValue(1, 100) <= mutationProbability) {
        float mod = randFloat(-0.2f, 0.3f);
        genes.arrowResistance *= (1.0f + mod);
        TraceLog(LOG_INFO, "Mutación de res. flechas: %.1f%% (%.1f -> %.1f)", 
                 mod * 100.0f, genes.arrowResistance / (1.0f + mod), genes.arrowResistance);
        wasMutated = true;
    }
    
    if (GetRandomValue(1, 100) <= mutationProbability) {
        float mod = randFloat(-0.2f, 0.3f);
        genes.magicResistance *= (1.0f + mod);
        TraceLog(LOG_INFO, "Mutación de res. magia: %.1f%% (%.1f -> %.1f)", 
                 mod * 100.0f, genes.magicResistance / (1.0f + mod), genes.magicResistance);
        wasMutated = true;
    }
    
    if (GetRandomValue(1, 100) <= mutationProbability) {
        float mod = randFloat(-0.2f, 0.3f);
        genes.artilleryResistance *= (1.0f + mod);
        TraceLog(LOG_INFO, "Mutación de res. artillería: %.1f%% (%.1f -> %.1f)", 
                 mod * 100.0f, genes.artilleryResistance / (1.0f + mod), genes.artilleryResistance);
        wasMutated = true;
    }
    
    // Actualizar flag de mutación
    genes.mutated = wasMutated;
    
    if (wasMutated) {
        TraceLog(LOG_INFO, "¡Mutación aplicada con probabilidad %d%%!", mutationProbability);
    }
    
    return wasMutated;
}

// Método para generar un número aleatorio flotante
float GeneticAlgorithm::randFloat(float min, float max) const {
    return min + (static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f) * (max - min);
}

// Método para obtener un índice aleatorio
int GeneticAlgorithm::randomIndex(int max) const {
    if (max <= 0) return 0;
    return GetRandomValue(0, max - 1);
}