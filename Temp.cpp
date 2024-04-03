#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Inmate {
public:
    string name;
    int id;
    int sleepTime;
    int p;
};

class Dorm {
public:
    string name;
    // Assuming sets for music channels and music
};

bool compareInmatesBySleepTime(const Inmate& inmate1, const Inmate& inmate2) {
    return inmate1.sleepTime < inmate2.sleepTime;
}

int main() {
    int N, M, p;
    cout << "Enter the number of inmates (N): ";
    cin >> N;
    cout << "Enter the number of dorms (M): ";
    cin >> M;
    cout << "Enter the sleep time threshold increment (p): ";
    cin >> p;

    vector<Inmate> inmates(N);
    // Input inmate details from a text file
    ifstream infile("inmates.txt");
    for (int i = 0; i < N; ++i) {
        infile >> inmates[i].name >> inmates[i].id >> inmates[i].sleepTime >> inmates[i].p;
    }
    infile.close();

    vector<Dorm> dorms(M);
    // Input dorm details
    for (int i = 0; i < M; ++i) {
        cout << "Enter name of dorm " << i + 1 << ": ";
        cin >> dorms[i].name;
        // Input other attributes of dorms
    }

    sort(inmates.begin(), inmates.end(), compareInmatesBySleepTime);

    int dormIndex = 0;
    int lastAssignedTime = 0;
    int assignedInmatesCount = 0;

    while (assignedInmatesCount < N && dormIndex < M) {
        Dorm& currentDorm = dorms[dormIndex];
        for (int i = 0; i < N; ++i) {
            if (inmates[i].sleepTime >= lastAssignedTime + p) {
                cout << "Assigning " << inmates[i].name << " to " << currentDorm.name << " dorm." << endl;
                lastAssignedTime = inmates[i].sleepTime;
                assignedInmatesCount++;
            }
        }
        dormIndex++;
    }

    if (assignedInmatesCount < N) {
        int additionalDorms = N - assignedInmatesCount;
        cout << "Minimum number of additional dorms required: " << additionalDorms << endl;
    }

    return 0;
}
