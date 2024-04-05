#include <bits/stdc++.h>
using namespace std;

class Inmate{
    private:
        string Name;
        int Earpod_ID;
        int arr[7];
        int p;
    public:
        Inmate(){
            cin >> Name >> Earpod_ID;
            for(int i=0;i<6;i++){
                cin >> arr[i];
            }
            cin >> p;
        }
};

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    int Number_Inmate;cin >> Number_Inmate;
    Inmate I1;
    return 0;
}