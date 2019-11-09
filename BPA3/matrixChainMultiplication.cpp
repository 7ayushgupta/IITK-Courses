#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
typedef long long int ll;
  
ll computeMatrixOrder(ll order[], ll length)
{  
    ll table[length][length], j;
    for(ll i = 1; i<length; i++) table[i][i] = 0;
    for(ll chain = 2; chain<length; chain++)
        for(ll i = 1; i<length-chain+1; i++)
            for(j = i, table[i][i+chain-1] = __INT_MAX__; j<=i+chain-2; j++)
                table[i][i+chain-1] = min(table[i][j] + table[j+1][i+chain-1] + order[i-1]*order[j]*order[i+chain-1], table[i][i+chain-1]); 
    return table[1][length-1];
}  

int main() {
    ll t;
    scanf("%lld", &t);
    while(t--)
    {
        ll length;
        scanf("%lld", &length);
        ll arr[length+1];
        for(int i = 0; i<length+1; i++)
            scanf("%lld", &arr[i]);
        printf("%lld\n", computeMatrixOrder(arr, length+1));
    }
    return 0;
}