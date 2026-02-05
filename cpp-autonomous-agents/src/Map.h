#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <ncurses.h>
#include <iostream>

class Map
{
private:
    std::vector<std::string> grid;
    int width;
    int height;

public:
    bool loadFromFile(const std::string& filename);
    char getTile(int x, int y) const;
    void setTile(int x, int y, char tile);
    bool isWalkable(int x, int y, bool hasKey) const;
    bool isInside(int x, int y) const;
    void removeWalls();
    void render() const;
    std::pair<int, int> getRandomEmptyTile() const;
    int getHeight() const;
    int getWidth() const;
};

#endif