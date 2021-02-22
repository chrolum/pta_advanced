#include <iostream>
#include <string>
using namespace std;

typedef unsigned long long ull;

ull convert_to_decimal(string num, int radix)
{
    unsigned long long base = 1;
    unsigned long long res = 0;
    int d;
    for (auto it = num.rbegin(); it != num.rend(); it++)
    {
        d = *it < 'a' ? *it - '0' : *it - 'a' + 10;
        res += d * base;
        base *= radix;
    }
    return res;
}

// return a smallest radix, if search failed return 0
ull binary_search_radix(ull target_num, string convert_s, ull lo, ull hi)
{
    ull mid, curr_num;
    ull res = 0;
    while (lo <= hi)//[lo, hi] while lo == hi, still need to search once
    {
        mid = lo + (hi - lo) / 2;
        curr_num = convert_to_decimal(convert_s, mid);
        if (target_num < curr_num)//bigger, find left region
        {
            hi = mid - 1;
            continue;
        }
        if (target_num > curr_num)//smaller, find right region
        {
            lo = mid + 1;
            continue;
        }

        if (target_num == curr_num)
        {
            res = mid; // not need to compare, beacuse there will be a smaller radix each loop
            hi = mid - 1;//find the smaller region
            continue;
        }
    }
    return res; //0 mean search failed
}

int main(int argc, char const *argv[])
{
    string n1, n2, target_s, test_s;
    int tag, radix;

    cin >> n1 >> n2;
    cin >> tag >> radix;    

    target_s = tag == 1 ? n1 : n2;
    test_s = tag == 1 ? n2 : n1;

    ull target_num;
    
    target_num = convert_to_decimal(target_s, radix);

    ull lo, hi;
    lo = 2;
    //confirm the highest radix
    const ull max_radix = 
        target_num > 36 ? target_num : 36;
    hi = max_radix;

    //confirm the lowest radix
    ull tmp_d;
    for (char digit : test_s)
    {
        tmp_d = digit < 'a' ? digit - '0' + 1: digit - 'a' + 11;
        lo = lo < tmp_d ? tmp_d : lo;
    }

    ull res_radix = binary_search_radix(target_num, test_s, lo, hi);

    if (!res_radix)
    {
        cout << "Impossible";
    }
    else
    {
        cout << res_radix; 
    }
    return 0;
}
