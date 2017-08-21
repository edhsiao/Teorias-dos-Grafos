#include <stdio.h>
#include <stdlib.h>



The whole operation is O(1).

Vertex temp = new Vertex(input)
temp.next = head
head = temp

Now, tail points to the new vertex too.
The whole operation is O(1) if we maintain the tail pointer.

Vertex temp = new Vertex(input)
tail.next = temp
tail = temp

int mark[100000];
int index2 = 1;
int num[100000];
int menor[100000];
int pai[100000];

int minimo (int a,int b)
{
    if (a <= b)
        return a;
    else
        return b;
}

typedef struct elementoGrafo
{
    int info;
    struct elementoGrafo* prox;
} elementoGrafo;

typedef struct tipoLista
{
    elementoGrafo *cabeca;
} tipoLista;

typedef struct tipoGrafo
{
    int vertice;
    tipoLista* vet;
} tipoGrafo;

elementoGrafo* novoElemento(int b)
{
    elementoGrafo* novoNo = (elementoGrafo*)(malloc(sizeof(elementoGrafo)));
    novoNo->info = b;
    novoNo->prox = NULL;
    return novoNo;
}

tipoGrafo* criaGrafo(int n)
{
    int i;
    tipoGrafo* grafo = (tipoGrafo *)(malloc(sizeof(tipoGrafo)));
    grafo->vertice = n;

    grafo->vet = (tipoLista *)malloc(n * sizeof(struct tipoLista));

    for (i = 0; i < n; i++)
        grafo->vet[i].cabeca = NULL;
    return grafo;
}

void addAresta(tipoGrafo* grafo, int a, int b)
{
    elementoGrafo* novoNo = novoElemento(b);
    novoNo->prox = grafo->vet[a].cabeca;
    grafo->vet[a].cabeca = novoNo;

    novoNo = novoElemento(a);
    novoNo->prox = grafo->vet[b].cabeca;
    grafo->vet[b].cabeca = novoNo;
}

void DFS(tipoGrafo*G,int v)
{
    mark[v] = 1;
    num[v] = index2;
    menor[v] = index2;
    index2++;
    elementoGrafo* noTemp = G->vet[v].cabeca;
    while(noTemp != NULL)
    {
        if(mark[noTemp->info] == 0)
        {
            pai[noTemp->info] = v;
            DFS(G,noTemp->info);
            menor[v] = minimo(menor[v],menor[noTemp->info]);
            if(menor[noTemp->info] > num[v])
            {
                printf("%d %d\n",v,noTemp->info);
            }
            menor[v] = minimo(menor[v],menor[noTemp->info]);
        }
        else if (!(pai[v] == noTemp->info))
            menor[v] = minimo(menor[v],num[noTemp->info]);
        noTemp = noTemp->prox;
    }
}

void inicializaVetores(int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        mark[i] = 0;
        num[i] = -1;
        pai[i] = -1;
    }
}

int main()
{
    int n; //vertices
    int m; //arestas
    int i;
    int a;
    int b;

    scanf("%d",&n);
    scanf("%d",&m);
    tipoGrafo* G = criaGrafo(n);
    for (i=0; i< m; i++)
    {
        scanf("%d",&a);
        scanf("%d",&b);
        addAresta(G,b,a);
    }

//    addAresta(G,1,0);
//    addAresta(G,0,2);
//    addAresta(G,2,1);
//    addAresta(G,0,3);
//    addAresta(G,3,4);
    inicializaVetores(n);
    DFS(G,0);
    return 0;
}
