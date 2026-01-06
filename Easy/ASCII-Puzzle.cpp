#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

 void toLowerCase(string& s) {
  
  	// Manual converting each character to lowercase
  	// using ASCII values
    for (char &c : s) {
        if (c >= 'A' && c <= 'Z') {
          
          	// Convert uppercase to lowercase
          	// by adding 32
            c += 32;
        }
    }
}

int main()
{
    int l;
    cin >> l; cin.ignore();
    int h;
    cin >> h; cin.ignore();
    string t;
    getline(cin, t);

    toLowerCase(t);

    for (int i = 0; i < h; i++) {
        string row;
        getline(cin, row);
        for (char &c : t) {
            int nword = c - 'a' + 1;

            if(nword < 1 || nword > 26){
                nword = 27;
            }

            int spos = l * (nword - 1);
            for (int s = spos; s < spos + l; ++s) {
                cout << row[s];
            }
        }
        cout << endl;
    }
}