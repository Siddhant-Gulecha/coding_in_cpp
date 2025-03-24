#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

vector<int> Rabin_Karp_matcher(string T, string P){
    int n = T.length();
    int m = P.length();
    int d = 10;
    int q = 13;
    int p = 0;
    int h = (int)(pow(d,m-1))%q;
    int t = 0;
    vector<int> shifts;

    for(int i=0; i<m; i++){
        p = ((d*p) + P[i])%q;
        t = ((d*t) + T[i])%q;
    }
    cout<<p<<" "<<t<<endl;
    if(p==t){
        shifts.push_back(0);
    }

    for(int s=1; s<n-m+1; s++){

        t = (d * (t - T[s - 1] * h) + T[s + m - 1]) % q;//shifting hash function

        t = (t+q)%q;//in case t is -ve

        if(p==t){

            if(T.substr(s, m) == P){

                shifts.push_back(s);

            }
        }        
    }
    return shifts;
}

void printshifts(vector<int> shifts, string t, string p){
    int m = p.length();
    if(shifts.size()==0){
        cout<<"\nNo Valid Shifts\n";
        return;
    }
    cout<<"\nValid Shifts : \n\n";
    for(int i=0; i<shifts.size(); i++){
        cout<<shifts[i]<<" : ";
        for(int j=0; j<shifts[i]; j++){
            cout<<t[j];
        }cout<<'('<<p<<')';
        for(int j=shifts[i]+m; j<t.length(); j++){
            cout<<t[j];
        }cout<<endl;
    }cout<<endl;
}

int main(){
    string t,p;
    cout<<"enter text : ";
    cin>>t;
    cout<<"enter pattern to search : ";
    cin>>p;

   /*t = "abcabca";
    p = "abca";*/

    //valid shifts
    vector<int> shifts = Rabin_Karp_matcher(t,p);

    //printing valid shifts
    printshifts(shifts, t, p);
}
