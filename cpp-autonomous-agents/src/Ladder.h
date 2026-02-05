#ifndef LADDER_H
#define LADDER_H

#include "Item.h"
#include "Map.h"

class Ladder: public Item
{
public:
    Ladder(int x, int y);
    void render(Map& map) const override;
    void interact(Hero& hero, Map& map) override;
    
};

#endif