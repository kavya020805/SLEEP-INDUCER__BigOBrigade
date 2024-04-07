#include<bits/stdc++.h>
using namespace std;

bool compareStacks(const stack<pair<pair<int, int>, string>>& s1, const stack<pair<pair<int, int>, string>>& s2) {
    return s1.size() < s2.size(); // Sort in descending order
}

typedef long long int ll;

int main(){
    int n,m,summ=0;
    cin >> n >> m;
    ll c[m];
    for(int j=0;j<m;j++) {
        cin >> c[j];
        summ += c[j];
    }
    vector<pair<pair<int,int>, string>> a; // Pair of pair<int, int> and string
    for(int i=0;i<n;i++) {
        int x,y;
        string name;
        cin >> x >> y >> name; // Input sleep time (x), channel (y), and name
        a.push_back({{x, y}, name});
    }
    sort(a.begin(),a.end());
    
    vector<stack<pair<pair<int,int>, string>>> v; // Stack of pair of pair<int, int> and string
    v.push_back(stack<pair<pair<int,int>, string>>());
    v.back().push({{a[0].first.first, a[0].first.second}, a[0].second}); // Pushing sleep time, channel, and name
    for(int i=1;i<n;i++) {
        int c=0;
        for(int j=0;j<v.size();j++) {
            if(abs(v[j].top().first.first-a[i].first.first)>=v[j].top().first.second) {
                c++;
                v[j].push({{a[i].first.first, a[i].first.second}, a[i].second});
                break;
            }
        }
        if(c==0) {
            v.push_back(stack<pair<pair<int,int>, string>> ());
            v.back().push({{a[i].first.first, a[i].first.second}, a[i].second});
        }
    }
    sort(v.begin(), v.end(), compareStacks);
    int x = v.size();
    cout << x << " " << summ << endl;
    int j = 0;
    if(x > summ) {
        cout << "Not possible\n";
    }
    else {
        for(int i=0;i<m;i++) {
            cout << "dorm " << i+1 << " " << endl;
            int tmp1 = 0;
            while(c[i]--) {
                cout << "Channel-" << tmp1+1 << ": ";
                tmp1++;
                while(!v[j].empty()) {
                    cout << v[j].top().second << " ";
                    v[j].pop();
                }
                j++;
                cout << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
