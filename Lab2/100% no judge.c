#include <stdio.h>
#include <stdlib.h>

int mark[100000];
int index2 = 1;
int num[100000];
int menor[100000];
int pai[100000];
int resposta[100000];

int minimo (int a,int b) {
    if (a <= b)
        return a;
    else
        return b;
}

//--------------------------------------------LISTA DE ADJACENCIA -------------------------//////
///////////////////////////////////////////////////////////////////////////////////////////
typedef struct elementoGrafo
{
	int info;
	struct elementoGrafo* prox;
}elementoGrafo;

typedef struct tipoLista
{
	elementoGrafo *cabeca;
}tipoLista;

typedef struct tipoGrafo
{
	int vertice;
	tipoLista* vet;
}tipoGrafo;
//==========================================================================//

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

    // GRAFO UNIDIRECIONAL
    novoNo = novoElemento(a);
    novoNo->prox = grafo->vet[b].cabeca;
    grafo->vet[b].cabeca = novoNo;
}

void DFS(tipoGrafo*G,int v) {
    int filho = 0;
    mark[v] = 1;
    num[v] = index2;
    menor[v] = index2;
    index2++;
    elementoGrafo* noTemp = G->vet[v].cabeca;
    while(noTemp != NULL) {
        if(mark[noTemp->info] == 0) {
            filho++;
            pai[noTemp->info] = v;
            DFS(G,noTemp->info);
            menor[v] = minimo(menor[v],menor[noTemp->info]);
            if(pai[v] == -1 && filho > 1)
                    resposta[v] = 1;
            if (pai[v] != -1 && menor[noTemp->info] >= num[v])
                resposta[v] = 1;
        }
        else if (!(pai[v] == noTemp->info))
            menor[v] = minimo(menor[v],num[noTemp->info]);
        noTemp = noTemp->prox;
    }
}

void inicializaVetores(int n) {
    int i;
    for (i=0;i<n;i++) {
        mark[i] = 0;
        num[i] = -1;
        pai[i] = -1;
        resposta[i] = NULL;
    }
}

void resultado(int n) {
    int i;
    for(i = 0;i<n;i++){
        if(resposta[i] == 1)
            printf("%d\n",i);
    }
}

int main()
{
    // USAR RECURSÃO NO DFS para deixar de fazer recalculos.
    int n; //vertices
    int m; //arestas
    int i;
    int a;
    int b;

    scanf("%d",&n);
    scanf("%d",&m);
    tipoGrafo* G = criaGrafo(n);
    for (i=0;i<m;i++) {
        scanf("%d",&a);
        scanf("%d",&b);
        addAresta(G,b,a);
    }
    inicializaVetores(n);
    DFS(G,0);
    resultado(n);
    return 0;
}
