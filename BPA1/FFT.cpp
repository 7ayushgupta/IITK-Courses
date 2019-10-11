#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <complex>
using namespace std;

typedef long long int ll;
typedef pair<double, double> comp;
typedef vector<comp> polynomial;

comp product(comp a, comp b)
{
    comp result;
    result.first = (a.first)*(b.first)-(a.second)*(b.second);
    result.second = (a.first)*(b.second)+(a.second)*(b.first);
    return result;
}

comp sum(comp a, comp b)
{
    comp result;
    result.first = a.first + b.first;
    result.second = a.second + b.second;
    return result;
}

comp subtract(comp a, comp b)
{
    comp result;
    result.first = a.first - b.first;
    result.second = a.second - b.second;
    return result;
}

ll logarithm_base2(ll n)
{
    ll c = 0;
    while(pow(2, c)<n)
        c++;
    return c;
}
polynomial recursiveFFT(polynomial a)
{
    ll n = a.size();
    if(n==1)   
        return a;
    else
    {
        polynomial a_odd, y_odd, a_even, y_even;
        for(ll i = 0; i<=n/2-1; i++)
        {
            a_even.push_back(make_pair(a[2*i].first, a[2*i].second));
            a_odd.push_back(make_pair(a[2*i+1].first, a[2*i+1].second)); 
        }
        
        y_odd = recursiveFFT(a_odd);
        y_even = recursiveFFT(a_even);
        polynomial y(n+1);
        comp omega_n(cos(2*M_PI/n), sin(2*M_PI/n));
        comp omega(1,0);
        for(ll i=0; i<=n/2-1; i++)
        {
            y[i]=sum(y_even[i], product(omega, y_odd[i]));
            y[i+n/2]=subtract(y_even[i], product(omega, y_odd[i]));
            omega = product(omega, omega_n);
        }
        return y;  
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    ll t;
    cin>>t;
    while(t--)
    {
        ll n;
        cin>>n;
        ll log_pow = logarithm_base2(n);
        //cout<<log_pow<<endl;
        ll N = pow(2, log_pow);
        polynomial input_poly, output_poly;
        for(ll i = 0; i<n; i++)
        {
            comp input;
            cin>>input.first>>input.second;
            input_poly.push_back(input);
        }
        input_poly.resize(N);
        output_poly = recursiveFFT(input_poly);
        for(ll i = 0; i<N; i++)
            printf("(%0.3f,%0.3f)\n",output_poly[i].first, output_poly[i].second);
    }
    return 0;
}