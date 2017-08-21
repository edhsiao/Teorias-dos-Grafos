#include <stdio.h>
#include <stdlib.h>

int vis [100000];
int aux [100000];
int low [100000];
int pai [100000];

int t = 1;

struct grafo
{
    int nro_vertices;
    int** listaAdj;
    int* grau;
};

typedef struct grafo Grafo;

Grafo* cria_Grafo(int nro_vertices,int nro_aresta)
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
            gr->listaAdj[i] = (int*) malloc(nro_aresta* sizeof(int));

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

void dfs(Grafo *gr,int x,int p)
{
    int i;
    vis[x] = t;
    low[x] = t;
    t = t + 1;

    int tam = gr->grau[x];

    for (i = 0; i< tam; ++i)
    {
        if (gr->listaAdj[x][i] == p)
            continue;

        if (vis[gr->listaAdj[x][i]] == -1)
        {
            dfs(gr,gr->listaAdj[x][i],x);

            if (low[gr->listaAdj[x][i]] > vis[x])
                printf("%d %d\n",x,gr->listaAdj[x][i]);

              low[x] = menor(low[x],low[gr->listaAdj[x][i]]);

        }
        else
            low[x]  = menor(low[x], vis[gr->listaAdj[x][i]]);
    }
}

void bridge(Grafo *gr,int N)
{
    int i;

    for (i = 0; i < N; i++)
    {
        pai[i] = -1;
        vis[i] = -1;
        low[i] = -1;
    }

    for (i = 0; i < gr->grau[i]; i++)
        if (vis[i] == -1)
            dfs(gr,i,-1);
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


    imprime_listaAdj(gr);

    bridge(gr,N);

    return 0;
}
