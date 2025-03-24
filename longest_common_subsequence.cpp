#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;


void printset(unordered_set<string> vec){
    unordered_set<string>::iterator itr = vec.begin();
    while(itr != vec.end()){
        cout<<*itr<<endl;
        itr++;
    }cout<<endl;
}

void getallsubsequencesrecursive(unordered_set<string> &ans, vector<vector<int>> &dirn, string s1, string s2, int i, int j,string temp){
    if(i==0 || j==0){
        ans.insert(temp);
        return;
    }
    else if(dirn[i][j] == 0){//up
        getallsubsequencesrecursive(ans,dirn,s1,s2,i-1,j,temp);
    }
    else if(dirn[i][j] == 1){//top left
        getallsubsequencesrecursive(ans,dirn,s1,s2,i-1,j-1,s1[i-1]+temp);
    }
    else if(dirn[i][j] == 2){//left
        getallsubsequencesrecursive(ans,dirn,s1,s2,i,j-1,temp);
    }
    else{//left and up
        getallsubsequencesrecursive(ans,dirn,s1,s2,i,j-1,temp);
        getallsubsequencesrecursive(ans,dirn,s1,s2,i-1,j,temp);
    }
}

void getallsubsequences(unordered_set<string> &ans, vector<vector<int>> &dirn, string s1, string s2){
    getallsubsequencesrecursive(ans,dirn,s1,s2,s1.length(),s2.length(),"");
}

void longest_common_subsequence_DP(string s1, string s2, vector<vector<int>> &dp, vector<vector<int>> &dirn){
    for(int i=0; i<s1.length(); i++){
        for(int j=0; j<s2.length(); j++){
            if(s1[i] == s2[j]){
                dp[i+1][j+1] = dp[i][j] + 1;
                dirn[i+1][j+1] = 1;
                continue;
            }
            if(dp[i+1][j] == dp[i][j+1]){//both equal
                dp[i+1][j+1] = dp[i+1][j];
                dirn[i+1][j+1] = 3;
                continue;
            }
            if(dp[i+1][j] > dp[i][j+1]){//left greater
                dp[i+1][j+1] = dp[i+1][j];
                dirn[i+1][j+1] = 2;
                continue;
            }
            //top greater
            dp[i+1][j+1] = dp[i][j+1];
            dirn[i+1][j+1] = 0;
        }
    }
}

int main(){
    //input
    string s1,s2;
    cout<<"enter first string : ";
    cin>>s1;
    cout<<"enter second string : ";
    cin>>s2;

    //declaration of dp table and dirn table
    vector<vector<int>> dp(s1.length()+1,vector<int>(s2.length()+1));
    vector<vector<int>> dirn(s1.length()+1,vector<int>(s2.length()+1));
    //0 for up, 1 for top left, 2 for left, 3 for both left and up simultaneously

    //function call
    longest_common_subsequence_DP(s1,s2,dp,dirn);

    //ans to store strings
    unordered_set<string> ans;
    //function call to extract all subsequences
    getallsubsequences(ans,dirn,s1,s2);

    //cout
    cout<<"\nlongest subsequence length : "<<dp[s1.length()][s2.length()]<<endl<<endl;
    cout<<"strings:\n";
    printset(ans);

}
