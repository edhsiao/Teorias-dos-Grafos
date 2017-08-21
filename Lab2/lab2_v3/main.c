#include <stdio.h>
#include <stdlib.h>

struct grafo
{
    int nro_vertices;
    int** listaAdj;
    int* grau;
};

typedef struct grafo Grafo;

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

void dfs(Grafo *gr,int u, int *vis, int *achou,int *low, int pai[])
{

    static int cont = 0;
    int i;

    vis[u] = 1;
    achou[u] = low[u] = ++cont;


    for (i = 0; i< gr->grau[u]; ++i)
    {
        int v = gr->listaAdj[u][i];

        if (vis[v] == -1)
        {
            pai[v] = u;
            dfs(gr,v, vis, achou, low, pai);

            low[u]  = menor(low[u], low[v]);

            if (low[v] > achou[u])
                printf("%d %d\n",u,v);
        }

        else
            if (v != pai[u])
                low[u]  = menor(low[u], achou[v]);
    }
}

void bridge(Grafo *gr,int N)
{
    int *vis,*achou,*low,*pai;

    int i;

    vis = (int*)malloc(N*sizeof(int));
    achou = (int*)malloc(N*sizeof(int));
    low = (int*)malloc(N*sizeof(int));
    pai = (int*)malloc(N*sizeof(int));

    for (i = 0; i < N; i++)
    {
        pai[i] = -1;
        vis[i] = -1;
    }

    for (i = 0; i < N; i++)
        if (vis[i] == -1)
            dfs(gr,i, vis, achou, low, pai);
}

int main()
{
    int N,M;

    scanf("%d %d", &N,&M);

    Grafo* gr = cria_Grafo(N,M);

    int i,u,v;
    for (i = 0 ; i < M; i++)
    {
        scanf("%d %d",&u,&v);
        insereAresta(gr,u,v);
    }

//
//    insereAresta(gr,1,0);
//    insereAresta(gr,0,2);
//    insereAresta(gr,2,1);
//    insereAresta(gr,0,3);
//    insereAresta(gr,3,4);


//    imprime_listaAdj(gr);

    bridge(gr,N);

    return 0;
}
