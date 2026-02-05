#include "Ladder.h"

Ladder::Ladder(int x, int y)
{
    this->x = x;
    this->y = y;
}

// Για απεικόνιση
void Ladder::render(Map&map) const
{
    attron(COLOR_PAIR(4));
    map.setTile(x, y, 'L');
    mvaddch(y, x, 'L');
    attroff(COLOR_PAIR(4));
}

void Ladder::interact(Hero& hero, Map& map)
{
    
}