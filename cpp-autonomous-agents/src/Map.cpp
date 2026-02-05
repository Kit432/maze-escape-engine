// Map Class
#include "Map.h"
#include "Hero.h"

// Διάβασμα δομής χάρτη από αρχείο
bool Map::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    grid.clear();
    std::string line;
    while (std::getline(file, line))
    {
        // Έλεγχος για σωστή δομή χάρτη
        for (char c : line)
        {
            if (c != '*' && c != ' ')
            {
                std::cerr << "Invalid character: " << c
                          << "Only '*' and ' ' allowed." << std::endl;
                file.close();
                return false;
            }
        }
        grid.push_back(line);
    }
    file.close();

    height = grid.size();
    width = (height > 0) ? grid[0].length() : 0;
    return true;
}

// Βοηθητική Συνάρτηση επιστροφής μέρους του χάρτη
char Map::getTile(int x, int y) const
{
    // Αν είναι εκτός ορίων επιστρέφει τοίχο '*'
    if (y < 0 || y >= height || x < 0 || x >= width) return '*';
    return grid[y][x];
}

void Map::setTile(int x, int y, char tile)
{
    if (y >= 0 && y < height && x >= 0 && x < width)
    {
        grid[y][x] = tile;
    }
}

// Βοηθητική Συνάρτηση για το αν οι ήρωες μπορούν να περπατήσουν
bool Map::isWalkable(int x, int y, bool hasKey) const
{
    char tile = getTile(x, y);
    if (tile == '*' || (tile == 'C' && hasKey == false))
        return false;
    else
        return true;
}

// Βοηθητική Συνάρτηση για το αν είναι μέσα στα όρια του χάρτη
bool Map::isInside(int x, int y) const
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Βοηθητική Συνάρτηση για όταν συναντηθούν οι ήρωες
void Map::removeWalls()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (grid[y][x] == '*')
            {
                grid[y][x] = ' ';
                mvaddch(y, x, ' ');
                refresh();
                napms(10);
            }
        }
    }
}

// Εμφανίζει όλο τον χάρτη στην οθόνη, γραμμή-γραμμή
void Map::render() const
{
    for (int y = 0; y < height; y++)
    {
        mvprintw(y, 0, "%s", grid[y].c_str());
    }
}

// Βρίσκει τυχαία κενή θέση για να τοποθετηθεί ήρωας ή αντικείμενο
std::pair<int, int> Map::getRandomEmptyTile() const
{
    int x, y;
    do
    {
        x = std::rand() % width;
        y = std::rand() % height;
    } while (grid[y][x] != ' ');
    
    return {x, y};
}

int Map::getHeight() const
{
    return height;
}

int Map::getWidth() const
{
    return width;
}