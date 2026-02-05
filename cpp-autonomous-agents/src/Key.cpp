// Key Class
#include "Key.h"

Key::Key(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Για απεικόνιση
void Key::render(Map& map) const
{
    attron(COLOR_PAIR(2));
    map.setTile(x, y, 'K');
    mvaddch(y, x, 'K');
    attroff(COLOR_PAIR(2));
}

// Για αλληλεπίδραση με ήρωες
void Key::interact(Hero& hero, Map& map)
{
    if (isActive() && hero.isAt(x, y)==true && hero.hasKeyItem()==false)
    {
        hero.pickUpKey();
        deactivate(map);
    }
}