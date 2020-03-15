#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>

using namespace std;
typedef long long int ll;

ll eleSearch(ll array[], ll left, ll right, ll key)
{
    ll mid = (left + right)/2;
    if(left > right) return -1;
    if(array[mid] == key) return mid;
    if(array[left]<=array[mid])
    {
        if(array[left]<=key && array[mid]>=key)
            return eleSearch(array, left, mid-1, key);
        else
            return eleSearch(array, mid+1, right, key);
    }
    else
    {
        if(array[mid]<=key && array[right]>=key)
            return eleSearch(array, mid+1, right, key);
        else
            return eleSearch(array, left, mid-1, key);
    }
}

int main() {
    int t;
    cin>>t;
    while(t--)
    {
        ll n, i, j, ans;
        cin>>n;
        ll arr[n], k;
        for(i = 0; i<n; i++)
            cin >> arr[i];
        cin>>k;
        cout<<eleSearch(arr, 0, n-1, k)<<endl; 
    }
    return 0;
}