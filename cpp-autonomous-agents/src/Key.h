#ifndef KEY_H
#define KEY_H

#include "Item.h"
#include "Map.h"

class Key: public Item
{
public:
    Key(int x, int y);
    void render(Map& map) const override;
    void interact(Hero& hero, Map& map) override;
    
};

#endif