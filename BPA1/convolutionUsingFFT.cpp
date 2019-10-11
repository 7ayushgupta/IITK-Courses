#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <complex>

using namespace std;
#define PI (long double)acos(-1.0)
typedef long long int ll;
typedef pair<long double, long double> comp;
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

comp divide(comp a, long double n)
{
    comp result;
    result.first = a.first/n;
    result.second = a.second/n;
    return result;
}

polynomial dot_product(polynomial a, polynomial b)
{
    polynomial result;
    for(ll i = 0; i<a.size(); i++)
        result.push_back(product(a[i], b[i]));
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
        polynomial y(n);
        comp omega_n((long double)cos(2*PI/n), (long double)sin(2*PI/n));
        comp omega(1.0L,0.0L);
        for(ll i=0; i<=n/2-1; i++)
        {
            y[i]=sum(y_even[i], product(omega, y_odd[i]));
            y[i+n/2]=subtract(y_even[i], product(omega, y_odd[i]));
            omega = product(omega, omega_n);
        }
        return y;  
    }
}

polynomial recursiveInvFFT(polynomial y)
{
    ll n = y.size();
    if(n==1)   
        return y;
    else
    {
        polynomial a_odd, y_odd, a_even, y_even;
        for(ll i = 0; i<=n/2-1; i++)
        {
            y_even.push_back(make_pair(y[2*i].first, y[2*i].second));
            y_odd.push_back(make_pair(y[2*i+1].first, y[2*i+1].second)); 
        }
        
        a_odd = recursiveInvFFT(y_odd);
        a_even = recursiveInvFFT(y_even);
        polynomial a(n);
        comp omega_n((long double)cos(-2*PI/n), (long double) sin(-2*PI/n));
        comp omega(1.0L,0.0L);
        for(ll i=0; i<=n/2-1; i++)
        {
            a[i]=sum(a_even[i], product(omega, a_odd[i]));
            a[i+n/2]=subtract(a_even[i], product(omega, a_odd[i]));
            omega = product(omega, omega_n);
        }
        return a;  
    }
}

void display(polynomial a)
{
    long double real_part;
    long double complex_part;
    for(ll i = 0; i<a.size(); i++)
    {
        real_part = a[i].first;
        complex_part = a[i].second;
        if(real_part<0 && real_part>-0.0005) real_part=0;
        if(complex_part<0 && complex_part>-0.0005) complex_part=0;
        printf("(%.3Lf,%.3Lf)\n", real_part, complex_part);
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
        ll log_pow = logarithm_base2(2*n);
        ll N = pow(2, log_pow);
        polynomial poly1, poly2, poly_product, output_poly;
        for(ll i = 0; i<n; i++)
        {
            comp input;
            cin>>input.first>>input.second;
            poly1.push_back(input);
        }
        for(ll i = 0; i<n; i++)
        {
            comp input;
            cin>>input.first>>input.second;
            poly2.push_back(input);
        }
        poly1.resize(N);
        poly2.resize(N);
        poly_product = dot_product(recursiveFFT(poly1), recursiveFFT(poly2));        
        output_poly = recursiveInvFFT(poly_product);
        for(ll i = 0; i<output_poly.size(); i++)
            output_poly[i] = divide(output_poly[i], N);
        display(output_poly);
    }
    return 0;
}