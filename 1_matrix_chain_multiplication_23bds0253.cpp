#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;
// can verify ans at : https://www.mimuw.edu.pl/~erykk/algovis/mcm.htmlhttps://www.mimuw.edu.pl/~erykk/algovis/mcm.html

void print_expression(vector<vector<int>> &m,int s, int e){
    if(s==e){
        cout<<'A'<<s+1<<"";
        return;
    }
    int op = m[e][s];
    cout<<"( ";
    print_expression(m,s,op);
    cout<<" . ";
    print_expression(m,op+1,e);
    cout<<" )";
}

void printvec(vector<int> vec){
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

int main(){

    int n;cout<<"enter the number of matrices :";cin>>n; 

    vector<int> dimensions;

    int temp;

    cout<<"enter dimensions of first matrix (m n) : ";
    cin>>temp;dimensions.push_back(temp);
    cin>>temp;dimensions.push_back(temp);

    for(int i=0; i<n-1; i++){
        cout<<"enter dimensions of next matrix : "<<temp<<" x ";
        cin>>temp;
        dimensions.push_back(temp);
    }
    //input OK

    //DP table
    vector<vector<int>> m(n,vector<int>(n));
    //if m[i][j] is no of mult op, then m[j][i] is last multiplication op
    //given i<j

    //no of matrices multiplied from 2 to n [a1,a2] [a1,a2,a3] etc

    for(int i=2; i<=n; i++){

        //each subproblem [a1,a2,a3] [a2,a3,a4] [a3,a4,a5] etc

        for(int j=0; j<=n-i; j++){
            
            int min_operations = INT_MAX;
            int min_operator = 0;

            //each operator of subproblem [(a1).(a2,a3,a4)] [(a1,a2).(a3,a4)] [(a1,a2,a3).(a4)] etc 

            for(int k=j; k<j+i-1; k++){
                int operations = m[j][k] 
                    + dimensions[j]*dimensions[k+1]*dimensions[j+i] 
                    + m[k+1][j+i-1];

                if(operations < min_operations){
                    min_operations = operations;
                    min_operator = k;
                }
            }
           
            m[j][j+i-1] = min_operations;
            m[j+i-1][j] = min_operator; 
        }
        
    }
    //printvec(m);
    cout<<"\noptimal way to multiply this chain of matrices is :\n\n";
    print_expression(m,0,n-1);
    cout<<endl<<endl;
    cout<<"minimum cost : "<<m[0][n-1]<<endl;
}