


#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
int main(){
    int n,m;
    cin >> n >> m;
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
    cout << v.size() << endl;
    for(int i=0;i<v.size();i++)
    {
        cout << "dorm " << i+1 << " ";
        while(!v[i].empty())
        {
            cout << v[i].top().first << " ";
            v[i].pop();
        }
        cout << endl;
    }


    return 0;
}















