// Αφηφημένη Κλάση Item για τα αντικέιμενα
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <ncurses.h>
#include "Hero.h"

class Item
{
protected:
    int x, y;
    bool active = true;

public:
    virtual ~Item() = default;
    
    virtual void render(Map& map) const = 0;
    virtual void interact(Hero& hero, Map& map) = 0;

    int getX() const { return x; }
    int getY() const { return y; }

    bool isActive() const { return active; }
    void deactivate(Map& map) { active = false; map.setTile(x, y, ' '); }
};

#endif