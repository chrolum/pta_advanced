#include <iostream>
#include <string>
using namespace std;

// 
unsigned long long convert_to_decimal(string num, int radix)
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

int main(int argc, char const *argv[])
{
    string n1, n2, base_s, test_s;
    int tag, radix;

    cin >> n1 >> n2;
    cin >> tag >> radix;    

    base_s = tag == 1 ? n1 : n2;
    test_s = tag == 1 ? n2 : n1;

    unsigned long long base_num, test_num;
    
    base_num = convert_to_decimal(base_s, radix);

    unsigned long long lo, hi, mid;
    lo = 2;
    const unsigned long long max_radix = 
        base_num > 36 ? base_num : 36;
    hi = max_radix;

    //confirm the lowest radix
    int tmp_d;
    for (char digit : test_s)
    {
        tmp_d = digit < 'a' ? digit - '0' + 1: digit - 'a' + 11;
        lo = lo < tmp_d ? tmp_d : lo;
    }
    unsigned long long min_radix = max_radix + 1;

    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        test_num = convert_to_decimal(test_s, mid);
        if (test_num > base_num)
        {
            hi = mid - 1;
        }
        else if (test_num < base_num)
        {
            lo = mid + 1;
        }
        else //test_num == base_num
        {
            min_radix = min_radix > mid ? mid : min_radix;
            hi = mid - 1;// continue to search smaller radix
        }
        // cout << mid << " " << lo << " " << hi << endl;
    }


    if (min_radix == max_radix + 1)
    {
        cout << "Impossible";
    }
    else
    {
        cout << min_radix; 
    }
    return 0;
}
