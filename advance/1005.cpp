#include <iostream>
#include <map>
#include <string>
using namespace std;

string trans[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main(int argc, char const *argv[])
{
    string n;
    cin >> n;
    int sum = 0;
    for (char c : n) {
        sum += c - 48;
    }
    
    string res = to_string(sum);

    cout << trans[res[0] - 48];

    for (int i = 1; i < res.size(); i++) {
        cout << " " << trans[res[i] - 48];
    }
    

    return 0;
}
