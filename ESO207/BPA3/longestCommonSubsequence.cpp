#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
using namespace std;
typedef long long int ll;
  
ll computeLCS(char *string_a, char *string_b, ll length_1, ll length_2)  
{  
    int dp_previous[length_2+1] = {0};
    int dp_current[length_2+1] = {0};
    for (int i = 0; i <= length_1; i++)  
    {  
        for (int j = 0; j <= length_2; j++)  
        {  
            if (i == 0 || j == 0)  
                dp_current[j]=0;
            else if (string_a[i-1] == string_b[j-1])  
                dp_current[j] = dp_previous[j-1]+1;
        
            else
                dp_current[j] = max(dp_current[j-1], dp_previous[j]);
        }  
        for(int j=0;j<=length_2;j++)
            dp_previous[j] = dp_current[j];
    }  
    return dp_current[length_2];
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
        printf("%lld\n", computeLCS(string_1, string_2, length1, length2));
    }
    return 0;
}
