#include <iostream>
#include <vector>
#include <climits>
using namespace std;

void maxCrossingSum(vector<int>& arr, int l, int m, int h, int &maxSum, int &start, int &end) {
    int sum = 0;
    int leftSum = INT_MIN;
    int leftStart = m;
    
    for (int i = m; i >= l; i--) {
        sum += arr[i];
        if (sum > leftSum) {
            leftSum = sum;
            leftStart = i;
        }
    }

    sum = 0;
    int rightSum = INT_MIN;
    int rightEnd = m + 1;
    
    for (int i = m + 1; i <= h; i++) {
        sum += arr[i];
        if (sum > rightSum) {
            rightSum = sum;
            rightEnd = i;
        }
    }

    maxSum = leftSum + rightSum;
    start = leftStart;
    end = rightEnd;
}

void MaxSum(vector<int>& arr, int l, int h, int &maxSum, int &start, int &end) {
    if (l > h) {
        maxSum = INT_MIN;
        start = -1;
        end = -1;
        return;
    }

    if (l == h) {
        maxSum = arr[l];
        start = l;
        end = l;
        return;
    }

    int m = l + (h - l) / 2;

    int leftMaxSum, leftStart, leftEnd;
    int rightMaxSum, rightStart, rightEnd;
    int crossMaxSum, crossStart, crossEnd;

    MaxSum(arr, l, m, leftMaxSum, leftStart, leftEnd);
    MaxSum(arr, m + 1, h, rightMaxSum, rightStart, rightEnd);
    maxCrossingSum(arr, l, m, h, crossMaxSum, crossStart, crossEnd);

    if (leftMaxSum >= rightMaxSum && leftMaxSum >= crossMaxSum) {
        maxSum = leftMaxSum;
        start = leftStart;
        end = leftEnd;
    } else if (rightMaxSum >= leftMaxSum && rightMaxSum >= crossMaxSum) {
        maxSum = rightMaxSum;
        start = rightStart;
        end = rightEnd;
    } else {
        maxSum = crossMaxSum;
        start = crossStart;
        end = crossEnd;
    }
}

int maxSubarraySum(vector<int>& arr, int &start, int &end) {
    int maxSum;
    MaxSum(arr, 0, arr.size() - 1, maxSum, start, end);
    return maxSum;
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int start, end;
    int maxSum = maxSubarraySum(arr, start, end);

    // Display the maximum sum
    cout << "Max Sum: " << maxSum << endl;
    cout<<"subarray index : "<<start<<" to "<<end<<endl;
    
    // Display the subarray
    cout << "Subarray: ";
    for (int i = start; i <= end; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
