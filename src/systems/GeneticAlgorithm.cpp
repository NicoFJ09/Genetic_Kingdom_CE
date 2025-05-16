#include "GeneticAlgorithm.h"
#include <iostream>
#include <cstdlib>

GeneticAlgorithm::GeneticAlgorithm(int populationSize, float mutationRate)
    : populationSize(populationSize), mutationRate(mutationRate), nextId(0) {}

void GeneticAlgorithm::setPopulation(const std::vector<Enemy>& enemies) {
    population = enemies;
    for (auto& e : population) {
        e.id = nextId++;
    }
}

void GeneticAlgorithm::evolveGeneration() {
    float avgLife = calculateAverageLife();
    float avgSpeed = calculateAverageSpeed();
    float avgArrowRes = calculateAverageArrowRes();
    float avgMagicRes = calculateAverageMagicRes();
    float avgArtilleryRes = calculateAverageArtilleryRes();

    std::vector<Enemy> parents = selectParents(avgLife, avgSpeed, avgArrowRes, avgMagicRes, avgArtilleryRes);

    std::vector<Enemy> nextGeneration;
    while (nextGeneration.size() < populationSize) {
        Enemy& parent1 = parents[randomIndex(parents.size())];
        Enemy& parent2 = parents[randomIndex(parents.size())];

        Enemy child = crossover(parent1, parent2);
        mutate(child);
        child.id = nextId++;
        nextGeneration.push_back(child);
    }

    population = nextGeneration;
}

const std::vector<Enemy>& GeneticAlgorithm::getPopulation() const {
    return population;
}

void GeneticAlgorithm::printGenerationSummary(int generation) const {
    std::cout << "\nGeneración " << generation << ":\n";
    for (const auto& e : population) {
        std::cout << "ID: " << e.id << " Vida: " << e.life << " Vel: " << e.speed
                  << " ResF: " << e.arrowResistance << " ResM: " << e.magicResistance
                  << " ResA: " << e.artilleryResistance << "\n";
    }
}

float GeneticAlgorithm::calculateAverageLife() const {
    float sum = 0.0f;
    for (const auto& e : population) sum += e.life;
    return sum / population.size();
}

float GeneticAlgorithm::calculateAverageSpeed() const {
    float sum = 0.0f;
    for (const auto& e : population) sum += e.speed;
    return sum / population.size();
}

float GeneticAlgorithm::calculateAverageArrowRes() const {
    float sum = 0.0f;
    for (const auto& e : population) sum += e.arrowResistance;
    return sum / population.size();
}

float GeneticAlgorithm::calculateAverageMagicRes() const {
    float sum = 0.0f;
    for (const auto& e : population) sum += e.magicResistance;
    return sum / population.size();
}

float GeneticAlgorithm::calculateAverageArtilleryRes() const {
    float sum = 0.0f;
    for (const auto& e : population) sum += e.artilleryResistance;
    return sum / population.size();
}

int GeneticAlgorithm::countAttributesAbove(const Enemy& e, float avgLife, float avgSpeed, float avgArrowRes, float avgMagicRes, float avgArtilleryRes) const {
    int count = 0;
    if (e.life > avgLife) count++;
    if (e.speed > avgSpeed) count++;
    if (e.arrowResistance > avgArrowRes) count++;
    if (e.magicResistance > avgMagicRes) count++;
    if (e.artilleryResistance > avgArtilleryRes) count++;
    return count;
}

std::vector<Enemy> GeneticAlgorithm::selectParents(float avgLife, float avgSpeed, float avgArrowRes, float avgMagicRes, float avgArtilleryRes) {
    std::vector<Enemy> parents;
    for (const auto& e : population) {
        if (countAttributesAbove(e, avgLife, avgSpeed, avgArrowRes, avgMagicRes, avgArtilleryRes) >= 2) {
            parents.push_back(e);
        }
    }
    if (parents.empty()) parents = population;
    return parents;
}

Enemy GeneticAlgorithm::crossover(const Enemy& p1, const Enemy& p2) {
    return Enemy(
        p1.type,
        (p1.life + p2.life) / 2.0f,
        (p1.speed + p2.speed) / 2.0f,
        (p1.arrowResistance + p2.arrowResistance) / 2.0f,
        (p1.magicResistance + p2.magicResistance) / 2.0f,
        (p1.artilleryResistance + p2.artilleryResistance) / 2.0f
    );
}

void GeneticAlgorithm::mutate(Enemy& e) {
    if (randFloat(0.0f, 1.0f) < mutationRate) {
        int numAttributes = (rand() % 2) + 1;
        for (int i = 0; i < numAttributes; ++i) {
            int attr = rand() % 5;
            switch (attr) {
                case 0: e.life *= 1.5f; break;
                case 1: e.speed *= 1.5f; break;
                case 2: e.arrowResistance *= 1.5f; break;
                case 3: e.magicResistance *= 1.5f; break;
                case 4: e.artilleryResistance *= 1.5f; break;
            }
        }
    }
}

float GeneticAlgorithm::randFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

int GeneticAlgorithm::randomIndex(int max) {
    return rand() % max;
}
