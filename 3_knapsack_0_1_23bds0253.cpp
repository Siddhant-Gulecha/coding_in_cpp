#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


void printvec(vector<int> vec){
    for(auto x:vec){
        cout<<x<<" ";
    }cout<<endl;
}

void printvec(vector<string> vec){
    for(auto x:vec){
        cout<<x<<" ";
    }cout<<endl;
}

void printvec(vector<vector<int>> vec){
    for(auto x:vec){
        for(auto y:x){
            cout<<y<<" ";
        }
        cout<<endl;
    }
}
void printvec(vector<bool> v){
    cout<<"{ ";
    for(auto x:v){
        if(x)cout<<"1 ";
        else cout<<"0 ";
    }cout<<"}\n";
}


void get_taken_info_recursive(vector<bool> &taken, vector<vector<int>> &dp, vector<int> &weights, int i, int j){
    if(i==0||j==0){
        return;
    }
    if(j-weights[i-1]<0 || dp[i][j] == dp[i-1][j]){
        taken[i-1] = false;
        get_taken_info_recursive(taken,dp,weights,i-1,j);
    }else{
        taken[i-1] = true;
        get_taken_info_recursive(taken,dp,weights,i-1,j-weights[i-1]);
    }
}

void get_taken_info(vector<bool> &taken, vector<vector<int>> &dp, vector<int> &weights){
    get_taken_info_recursive(taken,dp,weights,dp.size()-1,dp[0].size()-1);
}
void O_1_knapsack(vector<vector<int>> &dp, vector<int> &weights, vector<int> &profits){
    int W = dp[0].size() - 1;
    int n = dp.size() - 1;
    for(int i=0; i<=n; i++){
        for(int j=0; j<=W; j++){
            if(i==0 || j==0){
                dp[i][j] = 0;
                continue;
            }
            if(weights[i-1] > j){//cant add item in knapsack
                dp[i][j] = dp[i-1][j];
                continue;
            }
            int value_if_taken = profits[i-1] + dp[i-1][j - weights[i-1]];
            int value_if_not_taken = dp[i-1][j];
            dp[i][j] = max(value_if_taken,value_if_not_taken);
        }
    }
}

int main(){
    cout<<"\n23bds0253 | Siddhant Gulecha \n\n\n";
    int W;cout<<"enter max weight of knapsack(W) : ";cin>>W;
    int n;cout<<"enter number of items : ";cin>>n;

    vector<int> weights(n);
    vector<int> profits(n);
    vector<string> names(n);

    cout<<"enter name value and weight of "<<n<<" items : "<<endl;
    for(int i=0; i<n; i++){
        cin>>names[i]>>profits[i]>>weights[i];
    }

    vector<vector<int>> dp(n+1,vector<int>(W+1));

    O_1_knapsack(dp,weights,profits);

    cout<<"\nmax profit : "<<dp[n][W]<<endl;

    vector<bool> taken(n);
    get_taken_info(taken,dp,weights);

    printvec(taken);

    cout<<"\nnames of items taken : \n";

    for(int i=0; i<n; i++){
        if(taken[i]){
            cout<<names[i]<<" "<<profits[i]<<endl;
        }
    }
    //printvec(dp);
}