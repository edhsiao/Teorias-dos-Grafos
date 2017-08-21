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



typedef struct resultado
{
    int orig;
    int dest;
} resultado;

elem_Grafo* novoElem(int item);
tipoGrafo* cria_Grafo(int n);
void insereAresta(tipoGrafo* gr, int u, int v);
void bridge(tipoGrafo *gr,int u,resultado *res);
int menor(int a,int b);

int vis [100000];
int aux [100000];
int low [100000];
int pai [100000];

int t = 0;
int tam = 0;
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
        else {
            while((temp->prox != NULL) && (temp->prox->x < v))
                temp = temp->prox;
            aux->prox = temp->prox;
            temp->prox = aux;
        }
    }
}

void bridge(tipoGrafo *gr,int u,resultado *res)
{
    vis[u] = TRUE;
    low[u] = aux[u] = ++t;

    elem_Grafo* noAux = gr->vet[u].head;


    while(noAux != NULL)
    {
        if(vis[noAux->x] == FALSE)
        {
            pai[noAux->x] = u;
            bridge(gr,noAux->x,res);

            low[u] = menor(low[u],low[noAux->x]);

            if(low[noAux->x] > aux[u])
            {
                if(u < noAux->x)
                {
                     res[tam].orig = u;
                     res[tam].dest = noAux->x;
                     tam++;
                }
                else
                {
                    res[tam].orig = noAux->x;
                    res[tam].dest = u;
                    tam++;
                }
             //   printf("%d %d\n",u,noAux->x);
            }

            low[u] = menor(low[u],low[noAux->x]);
        }

       // else if (noAux->x != pai[u])
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

int comparCres(const void *a,const void *b)
{
    if( ((*(resultado*)a).orig) == (*(resultado*)b).orig)
        return 0;
    else if ( ((*(resultado *)a).orig) < ((*(resultado*)b).orig))
            return -1;
        else
            return 1;
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
    resultado res[M];

    tipoGrafo* gr = cria_Grafo(N);

    int u,v;
    for (i = 0 ; i < M; i++)
    {
        scanf("%d %d",&u,&v);
        insereAresta(gr,u,v);
        insereAresta(gr,v,u);
    //    displayGraph(gr);
    }

    for (i = 0; i < N; i++)
    {
        vis[i] = FALSE;
        pai[i] = NIL;
        aux[i] = NIL;
    }
    //displayGraph(gr);
//    for ( i = 0; i < N; i++)
//        if (vis[i] == FALSE)
            bridge(gr,i,res);

//    printf("\ntam = %d\n",tam);
//     for(i = 0; i < tam;i++)
//        printf("%d -> %d %d\n",i,res[i].orig,res[i].dest);

   // if(tam > 1)
        qsort(res,tam,sizeof(resultado),comparCres);

    for(i = 0; i < tam;i++)
        printf("%d %d\n",res[i].orig,res[i].dest);

    return 0;
}
