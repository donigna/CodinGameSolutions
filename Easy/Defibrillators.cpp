#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

constexpr double DEG2RAD = M_PI / 180.0;

struct Defib
{
    size_t id;
    string name;
    string address;
    string phone;
    string lon;
    string lat;
};

// Convert string data to defib struct
Defib string_to_defib(string &s, char delimiter)
{
    Defib new_defib;
    string token;
    for (size_t i = 0; i < 6; i++)
    {
        size_t pos = s.find(delimiter);
        token = s.substr(0, pos);
        s.erase(0, pos + 1);
        switch (i)
        {
        case 0:
            new_defib.id = stoul(token);
            break;
        case 1:
            new_defib.name = token;
            break;
        case 2:
            new_defib.address = token;
            break;
        case 3:
            new_defib.phone = token;
            break;
        case 4:
            new_defib.lon = token;
            break;
        case 5:
            new_defib.lat = token;
            break;
        }
    }

    return new_defib;
}

// convert string double and change ',' to '.'
double n_stod(string s)
{
    s.replace(s.find(','), 1, ".");
    return stod(s);
}

string closest_defibrillator(const vector<Defib> &defibs, const string &lon, const string &lat)
{
    double userLon = n_stod(lon) * DEG2RAD;
    double userLat = n_stod(lat) * DEG2RAD;

    double nearest_defibrillator = numeric_limits<double>::max();
    string nearest_defib;

    for (const auto &d : defibs)
    {
        double defLon = n_stod(d.lon) * DEG2RAD;
        double defLat = n_stod(d.lat) * DEG2RAD;

        double x = (defLon - userLon) * cos((defLat + userLat) / 2.0);
        double y = (defLat - userLat);
        double distance = sqrt(x * x + y * y) * 6371.0;

        if (distance < nearest_defibrillator)
        {
            nearest_defibrillator = distance;
            nearest_defib = d.name;
        }
    }

    return nearest_defib;
}
int main()
{
    string lon;
    cin >> lon;
    cin.ignore();
    string lat;
    cin >> lat;
    cin.ignore();
    int n;
    cin >> n;
    cin.ignore();

    vector<Defib> defibs;
    defibs.reserve(n);

    for (int i = 0; i < n; i++)
    {
        string defib;
        getline(cin, defib);
        defibs.push_back(string_to_defib(defib, ';'));
    }
    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << closest_defibrillator(defibs, lon, lat) << endl;
}