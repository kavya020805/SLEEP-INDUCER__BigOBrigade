#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <fstream>
#include <map>

using namespace std;

bool compareStacks(const stack<pair<string, int>>& s1, const stack<pair<string, int>>& s2) {
    return s1.size() < s2.size(); // Sort in descending order of stack sizes
}

int main() {
    // Input for inmate data
    int Number_Inmate;
    cout << "Enter number of inmates: ";
    cin >> Number_Inmate;

    vector<string> Names(Number_Inmate);
    vector<int> Earpod_ID(Number_Inmate);
    vector<vector<int>> Day(7, vector<int>(Number_Inmate));
    vector<int> Penalty(Number_Inmate);

    cout << "Enter inmate data (Name Earpod_ID Day1 Day2 Day3 Day4 Day5 Day6 Day7 Penalty):" << endl;
    for(int i = 0; i < Number_Inmate; i++) {
        cin >> Names[i] >> Earpod_ID[i];
        for(int j = 0; j < 7; j++) {
            cin >> Day[j][i];
        }
        cin >> Penalty[i];
    }

    // Input for dorm data
    int numDorms;
    cout << "Enter number of dorms: ";
    cin >> numDorms;

    vector<string> dormNames(numDorms);
    vector<int> numChannels(numDorms);

    cout << "Enter dorm names and number of channels for each dorm:" << endl;
    for (int i = 0; i < numDorms; ++i) {
        cin >> dormNames[i] >> numChannels[i];
    }

    // Allocate inmates to dorms based on sleeping times for each day
    vector<vector<stack<pair<string, int>>>> dormAllocations(numDorms, vector<stack<pair<string, int>>>(7));

    // Process allocation for each day
    for (int day = 0; day < 7; day++) {
        // Map to track dorms' remaining channel capacity for the current day
        vector<int> dormCapacity = numChannels;

        // Sort inmates based on their sleeping time on the current day
        vector<pair<int, int>> inmates;
        for (int i = 0; i < Number_Inmate; i++) {
            inmates.push_back({Day[day][i], i}); // {Sleeping time, Inmate index}
        }
        sort(inmates.begin(), inmates.end());

        // Allocate inmates to dorms based on sleeping times and dorm capacity
        for (const auto& inmate : inmates) {
            int inmateIndex = inmate.second;
            int sleepingTime = inmate.first;
            int inmatePenalty = Penalty[inmateIndex];

            // Find a dorm with available channel capacity for the current day
            int chosenDorm = -1;
            for (int i = 0; i < numDorms; i++) {
                if (dormCapacity[i] > 0) {
                    chosenDorm = i;
                    break;
                }
            }

            // If a dorm is found, allocate the inmate to that dorm for the current day
            if (chosenDorm != -1) {
                dormAllocations[chosenDorm][day].push({Names[inmateIndex], Earpod_ID[inmateIndex]});
                dormCapacity[chosenDorm]--;

                // Consider inmate's penalty (do something with it as needed)
                // For example, you can output the penalty for this inmate and dorm allocation
                cout << "Inmate " << Names[inmateIndex] << " (ID: " << Earpod_ID[inmateIndex] << ") allocated to Dorm " << dormNames[chosenDorm]
                     << " on Day " << day + 1 << " with Penalty: " << inmatePenalty << endl;
            }
        }
    }

    // Output to file (output.txt)
    ofstream outFile("output.txt");

    // Output dorm allocation for each day
    for (int day = 0; day < 7; day++) {
        outFile << "Day " << day + 1 << " Dorm Allocations:" << endl;
        for (int dormIdx = 0; dormIdx < numDorms; dormIdx++) {
            outFile << "Dorm " << dormNames[dormIdx] << " (Channels: " << numChannels[dormIdx] << "):" << endl;
            stack<pair<string, int>>& currentDormStack = dormAllocations[dormIdx][day];
            while (!currentDormStack.empty()) {
                outFile << "- " << currentDormStack.top().first << " (Earpod ID: " << currentDormStack.top().second << ")" << endl;
                currentDormStack.pop();
            }
            outFile << endl;
        }
        outFile << endl;
    }

    // Output dorm data
    outFile << "Dorm Data:" << endl;
    for (int i = 0; i < numDorms; i++) {
        outFile << "Dorm Name: " << dormNames[i] << endl;
        outFile << "Number of Channels: " << numChannels[i] << endl;
        outFile << endl;
    }

    outFile.close();

    cout << "Output has been written to output.txt" << endl;

    return 0;
}
