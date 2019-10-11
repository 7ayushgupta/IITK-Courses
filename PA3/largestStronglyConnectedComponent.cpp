#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
typedef long long ll;
ll TIME;

typedef struct node_template
{
	ll key;
	node_template* next;
}node;

class Stack{
    public:
        ll top;
        ll arr[100001];
    
        Stack();
        void push(ll c);
        bool isEmpty();
        ll pop();
};

Stack::Stack()
{
    this->top=0;
}

void Stack::push(ll c)
{
    (this->top)++;
    this->arr[this->top]=c;
}

bool Stack::isEmpty()
{
    return ((this->top)==0);
}

ll Stack::pop()
{
    if(this->isEmpty())
    {
        cout<<"Underflow";
        return -1;
    }
    else
    {
        (this->top)--;
        return arr[top+1];
    }
}

class Graph : public Stack
{
    public: 
        ll V, E;
        node ** Adj;
        node ** AdjT;
        ll* color; //0: white, 1: gray, 2: black
        ll* discovery_time;
        ll* finishing_time;
        ll* predecessor;
        Stack stack;
        Graph(ll, ll);    
        void performInput();
        void DFS();
        void DFS_Visit(ll);
        void DFS_Modified();
        ll DFS_Visit_Modified(ll);
        void computeTranspose();
};

Graph::Graph(ll v, ll e)
{
    Adj = (node **) malloc (v*sizeof(node *));
    AdjT = (node **) malloc (v*sizeof(node *));
    for(ll i = 0; i<v; i++)
    {
        Adj[i] = NULL;
        AdjT[i] = NULL;
    }
    discovery_time = (ll *)malloc(v*sizeof(ll));
    finishing_time = (ll *)malloc(v*sizeof(ll));
    predecessor = (ll *)malloc(v*sizeof(ll));
    color = (ll *)malloc(v*sizeof(ll));
    stack = Stack();
}

void Graph::performInput()
{
    for(ll i = 0; i<this->E; i++)
    {
        ll vert1, vert2;
        cin>>vert1>>vert2;
        node* node1 = (node*) malloc(sizeof(node));
        node* node2 = (node*) malloc(sizeof(node));
        node1->key = vert1;
        node2->key = vert2;
        node1->next = NULL;
        node2->next = NULL;
        if(Adj[vert1] == NULL)
	    	Adj[vert1] = node2;
		else
		{
			node *temp_ptr = Adj[vert1];
			while(temp_ptr->next!=NULL)
				temp_ptr = temp_ptr->next;
			temp_ptr->next=node2;
	    }
    }
}

void Graph::DFS_Visit(ll u)
{
    TIME=TIME+1;
    this->discovery_time[u] = TIME;
    this->color[u] = 1;
    ll num_neighbours = sizeof(this->Adj[u])/sizeof(this->Adj[u][0]);
    for (int i = 0; i<num_neighbours; i++)
    {
        node* pointed_node = &(this->Adj[u][i]);
        if(this->color[pointed_node->key] == 0)
        {
            this->predecessor[pointed_node->key]=u;
            this->DFS_Visit(pointed_node->key);
        }
    }
    this->color[u] = 2;
    TIME=TIME+1;
    this->finishing_time[u] = TIME;
    this->stack.push(u);
}

void Graph::DFS()
{
    for (int i = 0; i<this->V; i++)
    {
        this->color[i] = 0;
        this->predecessor[i] = -1;
    }
    TIME=0;
    for (int i = 0; i<this->V; i++)
    {
        if(this->color[i] == 0)
            DFS_Visit(i);
    }
}

void Graph::DFS_Modified()
{
    for (int i = 0; i<this->V; i++)
    {
        this->color[i] = 0;
        this->predecessor[i] = -1;
    }
    while(!this->stack.isEmpty())
    {
        ll v = this->stack.pop();
        if(this->color[v]==0)
        {
            ll length_DFS = this->DFS_Visit_Modified(v);
            cout<<endl;
        }
    }
}

ll Graph::DFS_Visit_Modified(ll v)
{
    this->color[v]=2;
    // Recur for all the vertices adjacent to this vertex 
    return 1;
}

void Graph::computeTranspose()
{   
    Graph graph_T = Graph(this->V, this->E);
    for (int i = 0; i < this->V; i++) 
    { 
        ll num_neighbours = sizeof(this->Adj[i])/sizeof(this->Adj[i][0]);
        for (int j = 0; j<num_neighbours; i++)
        {
            node* pointed_node = &(this->Adj[j][i]);
            if(AdjT[pointed_node->key] == NULL)
	    	    AdjT[pointed_node->key] = Adj[j];
		    else
		    {
			node *temp_ptr = AdjT[pointed_node->key];
			while(temp_ptr->next!=NULL)
				temp_ptr = temp_ptr->next;
			temp_ptr->next=Adj[j];
            }
	    }
    }  
}

int main() 
{
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin>>t;
    while(t--)
    {
        ll v, e;
        cin>>v>>e;
        Graph graph(v, e);
        graph.performInput();
        graph.DFS();
        graph.computeTranspose();
        graph.DFS_Modified();

    }
    return 0;
}
