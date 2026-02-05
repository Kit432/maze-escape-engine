#ifndef GAME_H
#define GAME_H

#include "Map.h"
#include "Hero.h"
#include "Grigorakis.h"
#include "Asimenia.h"
#include "Trap.h"
#include "Key.h"
#include "Cage.h"
#include "Ladder.h"
#include "Item.h"
#include <vector>
#include <memory>
#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <algorithm>

class Game
{
private:
    Map map;
    std::vector<std::shared_ptr<Item>> items;
    std::shared_ptr<Hero> grigorakis;
    std::shared_ptr<Hero> asimenia;
    int turns = 0;
    bool gameOver = false;
    bool met = false;
    bool happyEnd = false;

public:
    Game();

    void loadMap(const std::string& filename);
    void placeObjects();
    void render();
    std::pair<int, int> findLadder() const;
    std::vector<std::pair<int, int>> findShortestPath(int startX, int startY, int targetX, int targetY);
    void followPath(std::shared_ptr<Hero> hero1, std::shared_ptr<Hero> hero2, const std::vector<std::pair<int, int>>& path);
    bool heroesCanMeet() const;
    void update();
    void run();
};

#endif