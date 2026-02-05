// Game Class
#include "Game.h"

Game::Game()
{
    // Για τυχαία τοποθέτηση
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

// Κάνει load τον χάρτη
void Game::loadMap(const std::string& filename)
{
    if (!map.loadFromFile(filename))
    {
        endwin();
        throw std::runtime_error("Failed to load map: " + filename);
    }
}

// Τοποθετεί τα αντικείμενα και τους ήρωες σε τυχαίες θέσεις
void Game::placeObjects()
{

    // Τοποθέτησε Γρηγοράκη
    auto [gx, gy] = map.getRandomEmptyTile();
    grigorakis = std::make_shared<Grigorakis>(gx, gy, 'G');

    // Τοποθέτησε Ασιμένια τουλάχιστον 7 τετράγωνα μακριά
    std::pair<int, int> aPos;
    do
    {
        aPos = map.getRandomEmptyTile();
    } while (std::abs(aPos.first - gx) < 7 && std::abs(aPos.second - gy) < 7);

    asimenia = std::make_shared<Asimenia>(aPos.first, aPos.second, 'A');

    // Τοποθέτησε 2 παγίδες
    auto [ix1, iy1] = map.getRandomEmptyTile();
    items.push_back(std::make_shared<Trap>(ix1, iy1));
    auto [ix2, iy2] = map.getRandomEmptyTile();
    items.push_back(std::make_shared<Trap>(ix2, iy2));

    // Τοποθέτησε 2 κλειδιά
    auto [ix3, iy3] = map.getRandomEmptyTile();
    items.push_back(std::make_shared<Key>(ix3, iy3));
    auto [ix4, iy4] = map.getRandomEmptyTile();
    items.push_back(std::make_shared<Key>(ix4, iy4));
    

    // Τοποθέτησε 1 σκάλα (αόρατη στην αρχή)
    auto [ix5, iy5] = map.getRandomEmptyTile();
    items.push_back(std::make_shared<Ladder>(ix5,iy5));
}

// Ζωγραφίζει τα objects του παιχνιδιού(χάρτης, αντικείμενα, ήρωες)
void Game::render()
{
    clear();
    map.render();
    grigorakis->render();
    asimenia->render();

    // Εμφανίζει τα αντικείμενα μόνο εφόσον είναι ακόμα ενεργοποιημένα
    for (const auto& item: items)
    {
        if (item->isActive())
        {
            item->render(map);
        }
    }

    // Δείχνει τα τέρμινα
    int turnsRow = map.getHeight() + 1;
    mvprintw(turnsRow, 0, "Turn: %d", turns);
    refresh();
}

// Βοηθητική Συνάρτηση για να βρει την θέση της σκάλας
std::pair<int, int> Game::findLadder() const
{
    for (const auto& item : items)
    {
        if (auto ladder = dynamic_cast<Ladder*>(item.get()))
        {
            return {ladder->getX(), ladder->getY()};
        }
    }
    return {-1, -1};
}

// Αλγόριθμο που ακολουθούν οι ήρωες αφού βρεθούν
std::vector<std::pair<int, int>> Game::findShortestPath(int startX, int startY, int targetX, int targetY)
{
    std::queue<std::pair<int, int>> q;
    std::map<std::pair<int, int>, std::pair<int, int>> previous;
    std::set<std::pair<int, int>> visited;

    q.push({startX, startY});
    visited.insert({startX, startY});

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    while (!q.empty())
    {
        auto [x, y] = q.front(); q.pop();

        if (x == targetX && y == targetY)
            break;

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            auto next = std::make_pair(nx, ny);

            if (!map.isInside(nx, ny)) continue;
            if (visited.count(next)) continue;
            if (!map.isWalkable(nx, ny, true)) continue;

            visited.insert(next);
            previous[next] = {x, y};
            q.push(next);
        }
    }

    std::vector<std::pair<int, int>> path;
    std::pair<int, int> current = {targetX, targetY};
    while (current != std::make_pair(startX, startY))
    {
        path.push_back(current);
        if (previous.find(current) == previous.end()) return {};
        current = previous[current];
    }

    std::reverse(path.begin(), path.end());
    return path;
}

// Αναγκάζει τους ήρωες να πάρουν ένα συγκεκριμένο μονοπάτι
void Game::followPath(std::shared_ptr<Hero> hero1, std::shared_ptr<Hero> hero2, const std::vector<std::pair<int, int>>& path)
{
    for (const auto& [x, y] : path)
    {
        hero1->setPosition(x, y);
        hero2->setPosition(x, y);
        render();
        napms(150);
    }
}

