
#pragma once
#include "entities/enemies/Enemy.h"
#include <vector>

class GeneticAlgorithm {
public:
    GeneticAlgorithm(int populationSize, float mutationRate);

    void initializePopulation();
    void evolveGeneration();
    void printGenerationSummary(int generation) const;

    const std::vector<Enemy>& getPopulation() const;

private:
    int populationSize;
    float mutationRate;
    int nextId;

    std::vector<Enemy> population;

    Enemy generateRandomEnemy();
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
};
