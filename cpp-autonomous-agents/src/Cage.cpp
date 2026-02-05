// Cage Class
#include "Cage.h"

Cage::Cage(int x, int y, std::shared_ptr<Hero> trappedHero)
{
    this->x = x;
    this->y = y;
    this->trappedHero = trappedHero;
}

// Για απεικόνιση
void Cage::render(Map& map) const
{
    attron(COLOR_PAIR(3));
    map.setTile(x, y, 'C');
    mvaddch(y, x, 'C');
    attroff(COLOR_PAIR(3));
}

// Για αλληλεπίδραση με ήρωες
void Cage::interact(Hero& hero, Map& map)
{
    if (hero.hasKeyItem() && hero.isTrappedStatus() == false && hero.isAt(x, y))
    {
        {
            trappedHero->setTrapped(false);
            trappedHero = nullptr; // Cage is now empty
            hero.useKey();
            deactivate(map);
        }
    }
}