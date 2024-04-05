#include <bits/stdc++.h>
using namespace std;

int Number_Inmate;

class Inmate {
private:
    vector<string> Names;
    vector<int> Earpod_ID;
    vector<int> Day1;
    vector<int> Day2;
    vector<int> Day3;
    vector<int> Day4;
    vector<int> Day5;
    vector<int> Day6;
    vector<int> Day7;
    vector<int> p;

public:
    Inmate() {
        Names.resize(Number_Inmate);
        Earpod_ID.resize(Number_Inmate);
        Day1.resize(Number_Inmate);
        Day2.resize(Number_Inmate);
        Day3.resize(Number_Inmate);
        Day4.resize(Number_Inmate);
        Day5.resize(Number_Inmate);
        Day6.resize(Number_Inmate);
        Day7.resize(Number_Inmate);
        p.resize(Number_Inmate);
    }

    void input() {
        for(int i = 0; i < Number_Inmate; i++) {
            cin >> Names[i] >> Earpod_ID[i];
            cin >> Day1[i] >> Day2[i] >> Day3[i] >> Day4[i] >> Day5[i] >> Day6[i] >> Day7[i];
            cin >> p[i];
        }
    }

    void output() {
        for(int day = 1; day <= 7; day++) {
            vector<int> indices(Number_Inmate);
            iota(indices.begin(), indices.end(), 0);

            sort(indices.begin(), indices.end(), [&](int a, int b) {
                switch(day) {
                    case 1: return Day1[a] < Day1[b];
                    case 2: return Day2[a] < Day2[b];
                    case 3: return Day3[a] < Day3[b];
                    case 4: return Day4[a] < Day4[b];
                    case 5: return Day5[a] < Day5[b];
                    case 6: return Day6[a] < Day6[b];
                    case 7: return Day7[a] < Day7[b];
                    default: return false;
                }
            });

            cout << "Day " << day << ":" << endl;
            for(int i = 0; i < Number_Inmate; i++) {
                int idx = indices[i];
                cout << Names[idx] << ' ' << Earpod_ID[idx] << ' ';
                switch(day) {
                    case 1: cout << Day1[idx]; break;
                    case 2: cout << Day2[idx]; break;
                    case 3: cout << Day3[idx]; break;
                    case 4: cout << Day4[idx]; break;
                    case 5: cout << Day5[idx]; break;
                    case 6: cout << Day6[idx]; break;
                    case 7: cout << Day7[idx]; break;
                }
                cout << ' ' << p[idx] << endl;
            }
            cout << endl;
        }
    }
};

int main() {
    freopen("TestData1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    cin >> Number_Inmate;
    cout << Number_Inmate << endl;

    Inmate INMATE;
    INMATE.input();
    INMATE.output();

    return 0;
}
