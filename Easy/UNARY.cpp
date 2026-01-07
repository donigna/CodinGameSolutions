#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

int main()
{
    string message;
    getline(cin, message);

    // Write an answer using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    // cek apakah n - 1 == n - 2
    // jika iya,
    // tidak usah buat perubahan
    // jika tidak,
    // buat perubahan

    string answer;
    static bool n;

    for(char& c : message) {
        bitset<7> b(c);
        
        for(size_t i = 1; i < b.size()+1; i++) {
            if(answer.empty()){
                    n = b[b.size() - i];
                if(n)
                    answer += "0 ";
                else
                    answer += "00 ";
            }
            else if (n ^ b[b.size() - i])
            {
                answer += ' ';
                n = b[b.size() - i];
                
                if(n)
                answer += "0 ";
                else
                answer += "00 "; 
        }    
        answer += '0';    
    }
        cerr << endl;
    }

    

    cout << answer << endl;
}