#include <iostream>
#include <string> 
#include <stdio.h>
using namespace std;

typedef struct Stack{
    char arr[10000];
    int top=-1;
}stack;

void push(stack *s, char c)
{
    s->top++;
    s->arr[s->top]=c;
}

bool isEmpty(stack *s)
{
    return (s->top==-1);
}

void pop(stack *s)
{
    if(isEmpty(s))
        cout<<"Underflow";
    else
        s->top--;
}

void printStack(stack *s)
{
    if(isEmpty(s))
        printf("Stack is empty\n");
    else
    {
        for(int i = 0; i<=s->top; i++)
            printf("%c", s->arr[i]);
    }
    printf("\n");
}

bool isOperand(char s)
{
    return !(s == ')' || s=='(' || s=='+' || s=='-' || s=='*' || s=='/' || s=='^');
}

bool isOperator(char s)
{
    return(s=='+' || s=='-' || s=='*' || s=='/'|| s=='^');
}

bool precedenceComparatorLesser(char a, char b)
{
    if(a=='^')
        return false;
    else if((a=='/') && !(b=='^' || b=='/'))
        return false;
    else if((a=='*') && !(b=='/' || b=='*' || b=='^'))
        return false;
    else if(b=='(')
        return false;
    return true;   
}

string convertToPostfix(string input)
{
    stack s;
    string answer;
    int length=0;
    for(int i=0;i<input.length();i++)
    {
        if(input[i]=='(')
        {
            push(&s, '(');
        }
        else if(isOperand(input[i]))
        {      
            answer.push_back(input[i]); 
        }
        else if(input[i]==')')
        {
            while(s.arr[s.top]!='(')
            {
                answer.push_back(s.arr[s.top]);
                pop(&s);
            }
            pop(&s);
        }
        else if(isOperator(input[i]))
        {
            if(isEmpty(&s) || s.arr[s.top]=='(')
            {
                push(&s, input[i]);
            }
            else
            {
                while(!isEmpty(&s) && s.arr[s.top] != '(' && precedenceComparatorLesser(input[i], s.arr[s.top]))
                {
                    answer.push_back(s.arr[s.top]);
                    pop(&s);
                }
                push(&s, input[i]);                   
            }
        }
    }   
    while(!isEmpty(&s))
    {
        answer.push_back(s.arr[s.top]);
        pop(&s);
    }
    return answer;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    string input;
    string answer;
    getline (cin, input);
    int i=0;
    answer = convertToPostfix(input);
    cout<<answer;    
    return 0;
}