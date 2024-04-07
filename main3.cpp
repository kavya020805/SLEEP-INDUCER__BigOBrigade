#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

typedef long long int ll;

int main() {
    int Number_Inmate;
    cout << "Enter number of inmates: ";
    cin >> Number_Inmate;

    vector<string> Names(Number_Inmate);
    vector<int> Earpod_ID(Number_Inmate);
    vector<vector<int>> Day(7, vector<int>(Number_Inmate));
    vector<int> p(Number_Inmate);

    cout << "Enter inmate data (Name Earpod_ID Day1 Day2 Day3 Day4 Day5 Day6 Day7 Penalty):" << endl;
    for(int i = 0; i < Number_Inmate; i++) {
        cin >> Names[i] >> Earpod_ID[i];
        for(int j = 0; j < 7; j++) {
            cin >> Day[j][i];
        }
        cin >> p[i];
    }

    int numDorms;
    cout << "Enter number of dorms: ";
    cin >> numDorms;

    vector<int> Channel(numDorms);
    int summ = 0;
    vector<pair<string, int>> dorms;
    for (int i = 0; i < numDorms; ++i) {
        string dormName;
        int numChannels;
        cout << "Enter dorm name and number of channels for dorm " << i + 1 << ": ";
        cin >> dormName >> numChannels;
        Channel[i] = numChannels;
        summ += numChannels;
        dorms.push_back({dormName, numChannels});
    }

    ofstream outFile("output.txt");
    for(int day = 1; day <= 7; day++) {
        vector<int> indices(Number_Inmate);
        iota(indices.begin(), indices.end(), 0);

        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return Day[day - 1][a] < Day[day - 1][b];
        });

        vector<pair<pair<int,int>, string>> a;
        outFile << "Day " << day << ":" << endl;
        for(int i = 0; i < Number_Inmate; i++) {
            int idx = indices[i];
            a.push_back({{Day[day-1][idx], p[idx]}, Names[idx]});
        }
        sort(a.begin(),a.end());

        vector<stack<pair<pair<int,int>, string>>> v; // Stack of pair of pair<int, int> and string
        v.push_back(stack<pair<pair<int,int>, string>>());
        v.back().push({{a[0].first.first, a[0].first.second}, a[0].second}); // Pushing sleep time, channel, and name
        for(int i = 1; i < Number_Inmate; i++) {
            int c = 0;
            for(int j = 0; j < v.size(); j++) {
                if(abs(v[j].top().first.first - a[i].first.first) >= v[j].top().first.second) {
                    c++;
                    v[j].push({{a[i].first.first, a[i].first.second}, a[i].second});
                    break;
                }
            }
            if(c == 0) {
                v.push_back(stack<pair<pair<int,int>, string>> ());
                v.back().push({{a[i].first.first, a[i].first.second}, a[i].second});
            }
        }

        int j = 0;
        if(v.size() > summ) {
            outFile << "Not possible\n";
        }
        else {
            for(int i = 0; i < numDorms; i++) {
                outFile << "dorm " << i+1 << " " << endl;
                int tmp1 = 0;
                while(Channel[i]--) {
                    outFile << "Channel-" << tmp1+1 << ": ";
                    tmp1++;
                    while(!v[j].empty()) {
                        outFile << v[j].top().second << " ";
                        v[j].pop();
                    }
                    j++;
                    outFile << endl;
                }
                outFile << endl;
            }
        }
        outFile << endl;
    }

    outFile.close();

    cout << "Output has been written to output.txt" << endl;

    return 0;
}
