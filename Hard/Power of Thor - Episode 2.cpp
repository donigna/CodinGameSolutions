#include <iostream>
#include <string>
#include <vector>
#include <map>   // for using map
#include <tuple> // for using tuple

using namespace std;

const int WIDE = 4;
const int MAX_X = 39;
const int MAX_Y = 17;

// Represent giant position
struct Giant
{
    int x;
    int y;
};

// Represent positon and data of Thor.
class Thor
{
private:
    int tx;
    int ty;
    int h;
    int n;
    vector<Giant> giants;

public:
    // Constructor for thor initialization
    Thor(int start_tx, int start_ty) : tx(start_tx), ty(start_ty), h(0), n(0) {}

    // Update game state each loop
    void scan(int health, int num_giants, const vector<Giant> &giant_list)
    {
        h = health;
        n = num_giants;
        giants = giant_list;
    }

    // --- Helper Functions ---

    // Find the average center of all giants using barycenter method.
    pair<int, int> find_center() const
    {
        if (giants.empty())
            return {-1, -1};

        long long sumX = 0;
        long long sumY = 0;
        for (const auto &giant : giants)
        {
            sumX += giant.x;
            sumY += giant.y;
        }

        // The python code uses int() which truncates towards zero.
        int centerX = sumX / n;
        int centerY = sumY / n;

        cerr << "Center: (" << centerX << ", " << centerY << ")" << endl;

        return {centerX, centerY};
    }

    /*
        Find all giants inside striking distance
        x - current x position of thor
        y - current y position of thor
    */
    vector<Giant> _closest(int x, int y) const
    {
        vector<Giant> closest_giants;
        for (const auto &giant : giants)
        {
            if (abs(giant.x - x) <= WIDE && abs(giant.y - y) <= WIDE)
            {
                closest_giants.push_back(giant);
            }
        }
        return closest_giants;
    }

    // check if any giant is too close 1 tile from thor.
    bool giants_too_close(int x, int y) const
    {
        for (const auto &giant : giants)
        {
            if (abs(giant.x - x) <= 1 && abs(giant.y - y) <= 1)
            {
                return true;
            }
        }
        return false;
    }

    // calculate the Manhattan distance between two points;
    int dist(const pair<int, int> &p1, const pair<int, int> &p2) const
    {
        return abs(p1.first - p2.first) + abs(p1.second - p2.second);
    }

    // --- Core Logic Functions ---

    // Move thor to get closes to the center (cx, cy).
    // Update thor position (tx, ty) and return the action string.
    string find_move(int cx, int cy)
    {
        string action = "";

        // Vertical movement
        if (cy > ty)
        {
            action += "S";
            ty += 1;
        }
        else if (cy < ty)
        {
            action += "N";
            ty -= 1;
        }

        // Horizontal movement
        if (cx > tx)
        {
            action += "E";
            tx += 1;
        }
        else if (cx < tx)
        {
            action += "W";
            tx -= 1;
        }

        if (action.empty())
        {
            return "WAIT";
        }
        return action;
    }

    // Determine the best escape move when giants are too close.
    // update thor position and return the action string.
    string run_away()
    {
        // Structure: {Action_string, {Strike_count, {new_tx, new_ty}}}
        using MoveOption = tuple<string, int, int, int>;
        vector<MoveOption> possible_moves;

        map<string, pair<int, int>> directions = {
            {"E", {1, 0}}, {"N", {0, -1}}, {"NE", {1, -1}}, {"NW", {-1, -1}}, {"S", {0, 1}}, {"SE", {1, 1}}, {"SW", {-1, 1}}, {"W", {-1, 0}}, {"WAIT", {0, 0}}};

        for (const auto &entry : directions)
        {
            const string &action = entry.first;
            int dx = entry.second.first;
            int dy = entry.second.second;
            int next_x = tx + dx;
            int next_y = ty + dy;

            if (next_x >= 0 && next_x <= MAX_X && next_y >= 0 && next_y <= MAX_Y)
            {
                if (!giants_too_close(next_x, next_y))
                {
                    int strike_count = _closest(next_x, next_y).size();
                    possible_moves.emplace_back(action, strike_count, next_x, next_y);
                }
            }
        }

        if (possible_moves.empty())
        {
            return "STRIKE";
        }

        pair<int, int> center = find_center();

        MoveOption bestOption = possible_moves[0];
        string bestAction = get<0>(bestOption);
        int bestDist = dist({get<2>(bestOption), get<3>(bestOption)}, center);

        for (const auto &option : possible_moves)
        {
            const string &currentAction = get<0>(option);
            int currentStrikeCount = get<1>(option);
            int current_x = get<2>(option);
            int current_y = get<3>(option);
            int currentDist = dist({current_x, current_y}, center);

            if (currentStrikeCount > get<1>(bestOption) ||
                (currentStrikeCount == get<1>(bestOption) && currentDist > bestDist))
            {

                bestOption = option;
                bestAction = currentAction;
                bestDist = currentDist;
            }
        }

        // Update Thor's position if a move was chosen
        if (bestAction != "STRIKE" && bestAction != "WAIT")
        {
            tx = get<2>(bestOption);
            ty = get<3>(bestOption);
        }

        return bestAction;
    }

    // determine the action
    string find_best_move()
    {
        int centerX, centerY;
        tie(centerX, centerY) = find_center();

        if (giants_too_close(tx, ty))
        {
            return run_away();
        }
        else
        {
            return find_move(centerX, centerY);
        }
    }

    // main game loop
    string move()
    {
        if (n == 0)
            return "WAIT";

        vector<Giant> closest_giants = _closest(tx, ty);

        if (n == closest_giants.size())
        {
            return "STRIKE";
        }
        else
        {
            return find_best_move();
        }
    }
};

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int start_tx;
    int start_ty;
    cin >> start_tx >> start_ty;
    cin.ignore();

    // Instantiate Thor with the starting position
    Thor thor(start_tx, start_ty);

    // game loop
    while (1)
    {
        int h; // the remaining number of hammer strikes.
        int n; // the number of giants which are still present on the map.
        cin >> h >> n;
        cin.ignore();

        vector<Giant> current_giants;
        for (int i = 0; i < n; i++)
        {
            int x;
            int y;
            cin >> x >> y;
            cin.ignore();
            current_giants.push_back({x, y});
        }

        // Update Thor's state
        thor.scan(h, n, current_giants);

        string action = thor.move();

        cout << action << endl;
    }
}