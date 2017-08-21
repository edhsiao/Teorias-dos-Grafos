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

Grafo* matriz_transp(Grafo* gr,int N,int M)
{
    Grafo* grTrans = cria_Grafo(N,M);
    int v,i;
    for (v = 0; v < N; v++)
    {
        for(i = 0; i < gr->grau[v] ; i++ )
            insereAresta(grTrans,gr->listaAdj[v][i],v);
    }
    return grTrans;

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

void bridgeUtil(Grafo *gr,int u, int *vis, int *achou,int *low, int pred[])
{

    static int cont = 0;
    int i;
    vis[u] = 1;
      printViz(vis);
    //disc[u] = low[u] = ++time;
    printf("u = %d\n",u);
    achou[u] = low[u] = ++cont;
    printf("time = %d\n",cont);
    printf("disc[u] = %d\n",achou[u]);
    printf("low[u] = %d\n",low[u]);
    printf("grau[%d]= %d\n",u,gr->grau[u]);

    for (i = 0; i< gr->grau[u]; ++i)
    {
        printf("i = %d\n",i);
        int v = gr->listaAdj[u][i];
        printf("v = %d\n",v);
        if (vis[v] == 0)
        {
            printf("ENTROU IF\n");
            pred[v] = u;
            printf("ENTROU bridgeUtil\n");
            bridgeUtil(gr,v, vis, achou, low, pred);
            low[u]  = menor(low[u], low[v]);

            if (low[v] > achou[u])
                printf("%d %d\n",u,v);
        }

        else if (v != pred[u])
            low[u]  = menor(low[u], achou[v]);
    }
}

void corte(Grafo *gr,int N)
{
    int *vis,*achou,*low,*pred;

    int i;

    vis = (int*)malloc(N*sizeof(int));
    achou = (int*)malloc(N*sizeof(int));
    low = (int*)malloc(N*sizeof(int));
    pred = (int*)malloc(N*sizeof(int));

    for (i = 0; i < N; i++)
    {
        pred[i] = -1;
        vis[i] = 0;
    }

    // Call the recursive helper function to find Bridges
    // in DFS tree rooted with vertex 'i'
    for (i = 0; i < N; i++)
        if (vis[i] == 0)
            bridgeUtil(gr,i, vis, achou, low, pred);
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

    corte(gr,N);

    return 0;
}
