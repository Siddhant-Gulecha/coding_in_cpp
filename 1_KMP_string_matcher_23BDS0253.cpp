#include<iostream>
#include<vector>
using namespace std;

void printvec(string p, vector<int> vec){
    for(char c:p){
        cout<<c<<" ";
    }cout<<endl;
    for(auto x:vec){
        cout<<x<< " ";
    }cout<<"\n\n";
}

vector<int> compute_prefix_function(string p){
    int m = p.length();
    vector<int> phi(m);
    int k = 0;
    phi[0] = 0;
    for(int q = 1; q<m; q++){
        while(k>0 && p[k] != p[q]){
            k = phi[k];
        }
        if(p[k] == p[q]){
            k++;
        }
        phi[q] = k;
    }
    return phi;
}

vector<int> KMP_matcher(string t, string p){
    //prefix function
    vector<int> phi = compute_prefix_function(p);
    cout<<"\nprefix table : \n\n";
    printvec(p,phi);
    vector<int> shifts;
    int n = t.length();
    int m = p.length();
    int q = 0;
    for(int i=0; i<n; i++){
        while(q>0 && p[q] != t[i]){
            q = phi[q-1];
        }
        if(p[q]==t[i]){
            q++;
            if(q==m){
                shifts.push_back(i-m+1);
                q = phi[q-1];
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
    vector<int> shifts = KMP_matcher(t,p);

    //printing valid shifts
    printshifts(shifts, t, p);



}