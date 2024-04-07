
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

bool compareStacks(const stack<pair<int, int>>& s1, const stack<pair<int, int>>& s2) {
    return s1.size() < s2.size(); // Sort in descending order
}

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

    vector<pair<string, int>> dorms;
    for (int i = 0; i < numDorms; ++i) {
        string dormName;
        int numChannels;
        cout << "Enter dorm name and number of channels for dorm " << i + 1 << ": ";
        cin >> dormName >> numChannels;
        dorms.push_back({dormName, numChannels});
    }

    ofstream outFile("output.txt");
    for(int day = 1; day <= 7; day++) {
        vector<int> indices(Number_Inmate);
        iota(indices.begin(), indices.end(), 0);

        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return Day[day - 1][a] < Day[day - 1][b];
        });

        outFile << "Day " << day << ":" << endl;
        for(int i = 0; i < Number_Inmate; i++) {
            int idx = indices[i];
            outFile << Names[idx] << ' ' << Earpod_ID[idx] << ' ';
            outFile << Day[day - 1][idx] << ' ' << p[idx] << endl;
        }
        outFile << endl;
    }

    // Print dorm data
    outFile << "Dorm Data:" << endl;
    for (const auto& dorm : dorms) {
        outFile << "Dorm Name: " << dorm.first << endl;
        outFile << "Number of Channels: " << dorm.second << endl;
    }

    outFile.close();

    cout << "Output has been written to output.txt" << endl;

    return 0;
}
