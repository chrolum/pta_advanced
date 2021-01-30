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

bool isNormal(double a) {
    return (a < 10) && (a > -10);
}

void add_normalize(int e, double c, map<int, double>& ploy) {
    if (ploy.count(e) == 0) {
        ploy[e] = c;
    }
    else { // will be continous carry in
        bool hasCarried = true;
        while (hasCarried) {
            c += ploy[e];
            if (!isNormal(c)) { // has carry
                hasCarried = true;
                c = c / 10;
                ploy[e] = c;
                c = 1; //carry one
                e++;
            }
            else {
                hasCarried = false;
                ploy[e] = c;
            }    
        }
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
    double tmp_c, normal_c, carry;
    for (auto item1 : ploy1) {
        for (auto item2 : ploy2) {
            tmp_e = item1.first + item2.first;
            tmp_c = item1.second * item2.second;
            normal_c = tmp_c;
            carry = 0;

            //normalize the tmp coff
            while (!isNormal(normal_c)) {
                double normal_part = normal_c - (int)(normal_c / 10) * 10;
                normal_c = (int)(normal_c / 10);
                add_normalize(tmp_e, normal_part, res);
                carry++;
            }
            tmp_e += carry;
            
            add_normalize(tmp_e, normal_c, res);
        }
    }

    // print res
    cout << res.size();

    for (auto item = res.rbegin(); item != res.rend(); item++) {
        cout << " " << item->first;
        printf(" %.1f", item->second);
    }
    return 0;
}

