#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct elem_Grafo
{
    int x;
    struct elem_Grafo* prox;
} elem_Grafo;

typedef struct listaAdj
{
    elem_Grafo *head;
} listaAdj;

typedef struct Grafo
{
    int nro_vertices;
    listaAdj* vet;
} Grafo;

int visitado[100000];
int aux [100000];
int minimo [100000];
int pai [100000];
int resultado[100000];
int t = 0,tam = 0;

int menor(int a,int b)
{
    if(a > b)
        return b;
    return a;
}

elem_Grafo* novoElem(int item)
{
    elem_Grafo* novoNo = (elem_Grafo*)(malloc(sizeof(elem_Grafo)));
    novoNo->x = item;
    novoNo->prox = NULL;
    return novoNo;
}

Grafo* cria_Grafo(int n)
{
    int i;
    Grafo* gr = (Grafo *)(malloc(sizeof(Grafo)));
    gr->nro_vertices = n;

    gr->vet = (listaAdj *)malloc(n * sizeof(struct listaAdj));

    for (i = 0; i < n; i++)
        gr->vet[i].head = NULL;

    return gr;
}

void insereAresta(Grafo* gr, int u, int v)
{
    elem_Grafo *aux = novoElem(v);
    elem_Grafo *temp;

    if(gr->vet[u].head == NULL)
        gr->vet[u].head= aux;
    else
    {
        temp = gr->vet[u].head;
        if(temp->x > v)
        {
            aux ->prox = temp;
            gr->vet[u].head = aux;
        }
        else if (temp->prox == NULL)
        {
            aux->prox = temp->prox;
            temp->prox = aux;

        }
        else
        {
            while((temp->prox != NULL) && (temp->prox->x < v))
                temp = temp->prox;
            aux->prox = temp->prox;
            temp->prox = aux;
        }
    }
}

void busca(Grafo *gr,int u,int *res) //tarjan
{
    int filho = 0;
    visitado[u] = TRUE;
    minimo[u] = aux[u] = ++t;

    elem_Grafo* noAux = gr->vet[u].head;

    while(noAux != NULL)
    {
        if(visitado[noAux->x] == FALSE)
        {
            filho++;
            pai[noAux->x] = u;
            busca(gr,noAux->x,res);

            minimo[u] = menor(minimo[u],minimo[noAux->x]);

            if((pai[u] != -1) && (minimo[u] >= aux[u]) )
                res[u] = TRUE;
            if((pai[u] == -1) && (filho > 1))
                res[u] = TRUE;

            //    minimo[u] = menor(minimo[u],minimo[noAux->x]);
        }

        // else if (!(pai[u] == noAux->x))
        else if (u != noAux->x)
            minimo[u] = menor(minimo[u],aux[noAux->x]);

        noAux= noAux->prox;
    }
}

int comparCres(const void *a,const void *b)
{
    return ( *(int*)a - *(int*)b );
}


void displayGraph(Grafo *graph)
{
    int i;
    for (i = 0; i < graph->nro_vertices; i++)
    {
        elem_Grafo* noAux = graph->vet[i].head;

        printf("\n%d: ", i);
        while (noAux)
        {
            printf("%d->", noAux->x);
            noAux  = noAux->prox;
        }
        printf("NULL\n");
    }
}

int main()
{
    int n,m;
    int i;


    scanf("%d %d", &n,&m);

    Grafo* gr = cria_Grafo(n);

    int u,v;
    for (i = 0 ; i < m; i++)
    {
        scanf("%d %d",&u,&v);
        insereAresta(gr,u,v);
        insereAresta(gr,v,u);
//        displayGraph(gr);
    }

    for (i = 0; i < n; i++)
    {
        visitado[i] = FALSE;
        minimo[i] = FALSE;
        pai[i] = -1;
        aux[i] = -1;
    }

    for ( i = 0; i < n; i++)
    //    if (visitado[i] == FALSE)
            busca(gr,i,resultado);

    //  qsort(resultado,tam,sizeof(resultado),comparCres);


    for(i = 0; i < tam; i++)
        if(resultado[i] == TRUE)
            printf("%d ",[i]);
}
