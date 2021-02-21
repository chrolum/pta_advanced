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

    int lo, hi, mid;
    lo = 1, hi = 36;

    //confirm the lowest radix
    int tmp_d;
    for (char digit : test_s)
    {
        tmp_d = digit < 'a' ? digit - '0' : digit - 'a' + 10;
        lo = lo < tmp_d ? tmp_d : lo;
    }

    int min_radix = 37;
    bool firstLoop = true;
    while (lo < hi || firstLoop)
    {
        firstLoop = false;
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


    if (min_radix == 37)
    {
        cout << "Impossible";
    }
    else
    {
        cout << min_radix; 
    }
    return 0;
}
