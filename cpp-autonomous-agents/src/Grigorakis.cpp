#include "Grigorakis.h"

Grigorakis::Grigorakis(int startX, int startY, char symbol)
    : Hero(startX, startY, 'G') {}

void Grigorakis::move(const Map& map)
{

    static const int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    static const int dy[8] = {-1,  0,  1, -1, 1, -1, 0, 1};

    std::vector<std::pair<int, int>> unvisited;
    std::vector<std::pair<int, int>> fallback;

    // Σάρωση γειτονικών tiles
    for (int i = 0; i < 8; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!map.isInside(nx, ny)) continue;
        if (!map.isWalkable(nx, ny, hasKeyItem())) continue;

        char tile = map.getTile(nx, ny);

        if (tile == 'K' && !hasKeyItem())
        {
            setPosition(nx, ny);
            remember(nx, ny);
            return;
        }

        if (tile == 'C' && hasKeyItem() ) {
            setPosition(nx, ny);
            remember(nx, ny);
            return;
        }

        // Αν υπάρχει στην μνήμη του
        bool visited = false;
        for (const auto& p : getMemory())
        {
            if (p.first == nx && p.second == ny)
            {
                visited = true;
                break;
            }
        }

        if (!visited)
        {
            unvisited.emplace_back(nx, ny);
        }
        else
        {
            fallback.emplace_back(nx, ny);
        }
    }

    // Αν έχει δει την Ασημένια κινήται προς εκεί
    if (hasSeenAsimenia && !isTrappedStatus())
    {
        auto [tx, ty] = lastSeenAsimenia;

        std::vector<std::pair<int, int>> options;

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!map.isInside(nx, ny)) continue;
            if (!map.isWalkable(nx, ny, hasKeyItem())) continue;

            int distBefore = std::abs(x - tx) + std::abs(y - ty);
            int distAfter = std::abs(nx - tx) + std::abs(ny - ty);
            if (distAfter < distBefore)
            {
                options.emplace_back(nx, ny);
            }
        }

        if (!options.empty())
        {
            auto [nx, ny] = options[std::rand() % options.size()];
            setPosition(nx, ny);
            remember(nx, ny);
            return;
        }
    }

    // Εξερεύνηση άγνωστων tiles
    if (!unvisited.empty())
    {
        auto [nx, ny] = unvisited[std::rand() % unvisited.size()];
        setPosition(nx, ny);
        remember(nx, ny);
        return;
    }

    // Αν όλα είναι επισκέψιμα, πήγαινε κάπου τυχαία
    if (!fallback.empty())
    {
        auto [nx, ny] = fallback[std::rand() % fallback.size()];
        setPosition(nx, ny);
        remember(nx, ny);
        return;
    }   
}

void Grigorakis::render() const
{
    attron(COLOR_PAIR(5));
    mvaddch(y, x, 'G');
    attroff(COLOR_PAIR(5));
}