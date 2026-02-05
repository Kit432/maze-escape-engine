#ifndef CAGE_H
#define CAGE_H

#include "Item.h"
#include "Hero.h"
#include "Map.h"
#include <ncurses.h>
#include <memory>

class Cage: public Item
{
private:
    std::shared_ptr<Hero> trappedHero;

public:
    Cage(int x, int y, std::shared_ptr<Hero> trappedHero);
    void render(Map& map) const override;
    void interact(Hero& hero, Map& map) override;
};

#endif