#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;

typedef long long int ll;

class Inmate {
public:
    string name;
    int earpodID;
    string sleepPattern;
    int p;

    // Constructor
    Inmate(string name, int earpodID, const string& sleepPattern, int p) 
        : name(name), earpodID(earpodID), sleepPattern(sleepPattern), p(p) {}

    // Function to convert sleep pattern from "HH:MM" format to minutes
    int getSleepMinutes() {
        int hours = stoi(sleepPattern.substr(0, 2));
        int minutes = stoi(sleepPattern.substr(3, 2));
        return hours * 60 + minutes;
    }
};

// Function to compare stacks based on their sizes
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

    if (Number_Inmate <= 0) {
        cerr << "Invalid number of inmates. Exiting..." << endl;
        return 1; // Exit with error code
    }

    vector<Inmate> inmates;

    cout << "Enter inmate data (Name Earpod_ID SleepPattern p):" << endl;
    for(int i = 0; i < Number_Inmate; i++) {
        string name, sleepPattern;
        int earpodID, p;
        cin >> name >> earpodID >> sleepPattern >> p;

        // Add error handling for invalid earpod ID or sleep pattern
        if (earpodID <= 0 || sleepPattern.length() != 5 || sleepPattern[2] != ':' || p < 20) {
            cerr << "Invalid input for inmate data. Exiting..." << endl;
            return 1; // Exit with error code
        }

        inmates.push_back(Inmate(name, earpodID, sleepPattern, p));
    }

    int numDorms;
    cout << "Enter number of dorms: ";
    cin >> numDorms;

    if (numDorms <= 0) {
        cerr << "Invalid number of dorms. Exiting..." << endl;
        return 1; // Exit with error code
    }

    vector<int> Channel(numDorms);
    int summ = 0;
    vector<pair<string, int>> dorms;
    for (int i = 0; i < numDorms; ++i) {
        string dormName;
        int numChannels;
        cout << "Enter dorm name and number of channels for dorm " << i + 1 << ": ";
        cin >> dormName >> numChannels;

        // Add error handling for invalid number of channels
        if (numChannels <= 0) {
            cerr << "Invalid number of channels for dorm " << dormName << ". Exiting..." << endl;
            return 1; // Exit with error code
        }

        Channel[i] = numChannels;
        summ += numChannels;
        dorms.push_back({dormName, numChannels});
    }
    
    cout << endl;
    int day = 1; // Specify the day for processing
    vector<pair<pair<int, int>, pair<string, int>>> a; // Pair of pair<int, int> and pair<string, int>
    for (int i = 0; i < Number_Inmate; i++) {
        a.push_back({{inmates[i].getSleepMinutes(), inmates[i].p}, {inmates[i].name, inmates[i].earpodID}});
    }
    sort(a.begin(), a.end());

    vector<stack<pair<pair<int,int>, pair<string, int>>>> v; // Stack of pair of pair<int, int> and pair<string, int>
    v.push_back(stack<pair<pair<int,int>, pair<string, int>>>());
    v.back().push({{a[0].first.first, a[0].first.second}, a[0].second}); // Pushing sleep time, p, and name
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
    cout << ANSI_COLOR_ORANGE << x << " number of Channel of Dorm are filled out of " << summ << ANSI_COLOR_RESET  << endl;
    int j = 0;
    if(x > summ) {
        cout << ANSI_COLOR_RED << "Not possible" << ANSI_COLOR_RESET << endl;
    }
    else {
        for(int i = 0; i < numDorms; i++) {
            cout << ANSI_COLOR_PURPLE << "dorm " << i + 1 << " " << ANSI_COLOR_RESET << endl;
            int tmp1 = Channel[i];
            while(tmp1 > 0) {
                cout << ANSI_COLOR_BLUE << "Channel-" << tmp1 << ": ";
                tmp1--;
                if(j < x) {
                    while(!v[j].empty()) {
                        cout << ANSI_COLOR_GREEN << v[j].top().second.first << " (ID: " << v[j].top().second.second << ") "; // Output inmate name and Earpod ID
                        v[j].pop();
                    }
                    j++;
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
