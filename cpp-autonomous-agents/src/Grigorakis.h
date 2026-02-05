#ifndef GRIGORAKIS_H
#define GRIGORAKIS_H

#include "Hero.h"


class Grigorakis : public Hero
{
private:
    std::pair<int, int> lastSeenAsimenia = {-1, -1};
    bool hasSeenAsimenia = false;

public:
    Grigorakis(int startX, int startY, char symbol);
    void move(const Map& map) override;
    void render() const override;
};

#endif