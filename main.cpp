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

class Dorm{
    private:
        string name;
        int no_of_channel;
        int capacity;
        string *str;
    public:
        Dorm(int n , int  m){
            capacity=ceil((n*(1.0))/m);
            cin >> name >> no_of_channel;
            str= new string [capacity];
        }
        private:

};

int main(){
    freopen("data.txt","r",stdin);
    freopen("output.txt","w",stdout);
    
    int Number_Inmate;cin >> Number_Inmate;
    Inmate I1[Number_Inmate];
    int Number_of_Dorm;
    cin >> Number_of_Dorm;
    Dorm D1[Number_of_Dorm];
    

    return 0;
}