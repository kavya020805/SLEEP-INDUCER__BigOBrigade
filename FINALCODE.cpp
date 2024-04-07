#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

typedef long long int ll;

class Inmate {
public:
    string name;
    int earpodID;
    vector<int> sleepPattern;
    int penalty;

    // Constructor
    Inmate(string name, int earpodID, const vector<int>& sleepPattern, int penalty) 
        : name(name), earpodID(earpodID), sleepPattern(sleepPattern), penalty(penalty) {}
};

bool compareStacks(const stack<pair<pair<int, int>, pair<string, int>>>& s1, const stack<pair<pair<int, int>, pair<string, int>>>& s2) {
    return s1.size() < s2.size(); // Sort in descending order
}

int main() {
    // Define ANSI escape codes for text color
    #define ANSI_COLOR_RED     "\x1b[31m"
    #define ANSI_COLOR_ORANGE  "\x1b[38;5;208m" // Orange color code
    #define ANSI_COLOR_YELLOW  "\x1b[33m"
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_BLUE    "\x1b[34m"
    #define ANSI_COLOR_PURPLE  "\x1b[35m" // Purple color code
    #define ANSI_COLOR_RESET   "\x1b[0m"

    int Number_Inmate;
    cout << "Enter number of inmates: ";
    cin >> Number_Inmate;

    vector<Inmate> inmates;

    cout << "Enter inmate data (Name Earpod_ID Day1 Day2 Day3 Day4 Day5 Day6 Day7 Penalty):" << endl;
    for(int i = 0; i < Number_Inmate; i++) {
        string name;
        int earpodID, penalty;
        vector<int> sleepPattern(7);

        cin >> name >> earpodID;
        for(int j = 0; j < 7; j++) {
            cin >> sleepPattern[j];
        }
        cin >> penalty;

        inmates.push_back(Inmate(name, earpodID, sleepPattern, penalty));
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
    
    cout << endl;
    for(int day = 1; day <= 1; day++) { // Corrected loop condition
        cout << ANSI_COLOR_ORANGE << "Day " << day << ":" << ANSI_COLOR_RESET << endl;
        vector<pair<pair<int, int>, pair<string, int>>> a; // Pair of pair<int, int> and pair<string, int>
        for (int i = 0; i < Number_Inmate; i++) {
            a.push_back({{inmates[i].sleepPattern[day - 1], inmates[i].penalty}, {inmates[i].name, inmates[i].earpodID}});
        }
        sort(a.begin(), a.end());

        vector<stack<pair<pair<int,int>, pair<string, int>>>> v; // Stack of pair of pair<int, int> and pair<string, int>
        v.push_back(stack<pair<pair<int,int>, pair<string, int>>>());
        v.back().push({{a[0].first.first, a[0].first.second}, a[0].second}); // Pushing sleep time, penalty, and name
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
                v.push_back(stack<pair<pair<int,int>, pair<string, int>>> ());
                v.back().push({{a[i].first.first, a[i].first.second}, a[i].second});
            }
        }
        sort(v.begin(), v.end(), compareStacks);

        int x = v.size();
        cout << x << " " << summ << endl;
        int j = 0;
        if(x > summ) {
            cout << ANSI_COLOR_RED << "Not possible" << ANSI_COLOR_RESET << endl;
        }
        else {
            for(int i = 0; i < numDorms; i++) {
                cout << ANSI_COLOR_PURPLE << "dorm " << i + 1 << " " << ANSI_COLOR_RESET << endl;
                int tmp1 = Channel[i];
                while(Channel[i] > 0) {
                    cout << ANSI_COLOR_BLUE << "Channel-" << tmp1<< ": ";
                    tmp1--;
                    if(j < x) {
                        while(!v[j].empty()) {
                            cout << ANSI_COLOR_GREEN << v[j].top().second.first << " (ID: " << v[j].top().second.second << ") "; // Output inmate name and Earpod ID
                            v[j].pop();
                        }
                        j++;
                    }
                    cout << endl;
                    Channel[i]--;
                }
                j = 0;
                cout << endl;
            }
        }
    }
    
    outFile.close();

    cout << ANSI_COLOR_PURPLE << "Output has been written to output.txt" << ANSI_COLOR_RESET << endl;

    return 0;
}
