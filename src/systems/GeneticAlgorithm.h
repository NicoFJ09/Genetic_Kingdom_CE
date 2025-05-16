#pragma once
#include "../entities/enemies/Enemy.h"
#include <vector>
#include <string>

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, float mutationRate);
    ~GeneticAlgorithm();

    // Métodos originales (mantener para compatibilidad)
    void setPopulation(const std::vector<Enemy>& enemies); 
    void evolveGeneration();
    const std::vector<Enemy>& getPopulation() const;

    // Nuevos métodos para trabajar con vectores separados por tipo
    void setEnemyVectors(
        const std::vector<Enemy*>& ogres,
        const std::vector<Enemy*>& harpies,
        const std::vector<Enemy*>& mercenaries, 
        const std::vector<Enemy*>& darkElves
    );
    
    // Método para obtener estadísticas y resumen
    void printGenerationSummary(int generation) const;

private:
    int populationSize;
    float mutationRate;
    int nextId;

    // Vector general (mantener para compatibilidad)
    std::vector<Enemy> population;
    
    // Vectores específicos por tipo (punteros a los enemigos actuales)
    std::vector<Enemy*> ogres;
    std::vector<Enemy*> harpies;
    std::vector<Enemy*> mercenaries;
    std::vector<Enemy*> darkElves;

    // Métodos de utilidad existentes
    float calculateAverageLife() const;
    float calculateAverageSpeed() const;
    float calculateAverageArrowRes() const;
    float calculateAverageMagicRes() const;
    float calculateAverageArtilleryRes() const;
    int countAttributesAbove(const Enemy& e, float avgLife, float avgSpeed, float avgArrowRes, float avgMagicRes, float avgArtilleryRes) const;
    std::vector<Enemy> selectParents(float avgLife, float avgSpeed, float avgArrowRes, float avgMagicRes, float avgArtilleryRes);
    Enemy crossover(const Enemy& p1, const Enemy& p2);
    void mutate(Enemy& e);
    float randFloat(float min, float max);
    int randomIndex(int max);
    
    // Nuevos métodos auxiliares
    void calculateAverageStats(const std::vector<Enemy*>& enemies, float& avgLife, float& avgSpeed, 
                              float& avgArrowRes, float& avgMagicRes, float& avgArtilleryRes) const;
};