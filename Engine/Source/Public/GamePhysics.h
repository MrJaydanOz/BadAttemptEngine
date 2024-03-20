#pragma once
#include "Nodes/Particle.h"
#include "Game.h"

class Physics
{
    friend class Game;

private:
    std::vector<Particle> _particles;

public:
    bool isSimulating;

private:
    void Prepare();

    void Simulate(float deltaTime);
};