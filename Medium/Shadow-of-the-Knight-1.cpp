#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

string Jump(string direction, int sx, int sy, int w, int h){
    static int prevX, prevY;
    static int minX,maxX, minY, maxY;

    // run this at first jump
    if(w != prevX || h != prevY){
        minX = 0;
        minY = 0;
        maxX = w-1;
        maxY = h-1;
        prevX = w;
        prevY = h;
    }

    if(!direction.empty()) {
        if(direction.find('U') != string::npos) {
            maxY = sy - 1;
        }
        if(direction.find('D') != string::npos) {
            minY = sy + 1;
        } 
        if (direction.find('L') != string::npos){
            maxX = sx - 1;
        }
        if (direction.find('R') != string::npos) {
            minX = sx + 1;
        } 
    }

    int newX = (minX + maxX) / 2;
    int newY = (minY + maxY) / 2;

    return to_string(newX) + " " + to_string(newY);
}

int main()
{
    int w; // width of the building.
    int h; // height of the building.
    cin >> w >> h; cin.ignore();
    int n; // maximum number of turns before game over.
    cin >> n; cin.ignore();
    int x0;
    int y0;
    cin >> x0 >> y0; cin.ignore();

    // game loop
    while (1) {
        string bomb_dir; // the direction of the bombs from batman's current location (U, UR, R, DR, D, DL, L or UL)
        cin >> bomb_dir; cin.ignore();

        // Write an action using cout. DON'T FORGET THE "<< endl"
        string result = Jump(bomb_dir, x0, y0, w, h);
        
        // the location of the next window Batman should jump to.
        cout << result << endl;

        stringstream ss(result);
        ss >> x0 >> y0;
    }

    
}