#include<iostream>
#include<vector>
using namespace std;

void printvec(vector<vector<bool>> vec){
    for(auto x:vec){
        for(auto y:x){
            cout<<(y?'Q':'.');
        }
        cout<<endl;
    }cout<<endl;
}

void N_Queens(int n,vector<vector<vector<bool>>> &valid_boards,vector<vector<bool>> &chessboard,vector<bool> &col, vector<bool>&d1, vector<bool>&d2, int current_row){
    if(current_row==n){
        valid_boards.push_back(chessboard);
        return;
    }

    for(int i=0; i<n; i++){
        if(col[i] == false && d1[i+current_row] == false && d2[n-i-1+current_row] == false ){//is safe

            chessboard[current_row][i] = true;col[i] = true;d1[i+current_row] = true;d2[n-i-1+current_row] = true;

            N_Queens(n,valid_boards,chessboard,col,d1,d2,current_row+1);

            chessboard[current_row][i] = false;col[i] = false;d1[i+current_row] = false;d2[n-i-1+current_row] = false;
        }
    }
}

int main(){
    cout<<"\n23bds0253 | Siddhant Gulecha \n\n\n";

    int n;cout<<"enter value of n : ";cin>>n;
    if(n==0){
        cout<<"no solutions"<<endl;
        return 1;
    }
    vector<vector<vector<bool>>> valid_boards;
    vector<vector<bool>> chessboard(n,vector<bool>(n));

    vector<bool> col(n);
    vector<bool> d1(2*n - 1);//diagonals of positive slope /
    vector<bool> d2(2*n - 1);//diagonals of -ve slope \;


    N_Queens(n,valid_boards,chessboard,col,d1,d2,0);
    cout<<"number of solutions : "<<valid_boards.size()<<endl<<endl;
    for(int i=0; i<valid_boards.size(); i++){
        cout<<i+1<<"."<<endl;
        printvec(valid_boards[i]);
        cout<<endl;
    }
}
