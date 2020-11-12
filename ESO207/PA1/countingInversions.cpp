#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
typedef long long int ll;

ll mergeSort(ll arr[], ll n, ll left, ll mid, ll right)
{
    ll local[n], p, q, r, local_count = 0;
    p = r = left, q = mid;
    while((p<mid) && q<right+1)
    {
        if(arr[p]<=arr[q])
            local[r++] = arr[p++];  
        else
        {
            local[r++] = arr[q++];
            local_count+=mid-p;
        }
            
    }
    while(p<mid) local[r++]=arr[p++];
    while(q<right+1) local[r++]=arr[q++];
    for(ll i = left; i<=right; i++)
        arr[i] = local[i];
    return local_count;
}

ll countInversion(ll arr[], ll n, ll left, ll right)
{
    ll mid = (right+left)/2;
    if(right > left)
        return countInversion(arr, n, left, mid) + countInversion(arr, n, mid+1,right) + mergeSort(arr, n, left, mid+1, right);
    else 
        return 0;
}

int main() {
    int t;
    cin >> t;
    while(t--)
    {
        ll n;
        cin>>n;
        ll arr[n];
        for(ll i=0; i<n; i++)
            cin>>arr[i];
        cout<<countInversion(arr, n, 0, n-1)<<endl;
    }
    return 0;
}
