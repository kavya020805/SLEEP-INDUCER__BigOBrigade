


#include<bits/stdc++.h>
using namespace std;

bool compareStacks(const stack<pair<int, int>>& s1, const stack<pair<int, int>>& s2) {
    return s1.size() < s2.size(); // Sort in descending order
}

typedef long long int ll;
int main(){
    int n,m,summ=0;
    cin >> n >> m;
    ll c[m];
    for(int j=0;j<m;j++)
    {
        cin >> c[j];
        summ+=c[j];
    }
    vector<pair<int,int>> a;
    for(int i=0;i<n;i++)
    {
        int x,y;
        cin >>x>>y;
        a.push_back({x,y});
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
            cout << "dorm " << i+1 << " ";
        while(c[i]--)
        {
            while(!v[j].empty())
            {
                cout << v[j].top().first << " ";
                v[j].pop();
            }
            j++;
        }
        cout << endl;
    }
    }
    


    return 0;
}















