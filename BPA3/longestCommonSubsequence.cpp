#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
typedef long long int ll;
  
ll computeLCS(char *string_a, char *string_b, ll m, ll n)  
{  
    int table[m+1][n+1];  
    for (int i = 0; i <= m; i++)  
    {  
        for (int j = 0; j <= n; j++)  
        {  
            if (i == 0 || j == 0)  
                table[i][j] = 0;  
            else if (string_a[i - 1] == string_b[j - 1])  
                table[i][j] = table[i - 1][j - 1] + 1;  
        
            else
                table[i][j] = max(table[i - 1][j], table[i][j - 1]);  
        }  
    }  
    return table[m][n];  
}  

int main() {
    ll t;
    scanf("%lld", &t);
    while(t--)
    {
        ll length1, length2;
        scanf("%lld %lld", &length1, &length2);
        char string_1[length1+1];
        char string_2[length2+1];
        scanf("%s\n%s", string_1, string_2);
        printf("%lld", computeLCS(string_1, string_2, length1, length2));
    }
    return 0;
}
