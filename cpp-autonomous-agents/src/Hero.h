#ifndef HERO_H
#define HERO_H

#include <vector>
#include <string>
#include "ncurses.h"
#include "Map.h"
#include <cmath>

class Hero
{
protected:
    int x, y;
    char symbol;
    bool hasKey = false;
    bool isTrapped = false;
    std::vector<std::pair<int, int>> pathMemory;

public:
    Hero(int startX, int startY, char symbol);
    virtual ~Hero() = default;

    // Αφηρημένες μέθοδοι
    virtual void move(const Map& map) = 0;
    virtual void render() const = 0;

    void remember(int x, int y);
    const std::vector<std::pair<int, int>>& getMemory() const;
    bool isAt(int x, int y) const;
    void setPosition(int newX, int newY);
    void pickUpKey();
    void useKey();
    bool hasKeyItem() const;
    bool isTrappedStatus() const;
    void setTrapped(bool trapped);
    int getX() const;
    int getY() const;
    char getSymbol() const;
};

#endif