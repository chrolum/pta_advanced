#include <stdio.h>
#include <iostream>
#include <map>
using namespace std;

void read_ploy(int n, map<int, double>& ploy) {
    int e;
    double c;
    for (int i = 0; i < n; i++) {
        cin >> e >> c;
        ploy[e] = c;
    }
}


int main(int argc, char const *argv[])
{
    map<int, double> ploy1;
    map<int, double> ploy2;
    map<int, double> res;

    int n;
    cin >> n;
    read_ploy(n, ploy1);
    cin >> n;
    read_ploy(n, ploy2);

    //product
    int tmp_e;
    double tmp_c;
    for (auto item1 : ploy1) {
        for (auto item2 : ploy2) {
            tmp_e = item1.first + item2.first;
            tmp_c = item1.second * item2.second;

            if (res.count(tmp_e) == 0) {
                res[tmp_e] = tmp_c;
            }
            else {
                res[tmp_e] += tmp_c;
            }
        }
    }

    // print res
    cout << res.size();

    for (auto item = res.rbegin(); item != res.rend(); item++) {
        if (item->second < 0.1 && item->second > - 0.1) {
            continue;
        }
        cout << " " << item->first;
        printf(" %.1f", item->second);

    }
    return 0;
}   

