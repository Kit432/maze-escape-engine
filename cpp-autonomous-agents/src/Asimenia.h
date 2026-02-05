#ifndef ASIMENIA_H
#define ASIMENIA_H

#include "Hero.h"

class Asimenia : public Hero
{
private:
    bool gregorakisWasTrapped = false;
    std::pair<int, int> gregorakisCagePosition = {-1, -1};

public:
    Asimenia(int startX, int startY, char symbol);
    void move(const Map& map) override;
    void render() const override;
};

#endif