// Συνάρτηση ελέγχου για το αν είναι δυνατό να βρεθούν οι ήρωες
bool Game::heroesCanMeet() const
{
    std::queue<std::pair<int, int>> q;
    std::set<std::pair<int, int>> visited;

    int startX = grigorakis->getX();
    int startY = grigorakis->getY();
    int targetX = asimenia->getX();
    int targetY = asimenia->getY();

    q.push({startX, startY});
    visited.insert({startX, startY});

    int dx[4] = {0, 0, -1, 1};
    int dy[4] = {-1, 1, 0, 0};

    while (!q.empty())
    {
        auto [x, y] = q.front(); q.pop();

        if (x == targetX && y == targetY)
        {
            return true;
        }

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            std::pair<int, int> next = {nx, ny};

            if (!map.isInside(nx, ny)) continue;
            if (!map.isWalkable(nx, ny, true)) continue;
            if (visited.count(next)) continue;

            visited.insert(next);
            q.push(next);
        }
    }

    return false;
}

// Ενημερώνει την κατάσταση του παιχνιδιού κάθε τέρμινο
void Game::update()
{
    // Οι ήρωες κινούνται μόνο εφόσον δεν ειναι παγιδευμένοι
    if(grigorakis->isTrappedStatus() == false)
        grigorakis->move(map);
    if(asimenia->isTrappedStatus() == false)
        asimenia->move(map);
    
    // Αλληλεπιδράσεις με αντικείμενα
    for (auto it = items.begin(); it != items.end(); ++it)
    {
        auto& item = *it;

        // Αν ο Γρηγοράκης είναι πάνω σε item
        if (grigorakis->isAt(item->getX(), item->getY()))
        {
            item->interact(*grigorakis, map);

            // Αν ενεργοποιηθεί η παγίδα μετατρέπεται σε κλουβί
            if (auto trap = dynamic_cast<Trap*>(item.get()))
            {
                if (trap->isActivated())
                {
                    if (!dynamic_cast<Cage*>(item.get()))
                    {
                        *it = std::make_shared<Cage>(trap->getX(), trap->getY(), grigorakis);
                    }
                }
            }
        }

        // Αν η Ασημένια είναι πάνω σε item
        if (asimenia->isAt(item->getX(), item->getY()))
        {
            item->interact(*asimenia, map);

            if (auto trap = dynamic_cast<Trap*>(item.get()))
            {
                if (trap->isActivated())
                {
                    if (!dynamic_cast<Cage*>(item.get()))
                    {
                        *it = std::make_shared<Cage>(trap->getX(), trap->getY(), grigorakis);
                    }
                }
            }
        }
    }

    // Για όταν συναντηθούν
    if (grigorakis->getX() == asimenia->getX() && grigorakis->getY() == asimenia->getY())
    {
        map.removeWalls();

        auto [lx, ly] = findLadder();

        auto pathG = findShortestPath(grigorakis->getX(), grigorakis->getY(), lx, ly);

        followPath(grigorakis, asimenia, pathG);

        met = true;
        gameOver = true;
        
        // Όταν βρεθούν και οι δύο στη σκάλα
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            auto& item = *it;
            if (auto ladder = dynamic_cast<Ladder*>(item.get()))
            {
                if (grigorakis->isAt(ladder->getX(), ladder->getY()) &&
                asimenia->isAt(ladder->getX(), ladder->getY()))
                {
                    happyEnd = true;
                    met = false;
                }
            }
        }
    }
    
    // Για όταν το παιχνίδι είναι χαμένο
    if (turns > 1000 
    || (grigorakis->isTrappedStatus() == true && asimenia->isTrappedStatus() == true)
    || heroesCanMeet() == false)
    {
        gameOver = true;
    }
}

// Η κύρια μέθοδος όλου του προγράμματος
void Game::run()
{
    placeObjects();

    initscr();
    noecho();
    curs_set(FALSE);

    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK); // default
    init_pair(2, COLOR_YELLOW, COLOR_BLACK); // Κλειδιά
    init_pair(3, COLOR_RED, COLOR_BLACK); // Παγίδες/Κλουβιά
    init_pair(4, COLOR_CYAN, COLOR_BLACK); // Σκάλα
    init_pair(5,COLOR_BLUE,COLOR_BLACK); // Ήρωες

    // Τρέχει μέχρι να συναντηθούν ή να ειναι χαμένο το παιχνίδι
    while (!gameOver) 
    {
        render();
        update();
        turns++;

        napms(300); // Ταχύτητα παιχνιδιού
    }

    render();
    update();

    // Όταν συναντηθούν δεν αυξάνονται πια τα τέρμινα
    while(met)
    {
        render();
        update();

        napms(1000);
    }

    render();
    update();

    int turnsRow = map.getHeight() + 1;
    if (happyEnd)
    {
        mvprintw(turnsRow, 0, "VICTORY!"); 
    }
    else
    {
        mvprintw(turnsRow, 0, "DEFEAT...");
    }
    refresh();

    getch();
    endwin();
}