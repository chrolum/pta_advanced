#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int n;
    cin >> n;
    int* data = new int[n];

    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    int win_left = 0, win_right = 0;

    for (int i = 0; i < n; i++) {
        //TO-DO: silding window
    }

    int sum = 0;
    for (int i = win_left; win_left <= win_right; i++) {
        sum += data[i];
    }

    cout << sum;
    for (int i = win_left; i <= win_right; i++) {
        cout << data[i];
    }

    return 0;
}
