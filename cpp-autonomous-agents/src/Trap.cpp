// Trap Class
#include "Trap.h"

Trap::Trap(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Για απεικόνιση
void Trap::render(Map& map) const
{
    attron(COLOR_PAIR(3));
    map.setTile(x, y, 'T');
    mvaddch(y, x, 'T');
    attroff(COLOR_PAIR(3));
}

// Για αλληλεπίδραση με ήρωες
void Trap::interact(Hero& hero, Map& map)
{
    if (isActive() && hero.isAt(x, y))
    {
        if (hero.isTrappedStatus() == false)
            hero.setTrapped(true);
        activated = true;
        deactivate(map);
    }
}

bool Trap::isActivated() const
{
    return activated;
}
