#include<iostream>
#include<stdio.h>
#include<cmath>
#include<string>

using namespace std;
int nextPowerOfTwo(int n)
{
    return pow(2, ceil(log2(n)));
}

string addBitStrings(string first, string second)
{
    string result;  // To store the sum bits

    // make the lengths same before adding
    int length = first.length();
    int carry = 0;  // Initialize carry

    for (int i = length - 1; i >= 0; i--)
    {
        int firstDigit = first.at(i) - '0';
        int secondDigit = second.at(i) - '0';

        int sum = (firstDigit + secondDigit + carry);
        carry = 0;
        if(sum>9){
            sum-=10;
            carry = 1;
        }
        result = (char)(sum+(int)'0') + result;

    }

    if (carry) result = '1' + result;
    while(result.length()<length){result = '0'+result;}
    return result;
}



int multiplySingleBit(string a, string b)
{
    return (a[0] - '0') * (b[0] - '0');
}

int multiply(string X, string Y)
{
    int max_len = max(X.size(), Y.size());
    
    // If the size is not a power of 2, pad with zeros
    int next_power_of_2 = nextPowerOfTwo(max_len);

    while (X.size() < next_power_of_2) X = '0' + X;
    while (Y.size() < next_power_of_2) Y = '0' + Y;
    

    int n = X.length();

    // Base cases
    
    if (n == 0) return 0;
    if (n == 1) return multiplySingleBit(X, Y);

    int half = n>>1; 


    string Xl = X.substr(0, half);
    string Xr = X.substr(half, n);

    string Yl = Y.substr(0, half);
    string Yr = Y.substr(half, n);

    long int a = multiply(Xl, Yl);
    long int d = multiply(Xr, Yr);
    long int e = multiply(addBitStrings(Xl, Xr), addBitStrings(Yl, Yr))-a-d;

    return a * (pow(10,n)) + (e)*(pow(10,n>>1)) + d;
}

// Function to find the next power of 2 greater than or equal to the number length


int main()
{
    string a, b;

cout << "Enter two numbers to multiply: ";
    cin >> a >> b;

    int max_len = max(a.size(), b.size());
    
    // If the size is not a power of 2, pad with zeros
    int next_power_of_2 = nextPowerOfTwo(max_len);

    while (a.size() < next_power_of_2) a = '0' + a;
    while (b.size() < next_power_of_2) b = '0' + b;

    cout << "Modified numbers (padded to nearest power of 2 length):" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;


    long int result = multiply(a, b);
    cout << "Product = " << result << endl;

    return 0;
}
