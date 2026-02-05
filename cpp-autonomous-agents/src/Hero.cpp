// Αφηρημένη Κλάση Ήρωας για Γρηγοράκη και Ασημένια
#include "Hero.h"
#include "Map.h"  

Hero::Hero(int startX, int startY, char symbol)
{
    this->x = startX;
    this->y = startY;
    this->symbol = symbol;
}

// Αποθηκεύει τα tiles που έχει επισκεφθεί.
void Hero::remember(int x, int y)
{
    pathMemory.emplace_back(x, y);
}

// Επιστρέφει τα tiles που έχει επισκεφθεί.
const std::vector<std::pair<int, int>>& Hero::getMemory() const
{
    return pathMemory;
}

bool Hero::isAt(int checkX, int checkY) const
{
    return x == checkX && y == checkY;
}

void Hero::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

// Βοηθητική Συνάρτηση για το Αντικείμενο Κλειδί
void Hero::pickUpKey()
{
    hasKey = true;
}

void Hero::useKey()
{
    hasKey = false;
}

// Βοηθητική Συνάρτηση για το Αντικείμενο Κλειδί
bool Hero::hasKeyItem() const
{
    return hasKey;
}

// Βοηθητική Συνάρτηση για το Αντικείμενο Παγίδα
bool Hero::isTrappedStatus() const
{
    return isTrapped;
}

// Βοηθητική Συνάρτηση για το Αντικείμενο Παγίδα
void Hero::setTrapped(bool trapped)
{
    isTrapped = trapped;
}

int Hero::getX() const
{
    return x;
}

int Hero::getY() const
{
    return y;
}

char Hero::getSymbol() const
{
    return symbol;
}