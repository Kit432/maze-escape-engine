#ifndef TRAP_H
#define TRAP_H

#include "Item.h"
#include "Map.h"

class Trap: public Item
{
private:
    bool activated = false;

public:
    Trap(int x, int y);
    void render(Map& map) const override;
    void interact(Hero& hero, Map& map) override;
    bool isActivated() const;
};

#endif