#include <bits/stdc++.h>
using namespace std;

bool compareStacks(const stack<pair<int, int>>& s1, const stack<pair<int, int>>& s2) {
    return s1.size() < s2.size(); 
}

class Inmate{
    private:
        string name;
        int EarpodId;
        int time;
        int p;
    public:
        Inmate(string n,int i,int t,int pt):name(n), EarpodId(i), time(t),p(pt){}
        string getName()
        {
            return name; 
        }
        int getEarpodId() 
        { 
            return EarpodId; 
        }
        int getSleepTime()
        { 
            return time; 
        }
        int getTimeToFallAsleep()
        { 
            return p; 
        }
    
};

int main(){
    int n,m,summ=0;
    cin >> n >> m;
    int c[m];
    for(int j=0;j<m;j++)
    {
        cin >> c[j];
        summ+=c[j];
    }
    ifstream file("input.csv");

    if (!file.is_open()) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }
    // string Line;
    // getline(file, Line);
    // stringstream ss(Line);
    // char comma;
    // int n, m;
    // ss >> n >> comma >> m;
    // vector<int> mIntegers(m);
    // for (int i = 0; i < m; ++i) {
    //     ss >> comma >> mIntegers[i];
    // }
    vector<vector<string>> data;

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        vector<string> row;

        while (getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        data.push_back(row);
    }

    file.close();

    vector<vector<Inmate>> inmates;

    for (const auto& row : data) {
        string name = row[0];
        int earpodId = stoi(row[1]);
        int time = stoi(row[2]);
        int p = stoi(row[3]);

        vector<Inmate> dorm;
        dorm.push_back(Inmate(name, earpodId, time, p));
        inmates.push_back(dorm);
    }
    vector<pair<int,int>> a;
    

    for (auto& dorm : inmates) {
        for (Inmate& inmate : dorm) {
            a.push_back({inmate.getSleepTime(),inmate.getTimeToFallAsleep()});
        }
    }
    sort(a.begin(),a.end());
    vector<stack<pair<int,int>>> v;
    v.push_back(stack<pair<int,int>>());
    v.back().push({a[0].first,a[0].second});
    for(int i=1;i<n;i++)
    {
        int c=0;
        for(int j=0;j<v.size();j++)
        {
            if(abs(v[j].top().first-a[i].first)>=v[j].top().second)
            {
                c++;
                v[j].push({a[i].first,a[i].second});
                break;
            }
        }
        if(c==0)
        {
            v.push_back(stack<pair<int,int>> ());
            v.back().push({a[i].first,a[i].second});
        }
    }
    sort(v.begin(), v.end(), compareStacks);
    int x=v.size();
    cout << x << " " << summ << endl;
    int j=0;
    if(x>summ)
    {
        cout << "Not possible\n";
    }
    else
    {
    for(int i=0;i<m;i++)
    {
            cout << "dorm " << i+1 << " \n";
            int k=1;
        while(c[i]--)
        {
            
            cout << "Channel " << k << ": ";
            if(j==v.size())
            break;
            while(!v[j].empty())
            {
                cout << v[j].top().first << " ";
                v[j].pop();
            }
            j++;
            k++;
            cout << endl;
            
        }
        cout << endl;
        
    }
    }
    


    return 0;
}
