#include <iostream>
#include <vector>
#include <math.h>
#include <queue>
#include <set>
using namespace std;

typedef pair<int, int> Edge;//pair<vex, weight>
auto comp = [](const pair<int, int> &a, const pair<int, int> &b)
        { return a.second > b.second; };
class CityInfo
{
public:
    int** road;
    int* rescue_team;
    int city_num = 0;
    int road_num = 0;
    int c1 = 0, c2 = 0;
    int shortest_num = 0, max_rescue = 0;
public:
    int* distTo;
    vector<int>* pre_city;
    bool* hasVisited;
    set<int> path_cities;
    int visited_city_num = 0;
public:
    CityInfo()
    {
        cin >> city_num >> road_num >> c1 >> c2;
        rescue_team = new int[city_num];
        distTo = new int[city_num];
        // init the distTo array for dfs
        road = new int*[city_num];
        hasVisited = new bool[city_num];
        pre_city = new vector<int>[city_num];
        for (int i = 0; i < city_num; i++)
        {
            distTo[i] = INT32_MAX;
            cin >> rescue_team[i];
            road[i] = new int[city_num];
            hasVisited[i] = false;
        }
        // hasVisited[c1] = true;
        distTo[c1] = 0;

        int c1_tmp, c2_tmp, w;
        for (int i = 0; i < road_num; i++)
        {
            cin >> c1_tmp >> c2_tmp >> w;
            road[c1_tmp][c2_tmp] = w;
            road[c2_tmp][c1_tmp] = w;
        }
    }

    void print_res()
    {
        cout << shortest_num << ' ' << max_rescue << endl;
    }

    void dijstra()
    {
        int vex, w;
        while (!hasVisitedAllCity()) {
            vex = getMinVex();
            if (!hasVisited[vex]) {
                relax(vex);
            }
        }

        // cout << "distTo " << c2 << " is " << distTo[c2] << endl;
        shortest_num =  getShortPathNum(c2);
        max_rescue = getMaxRescueTeams(c2);
        // cout << "short " << shortest_num << endl;
    }

private:

    void relax(int v)
    {
        // cout << "relaxing vex " << v << endl;
        for (int i = 0; i < city_num; i++)
        { 
            if (road[v][i] == 0)//not road here
                continue;
            if (distTo[i] >= distTo[v] + road[v][i])
            {
                if (distTo[i] > distTo[v] + road[v][i]) {
                    pre_city[i].clear();
                }
                distTo[i] = distTo[v] + road[v][i];
                
                pre_city[i].push_back(v);
                // cout << "relaxing vex:" << v <<", " << "to: " << i << endl; //debug
            }
        }
        hasVisited[v] = true;
        visited_city_num++;
    }

    int getMinVex() {
        int min_dist = INT32_MAX;
        int min_vex = c1;
        for (int i = 0; i < city_num; i++)
        {
            if (distTo[i] < min_dist && !hasVisited[i]) {
                min_dist = distTo[i];
                min_vex = i;
            }
        }
        return min_vex;
    }

    bool hasVisitedAllCity() {
        return visited_city_num == city_num;
    }

    int getShortPathNum(int v)
    {
        path_cities.insert(v);
        if (v == c1)
            return 1;
        int n = 0;
        for (int pre_vex : pre_city[v]) {
            n += getShortPathNum(pre_vex);
        }
        return n;
    }

    int getMaxRescueTeams(int v) {
        // for (int v : path_cities) {
        //     max_rescue += rescue_team[v];
        //     // cout << v << " ";
        // }
        if (v == c1)
            return rescue_team[c1];
        int prev_max = 0;
        int tmp;
        for (int pre_vex : pre_city[v]) {
            tmp = getMaxRescueTeams(pre_vex);
            // cout << "prev vex: " << pre_vex << "max: " << tmp << endl;
            prev_max = prev_max < tmp ? tmp : prev_max;
        }
        return prev_max + rescue_team[v];
    }
};

int main(int argc, char const *argv[])
{
    CityInfo cities = CityInfo();
    cities.dijstra();
    cities.print_res();
    
    return 0;
}
