#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll; 

typedef struct Stack{
    ll arr[1005];
    ll top=0;
}stack;

void push(stack *s, ll c)
{
    (s->top)++;
    s->arr[s->top]=c;
}

bool isEmpty(stack *s)
{
    return ((s->top)==0);
}

void pop(stack *s)
{
    if(isEmpty(s))
        cout<<"Underflow";
    else
    (s->top)--;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    long long S;
    scanf("%lld", &S);
    while(S--)
    {
        ll Nk;
        scanf("%lld", &Nk);
        ll input[Nk];
        ll spans[Nk] = {0};
        for(ll i = 0; i<Nk; i++)
           scanf("%lld", &input[i]);
        stack s;
        for(ll i = 0; i<Nk; i++)
        {
            while(!isEmpty(&s) && input[i]>=input[s.arr[s.top]])
                pop(&s);
            if(isEmpty(&s)) spans[i]=i+1;
            else spans[i]=i-s.arr[s.top];
            push(&s, i);
        }
        for(ll i = 0 ; i<Nk; i++)
           printf("%lld\n", spans[i]);
    }
    return 0;
}