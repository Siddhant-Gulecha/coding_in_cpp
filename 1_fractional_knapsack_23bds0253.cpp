#include <iostream>
#include<cstdio>
using namespace std;
void swap(string *a, string *b){
    string temp = *a;
    *a = *b;
    *b = temp;
}
void swap(double *a, double *b){
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
void swap(int*a, int *b){
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

//fractional knapsack w/greedy approach

int main(){
    int n,W;
    string names[100];
    int weights[100];
    int profits[100];
    double ratio[100];
    char name_buffer[100];
    double taken[100];

    //input
    cin>>n;
     // Read the number of items
    for (int i = 0; i < n; i++) {

        scanf("%s %d %d", name_buffer, &weights[i], &profits[i]);
        names[i] = string(name_buffer); // Convert C-string to std::string

    }

    cin>>W;

    //calculation of price to weight ratio
    for(int i=0; i<n; i++){
        ratio[i] = profits[i]/(float)weights[i];
    }

    int w = 0;
    double value = 0;
    int j=0;
    
    //finding max value product
    while(w<W && j<n){
        int max = 0;
        for(int i=1; i<n-j; i++){
            if(ratio[i]>ratio[max]){
                max = i;
            }
        }
        swap(&ratio[n-j-1],&ratio[max]);
        swap(&weights[n-j-1],&weights[max]);
        swap(names[n-j-1],names[max]);

        if(w+weights[n-j-1]>W){
            double taken_ratio = (W-w)/(double)weights[n-j-1];
            w = W;
            value+=profits[n-j-1]*taken_ratio;
            taken[n-j-1] = taken_ratio;
            cout<<names[n-j-1]<<" ("<<taken[n-j-1]*100<<"%) : "<<profits[n-j-1]*taken[n-j-1]<<endl;
            j++;
            break;
        }
        else{
            w+=weights[n-j-1];
            value+=profits[n-j-1];
            taken[n-j-1] = 1;
            cout<<names[n-j-1]<<" (100%) : "<<profits[n-j-1]*taken[n-j-1]<<endl;
        }
        j++;
    }
    cout<<"total value: "<<value<<endl;
    cout<<"total weight: "<<w<<endl;
}