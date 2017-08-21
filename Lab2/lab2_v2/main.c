#include <stdio.h>
#include <stdlib.h>

struct grafo
{
    int nro_vertices;
    int** listaAdj;
    int* grau;
};

typedef struct grafo Grafo;

int *low,*val;

int i,t=0;

val = (int*)malloc(N*sizeof(int));
low = (int*)malloc(N*sizeof(int));

Grafo* cria_Grafo(int nro_vertices,int grau_max)
{
    Grafo *gr;
    gr = (Grafo*) malloc(sizeof(struct grafo));
    if(gr != NULL)
    {
        int i;
        gr->nro_vertices = nro_vertices;

        gr->grau = (int*) calloc(nro_vertices,sizeof(int));

        gr->listaAdj = (int**) malloc(nro_vertices * sizeof(int*));

        for(i = 0; i < nro_vertices; i++)
            gr->listaAdj[i] = (int*) malloc(grau_max* sizeof(int));

    }
    return gr;
}


void insereAresta(Grafo* gr, int orig, int dest)
{
    gr->listaAdj[orig][gr->grau[orig]] = dest;
    gr->listaAdj[dest][gr->grau[dest]] = orig;

    gr->grau[orig]++;
    gr->grau[dest]++;
}

void printViz(int *vis)
{
    int i;
    for (i = 0; i < 5; i++)
        printf("%d ",vis[i]);
    printf("\n");
}

int menor(int a,int b)
{
    if(a > b)
        return b;
    return a;
}

void imprime_listaAdj(Grafo *gr)
{
    if(gr == NULL)
        return;

    int i, j;
    for(i = 0; i < gr->nro_vertices; i++)
    {
        printf("%d: ", i);
        for(j = 0; j < gr->grau[i]; j++)
        {
            printf("%d, ", gr->listaAdj[i][j]);
        }
        printf("\n");
    }
}

void dfs(Grafo *gr,int x,int p)
{
    int i;
    val[x] = t;
    low[x] = t;
    t = t+1;
    int tam = gr->grau[u];
    for (i = 0; i< tam; ++i)
    {
        int u = gr->listaAdj[x][i];

        if (u == p)
            continue;

        if (vis[u] == -1)
        {
            dfs(gr,u,x);
            low[u]  = menor(low[x], low[u]);
        }

        if (low[u] > vis[x])
            printf("%d %d\n",u,v);
    }

    else
        low[x]  = menor(low[x], vis[u]);
}


void bridge(Grafo *gr,int N)
{

    for (i = 0; i < N; i++)
        vis[i] = -1;

    for (i = 0; i < N; i++)
    {
        if (vis[i] == -1)
            dfs(gr,i);
    }
}

int main()
{
    int N,M;

    scanf("%d %d", &N,&M);

    Grafo* gr = cria_Grafo(N,M);

//    int i,u,v;
//    for (i = 0 ; i < M; i++)
//    {
//        scanf("%d %d",&u,&v);
//        insereAresta(gr,u,v);
//    }


    insereAresta(gr,1,0);
    insereAresta(gr,0,2);
    insereAresta(gr,2,1);
    insereAresta(gr,0,3);
    insereAresta(gr,3,4);


    // imprime_listaAdj(gr);

//    for(i = 0; i < N; i++)
//        printf("grau [%d]= %d \n",i,gr->grau[i]);

    dfs(gr,N);

    return 0;
}
