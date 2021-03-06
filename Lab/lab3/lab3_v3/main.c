#include <stdio.h>
#include <stdlib.h>

#define INF 1000000000


typedef struct elem_Grafo
{
    int x;
    int peso;
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

elem_Grafo* novoElem(int item, int d)
{
    elem_Grafo* novoNo = (elem_Grafo*)(malloc(sizeof(elem_Grafo)));
    novoNo->x = item;
    novoNo->peso = d;
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

void insereAresta(Grafo* gr, int u, int v,int d)
{
    elem_Grafo *novoNo = novoElem(v,d);
    novoNo->prox = gr->vet[u].head;
    gr->vet[u].head = novoNo;

    novoNo = novoElem(u,d);
    novoNo->prox = gr->vet[v].head;
    gr->vet[v].head = novoNo;
}

int menor(int a,int b)
{
    if(a < b)
        return a;
    else
        return b;
}

struct NoMinHeap
{
    int  v;
    int distancia;
};

struct MinHeap
{
    int tam;
    int cap;
    int *pos;
    struct NoMinHeap **vet;
};

struct NoMinHeap* newNoMinHeap(int v, int dist)
{
    struct NoMinHeap* NoMinHeap = (struct NoMinHeap*) malloc(sizeof(struct NoMinHeap));
    NoMinHeap->v = v;
    NoMinHeap->distancia = dist;
    return NoMinHeap;
}

struct MinHeap* criaMinHeap(int c)
{
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(c * sizeof(int));
    minHeap->tam = 0;
    minHeap->cap = c;
    minHeap->vet = (struct NoMinHeap**) malloc(c * sizeof(struct NoMinHeap*));
    return minHeap;
}

void trocaNoMinHeap(struct NoMinHeap** a, struct NoMinHeap** b)
{
    struct NoMinHeap* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int pos)
{
    int menor, esq, dir;
    menor = pos;
    esq = 2 * pos + 1;
    dir = 2 * pos + 2;

    if (esq < minHeap->tam &&
            minHeap->vet[esq]->distancia < minHeap->vet[menor]->distancia )
        menor = esq;

    if (dir < minHeap->tam &&
            minHeap->vet[dir]->distancia < minHeap->vet[menor]->distancia )
        menor = dir;

    if (menor != pos)
    {
        struct NoMinHeap *menorNo = minHeap->vet[menor];
        struct NoMinHeap *posNo = minHeap->vet[pos];

        minHeap->pos[menorNo->v] = pos;
        minHeap->pos[posNo->v] = menor;

        trocaNoMinHeap(&minHeap->vet[menor], &minHeap->vet[pos]);

        minHeapify(minHeap, menor);
    }
}

int heapVazio(struct MinHeap* minHeap)
{
    return minHeap->tam == 0;
}

struct NoMinHeap* extractMin(struct MinHeap* minHeap)
{
    if (heapVazio(minHeap))
        return NULL;

    struct NoMinHeap* raiz = minHeap->vet[0];

    struct NoMinHeap* lastNode = minHeap->vet[minHeap->tam - 1];
    minHeap->vet[0] = lastNode;

    minHeap->pos[raiz->v] = minHeap->tam-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->tam;
    minHeapify(minHeap, 0);

    return raiz;
}

void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    int i = minHeap->pos[v];
    minHeap->vet[i]->distancia = dist;
    while (i && minHeap->vet[i]->distancia < minHeap->vet[(i - 1) / 2]->distancia)
    {
        minHeap->pos[minHeap->vet[i]->v] = (i-1) / 2;
        minHeap->pos[minHeap->vet[(i-1) / 2]->v] = i;
        trocaNoMinHeap(&minHeap->vet[i],  &minHeap->vet[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct MinHeap *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->tam)
        return 1;
    return 0;
}


int dijkstra(Grafo* gr , int orig,int t)
{
    int u = orig;
    int V = gr ->nro_vertices;
    int dist[V];
    int v;


    struct MinHeap* minHeap = criaMinHeap(V);

    for (v = 0; v < V; v++)
    {
        dist[v] = INF;
        minHeap->vet[v] = newNoMinHeap(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->vet[orig] = newNoMinHeap(orig, dist[orig]);

    minHeap->pos[orig]   = orig;

    dist[orig] = 0;

    decreaseKey(minHeap, orig, dist[orig]);

    minHeap->tam = V;
    while (!heapVazio(minHeap))
    {
        struct NoMinHeap* NoMinHeap = extractMin(minHeap);
        u = NoMinHeap->v;
        elem_Grafo* aux = gr ->vet[u].head;
        while (aux != NULL)
        {
            v = aux->x;
            if (isInMinHeap(minHeap, v) && dist[u] != INF && aux->peso + dist[u] < dist[v])
            {
                dist[v] = dist[u] + aux->peso;
                decreaseKey(minHeap, v, dist[v]);
            }
            aux = aux->prox;
        }
    }
        return dist[t];
}

int displayGraph(Grafo *graph)
{
    int i;
    for (i = 1; i < graph->nro_vertices; i++)
    {
        elem_Grafo* noAux = graph->vet[i].head;

        printf("\n%d: ", i);
        while (noAux)
        {
            printf("|%d / %d| -> ", noAux->x+1,noAux->peso);
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

    Grafo* gr = cria_Grafo(n*2+1);

    int u,v,d;

    for (i = 0 ; i < m; i++)
    {
        scanf("%d %d %d",&u,&v,&d);
        if( u % 2 != 0)
        {
            insereAresta(gr,2*u-1,2*v,d);
            insereAresta(gr,2*u,2*v-1,d);
        }
        else
        {
            insereAresta(gr,2*u,2*v-1,d);
            insereAresta(gr,2*u-1,2*v,d);
        }
    }

  //  displayGraph(gr);
    if(dijkstra(gr,1,2*n-1) != INF)
        printf("%d\n",dijkstra(gr,1,2*n-1));
    else
        printf("-1\n");

    return 0;

}
