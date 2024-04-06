


#include<bits/stdc++.h>
using namespace std;

typedef long long int ll;
int main(){
    int n,m;
    cin >> n >> m;
    ll a[n];
    for(int i=0;i<n;i++)
    {
        cin >> a[i];
    }
    sort(a,a+n);
    int p,c=0;
    cin >> p;
    vector<stack<int>> v;
    v.push_back(stack<int>());
    v.back().push(a[0]);
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<v.size();j++)
        {
            if(abs(v[j].top()-a[i])>=p)
            {
                c++;
                v[j].push(a[i]);
                break;
            }
        }
        if(c==0)
        {
            v.push_back(stack<int> ());
            v.back().push(a[i]);
        }
    }
    cout << v.size() << endl;
    for(int i=0;i<v.size();i++)
    {
        cout << "dorm " << i+1 << " ";
        while(!v[i].empty())
        {
            cout << v[i].top() << " ";
            v[i].pop();
        }
        cout << endl;
    }


    return 0;
}















