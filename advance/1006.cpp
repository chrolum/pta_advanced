#include <iostream>
#include <string>
using namespace std;

struct Record
{
    string id;
    string signInTime;
    string signOutTime;
};

int toInt(char c) {return c - 48;}

int getHour(string s) {return toInt(s[0])*10 + toInt(s[1]);}
int getMin(string s) {return toInt(s[3])*10 + toInt(s[4]);}
int getSec(string s) {return toInt(s[6])*10 + toInt(s[7]);}
// return r1 < r2
bool isEarlier(string r1_time, string r2_time) {
    int h1 = getHour(r1_time);
    int h2 = getHour(r2_time);
    if (h1 != h2)
        return h1 < h2;
    
    int m1 = getMin(r1_time);
    int m2 = getMin(r2_time);
    if (m1 != m2)
        return m1 < m2;
    
    int s1 = getSec(r1_time);
    int s2 = getSec(r2_time);
    return s1 < s2;
}


int main(int argc, char const *argv[])
{
    /* code */
    Record earlistSignInRecord;
    Record latestSignOutRecord;

    Record tmpRecord;
    int n;
    cin >> n;
    cin >> tmpRecord.id >> tmpRecord.signInTime >> tmpRecord.signOutTime;
    earlistSignInRecord = tmpRecord;
    latestSignOutRecord = tmpRecord;
    for (size_t i = 1; i < n; i++) {
        cin >> tmpRecord.id >> tmpRecord.signInTime >> tmpRecord.signOutTime;
        earlistSignInRecord = isEarlier(earlistSignInRecord.signInTime, tmpRecord.signInTime) 
            ? earlistSignInRecord : tmpRecord; 
        latestSignOutRecord = !isEarlier(latestSignOutRecord.signOutTime, tmpRecord.signOutTime)
            ? latestSignOutRecord : tmpRecord;
    }

    cout << earlistSignInRecord.id << " " << latestSignOutRecord.id;
    return 0;
}
