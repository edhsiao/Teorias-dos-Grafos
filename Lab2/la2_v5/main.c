#include <stdio.h>
#include <stdlib.h>
/* Adjacency list node*/
typedef struct adjlist_node
{
    int vertex;                /*Index to adjacency list array*/
    struct adjlist_node *next; /*Pointer to the next node*/
} adjlist_node_t, *adjlist_node_p;

/* Adjacency list */
typedef struct adjlist
{
    int num_members;           /*number of members in the list (for future use)*/
    adjlist_node_t *head;      /*head of the adjacency linked list*/
} adjlist_t, *adjlist_p;

/* Graph structure. A graph is an array of adjacency lists.
   Size of array will be number of vertices in graph*/
typedef struct graph
{
    int num_vertices;         /*Number of vertices*/
    adjlist_p adjListArr;     /*Adjacency lists' array*/
} graph_t, *graph_p;


adjlist_node_p createNode(int v)
{
    adjlist_node_p newNode = (adjlist_node_p)malloc(sizeof(adjlist_node_t));

    newNode->vertex = v;
    newNode->next = NULL;

    return newNode;
}
graph_p createGraph(int n)
{
    int i;
    graph_p graph = (graph_p)malloc(sizeof(graph_t));

    graph->num_vertices = n;

    graph->adjListArr = (adjlist_p)malloc(n * sizeof(adjlist_t));

    for(i = 0; i < n; i++)
    {
        graph->adjListArr[i].head = NULL;
        graph->adjListArr[i].num_members = 0;
    }

    return graph;
}

void addEdge(graph_t *graph, int src, int dest)
{
    adjlist_node_p newNode;

    newNode = createNode(dest);

    newNode->next = graph->adjListArr[src].head;
    graph->adjListArr[src].head = newNode;
    graph->adjListArr[src].num_members++;

    newNode = createNode(src);
    newNode->next = graph->adjListArr[dest].head;
    graph->adjListArr[dest].head = newNode;
    graph->adjListArr[dest].num_members++;


}

void displayGraph(graph_p graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = graph->adjListArr[i].head;
        printf("\n%d: ", i);
        while (adjListPtr)
        {
            printf("%d->", adjListPtr->vertex);
            adjListPtr = adjListPtr->next;
        }
        printf("NULL\n");
    }
}

void imp_viz(int *vis,int N)
{
    int i;
    for (i = 0; i < N;i++)
        printf("%d ",vis[i]);
    printf("\n");
}

int menor(int a,int b)
{
    if(a > b)
        return b;
    return a;
}

void dfs(graph_p gr,int u,int vis[],int disc[],int low[],int pai[])
{
    static int t =0;
    int i;
    vis[u] = 1;
    disc[u] = low[u] = ++t;

    int tam = gr->adjListArr[u].num_members;
    printf("grau %d = %d\n",u,tam);

    for(i = 0; i < tam; i++)
    {
        int v = gr->adjListArr[u].head->vertex;
        printf("v = %d\n",v);
        imp_viz(vis,gr->num_vertices);
        if (!vis[v])
        {
            printf("===entrou if1 dfs ====\n");
            pai[v] = u;
            dfs(gr,v,vis,disc,low,pai);

            low[u] = menor(low[u],low[v]);
             printf("entrando if 2====\n");
            if (low[v] > disc[u])
            {
                printf("entrou if 2====\n");
                printf("%d %d\n",u,v);
            }
        }
        else if (v!= pai[u])
            low[u]  = menor(low[u], vis[v]);

        gr->adjListArr[u].head = gr->adjListArr[u].head->next;
    }
}

void bridge(graph_p gr,int N)
{
    int *vis,*disc,*low,*pai;
    vis = (int*)malloc(N*sizeof(int));
    low = (int*)malloc(N*sizeof(int));
    pai = (int*)malloc(N*sizeof(int));
    disc = (int*)malloc(N*sizeof(int));
    int i;

    for (i = 0; i < N; i++)
    {
        pai[i] = -1;
      //  low[i] = -1;
        vis[i] = 0;
      //  disc[i] = -1;
    }

    for (i = 0; i < N; i++)
        if (vis[i] == 0)
            dfs(gr,i,vis,disc,low,pai);
}

int main()
{
    int N,M;

    scanf("%d %d", &N,&M);

    graph_p gr = createGraph(N);

    int i,u,v;
    for (i = 0 ; i < M; i++)
    {
        scanf("%d %d",&u,&v);
        addEdge(gr,u,v);
    }


//    addEdge(gr,1,0);
//    addEdge(gr,0,2);
//    addEdge(gr,2,1);
//    addEdge(gr,0,3);
//    addEdge(gr,3,4);


    displayGraph(gr);
    bridge(gr,N);

    return 0;
}
