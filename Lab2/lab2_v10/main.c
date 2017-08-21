#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define NIL -1

typedef struct elem_Grafo
{
	int x;
	struct elem_Grafo* prox;
}elem_Grafo;

typedef struct listaAdj
{
	elem_Grafo *head;
}listaAdj;

typedef struct tipoGrafo
{
	int nro_vertices;
	listaAdj* vet;
}tipoGrafo;

elem_Grafo* novoElem(int item);
tipoGrafo* cria_Grafo(int n);
void insereAresta(tipoGrafo* gr, int u, int v);
void bridge(tipoGrafo *gr,int u);
int menor(int a,int b);

int vis [100000];
int aux [100000];
int low [100000];
int pai [100000];

int t = 1;

elem_Grafo* novoElem(int item)
{
    elem_Grafo* novoNo = (elem_Grafo*)(malloc(sizeof(elem_Grafo)));
    novoNo->x = item;
    novoNo->prox = NULL;
    return novoNo;
}

tipoGrafo* cria_Grafo(int n)
{
    int i;
    tipoGrafo* gr = (tipoGrafo *)(malloc(sizeof(tipoGrafo)));
    gr->nro_vertices = n;

    gr->vet = (listaAdj *)malloc(n * sizeof(struct listaAdj));

    for (i = 0; i < n; i++)
        gr->vet[i].head = NULL;

    return gr;
}

void insereAresta(tipoGrafo* gr, int u, int v)
{
    printf(" u = %d , v = %d\n",u,v);
    elem_Grafo *aux = novoElem(v);
    elem_Grafo *temp;

    if(gr->vet[u].head == NULL)
    {
         printf("gr->vet[%d].head VAZIO \n",u);
        gr->vet[u].head= aux;
    }
    else
    {
        printf("gr->vet[%d].head NAO VAZIO = %d\n",u,gr->vet[u].head->x);
        temp = gr->vet[u].head;
        printf("temp->x = %d\n",temp->x);
        if(temp->x > v)
        {
            printf("temp->x  %d > v %d\n",temp->x ,v);
            aux ->prox = temp;
            gr->vet[u].head = aux;
        }
        else if (temp->prox == NULL)
        {
            printf("temp->prox == NULL\n");
            aux->prox = temp->prox;
            temp->prox = aux;

        }
        else {
             printf("Else\n");
            while((temp->prox != NULL) && (temp->prox->x < v))
                temp = temp->prox;
            aux->prox = temp->prox;
            temp->prox = aux;
        }
    }
}

void bridge(tipoGrafo *gr,int u)
{
    vis[u] = TRUE;
    low[u] = t;
    aux[u] = t;
    t = t+1;

    elem_Grafo* noAux = gr->vet[u].head;


    while(noAux != NULL)
    {
        if(vis[noAux->x] == FALSE)
        {
            pai[noAux->x] = u;
            bridge(gr,noAux->x);

            low[u] = menor(low[u],low[noAux->x]);

            if(low[noAux->x] > aux[u])
                printf("%d %d\n",u,noAux->x);

            low[u] = menor(low[u],low[noAux->x]);
        }

      //  else if (v != pai[u])
        else if (!(pai[u] == noAux->x))
            low[u] = menor(low[u],aux[noAux->x]);

        noAux= noAux->prox;
    }
}

int menor(int a,int b)
{
    if(a > b)
        return b;
    return a;
}
void displayGraph(tipoGrafo *graph)
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
    int N,M;
    int i;

    scanf("%d %d", &N,&M);

    tipoGrafo* gr = cria_Grafo(N);

    int u,v;
    for (i = 0 ; i < M; i++)
    {
        scanf("%d %d",&u,&v);
        insereAresta(gr,u,v);
        insereAresta(gr,v,u);
        displayGraph(gr);
    }

//   displayGraph(gr);
//    insereAresta(gr,1,0);
//    insereAresta(gr,0,1);
//    displayGraph(gr);
//    printf("\n=====\n");
//
//    insereAresta(gr,0,2);
//     insereAresta(gr,2,0);
//    displayGraph(gr);
//        printf("\n=====\n");
//    insereAresta(gr,2,1);
//    insereAresta(gr,1,2);
//    displayGraph(gr);
//        printf("\n=====\n");
//    insereAresta(gr,0,3);
//     insereAresta(gr,3,0);
//    displayGraph(gr);
//        printf("\n=====\n");
//    insereAresta(gr,3,4);
//    insereAresta(gr,4,3);
//   displayGraph(gr);
//       printf("\n=====\n");

    for (i = 0; i < N; i++)
    {
        vis[i] = FALSE;
        pai[i] = NIL;
        aux[i] = NIL;
    }
    displayGraph(gr);

    bridge(gr,0);

    return 0;
}
