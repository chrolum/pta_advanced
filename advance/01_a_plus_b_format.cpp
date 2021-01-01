#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>
using namespace std;

string solution(int a, int b)
{
    int sum = a + b;
    if (sum == 0)
        return "0";
    ostringstream formatted;
    int cnt = 0;
    int low_digit;
    int nagetive = sum < 0 ? 1 : 0;

    while (sum != 0)
    {
        low_digit = sum % 10;
        formatted << abs(low_digit);
        cnt++;
        if (cnt == 3 && sum / 10 != 0)
        {
            formatted << ",";
            cnt = 0;
        }
        sum = sum / 10;
    }
    if (nagetive)
        formatted << "-";
    string res = formatted.str();
    reverse(res.begin(), res.end());
    return res;
}

int main(int argc, char const *argv[])
{
    /* code */
    int a, b;
    string res;
    while (cin >> a >> b)
    {
        res = solution(a, b);
        cout << res << endl;
    }

    return 0;
}