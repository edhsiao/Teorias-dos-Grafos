#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_N 10000
#define MAX_M 30000


int visitado[MAX_N];
int pai [MAX_N];

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
    elem_Grafo *aux = novoElem(v,d);
    elem_Grafo *temp;

    if(gr->vet[u].head == NULL)
        gr->vet[u].head = aux;
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

int menor(int a,int b)
{
    if(a < b)
        return a;
    else
        return b;
}


struct MinHeapNode
{
    int  v;
    int dist;
};

struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    struct MinHeapNode **array;
};


struct MinHeapNode* newMinHeapNode(int v, int dist)
{
    struct MinHeapNode* minHeapNode =
           (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}


struct MinHeap* createMinHeap(int capacity)
{
    struct MinHeap* minHeap =
         (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int *)malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
         (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist )
      smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist )
      smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *smallestNode = minHeap->array[smallest];
        MinHeapNode *idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}


int isEmpty(struct MinHeap* minHeap)
{
    return minHeap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
    if (isEmpty(minHeap))
        return NULL;


    struct MinHeapNode* root = minHeap->array[0];

    struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;


    minHeap->pos[root->v] = minHeap->size-1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

dijsktra()


void displayGraph(Grafo *graph)
{
    int i;
    for (i = 0; i < graph->nro_vertices; i++)
    {
        elem_Grafo* noAux = graph->vet[i].head;

        printf("\n%d: ", i+1);
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

    Grafo* gr = cria_Grafo(n);

    int u,v,d;
    for (i = 0 ; i < m; i++)
    {
        scanf("%d %d %d",&u,&v,&d);
        insereAresta(gr,u-1,v-1,d);
        insereAresta(gr,v-1,u-1,d);
    }

    displayGraph(gr);

    for (i = 0; i < n; i++)
    {
        visitado[i] = FALSE;
        pai[i] = -1;
    }












//    int i,j,n,m,u,v,d;
//    scanf("%d",&n);
//    scanf("%d",&m);
//    int **grafo = (int**)malloc(n * sizeof(int*));
//
//    for (i = 0; i < n; i++)
//    {
//        grafo[i] = (int*) malloc(n * sizeof(int));
//        for (j = 0; j < n; j++)
//        {
//            if (i == j )
//                grafo[i][j] = 0;
//            else
//                grafo[i][j] = MAX;
//        }
//    }
//
//
//    for(i = 0; i < m ; i++)
//    {
////        scanf("%d",&u);
////        scanf("%d",&v);
////        scanf("%d",&d);
////        grafo[u][v] = d;
//
//
////        grafo[0][1] = 3;
////        grafo[1][2] = 4;
////        grafo[2][0] = -1;
////        grafo[2][3] = -5;
////        grafo[2][4] = -6;
////        grafo[3][1] = 3;
////        grafo[4][3] = 0;
//
////        grafo[0][1] = 3;
////        grafo[1][2] = 4;
////        grafo[2][0] = -1;
////        grafo[2][3] = -5;
////        grafo[2][4] = -6;
////        grafo[3][1] = 3;
////        grafo[4][3] = -2;
//
//    }
//
//    floyd(grafo,n);
    return 0;
}


//typedef struct node *link;
//
//struct node
//{
//    int v;
//    int d;
//    link next;
//};
//struct graph
//{
//    int V;
//    int E;
//    link *adj;
//};
//link NEW (int v, link next)
//{
//    link x = malloc (sizeof *x);
//    x->v = v;
//    x->next = next;
//    return x;
//}
//Graph GRAPHinit (int V)
//{
//    int v;
//    Graph G = malloc (sizeof *G);
//    G->V = V;
//    G->E = 0;
//    G->adj = malloc (V*sizeof (link));
//    for (v=0; v<V; v++)
//        G->adj[v] = NULL;
//    return G;
//}
//
//void GRAPHinsertE (Graph G, Edge e)
//{
//    int v = e.v, w = e.w;
//    G->adj[v] = NEW (w, G->adj[v]);
//    G->adj[w] = NEW (v, G->adj[w]);
//    G->E++;
//}
//int GRAPHedges (Edge a[], Graph G)
//{
//    int v, E=0;
//    link t;
//    for (v = 0; v < G->V; v++)
//        for (t = G->adj[v]; t != NULL; t = t->next)
//            if (v < t->v) a[E++] = EDGE (v, t->v);
//    return E;
//}
//
//int menor(int a,int b)
//{
//    if(a < b)
//        return a;
//    else
//        return b;
//}

//void floyd (int **grafo,int n)
//{
//    int aux[n][n];
//    int i,j,k,tem_ciclo_neg = 0;
//
//    for(i = 0; i < n; i++)
//        for(j = 0; j < n; j++)
//            aux[i][j] = grafo[i][j];
//
//
//    for (i = 0; i < n; i++)
//    {
//        for (j = 0; j < n; j++)
//        {
//            for (k = 0; k < n; k++)
//            {
//
//                if (aux[j][i] != MAX &&
//                        aux[i][k] != MAX &&
//                        aux[j][i] + aux[i][k] < aux[j][k])
//                    aux[j][k]= menor(aux[j][k],aux[j][i]+aux[i][k]);
//            }
//        }
//    }
//
//    for(i = 0; i < n; i++)
//        if(aux[i][i] < 0)
//            tem_ciclo_neg = 1;
//
//    if(tem_ciclo_neg)
//        printf("Ciclo negativo");
//
//    else
//    {
//        for (i = 0; i < n; i++)
//        {
//            for ( j = 0; j < n; j++)
//            {
//                if (aux[i][j] == MAX)
//                    printf("%s ","INF");
//                else
//                    printf ("%d ",aux[i][j]);
//            }
//            printf("\n");
//        }
//    }
//}

