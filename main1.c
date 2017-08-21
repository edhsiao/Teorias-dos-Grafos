/*
 * main.c
 *
 *  Created on: 17/06/2016
 *      Author: felipe
 *
 *
 *
 *      Algoritmo
 *
 *      O que quero menor caminho de s a t, com numero de
 *      vertices intermediario impar, ou seja o numero
 *      de aresta nesse caminho será par, pois temos
 *      2k+1 vertices intermediarios + s e t logo N= 2k+3
 *      que é impar e o caminho possui N-1 arestas, C= 2k +3 -1
 *      =2k+2 que é par.
 *
 *      Sabemos que em um grafo bipartido dois vertices do mesmo
 *      conjunto, só possuem caminho com um numero par de arestas
 *
 *      Entao o problema passa a ser
 *
 *      Dado um Grafo G, transforma-lo em um grafo G' bipartido,
 *      com s e t pertencente ao mesmo conjunto.
 *      Para então achar o caminho minimo.
 *
 *
 *        Como transformar G em G'
 *        Duplico os vertices de G onde antes teriamos x, agora temos os
 *        vértices x e x'
 *        Cada aresta (x,y) vou transformar em uma aresta  (x',y) e
 *        (x,y'), entao todo caminho de s a t terá numero de arestas
 *        par
 *
 *
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#define INFINITO 2147483647

typedef struct node {
	int dist;
	int id;
} node;
node *Qheap; //Min-heap com os vertices relaxados
typedef struct aresta {
	int origem, dest;
	int peso;
	struct aresta *prox;
} aresta;
typedef struct vertice {
	int id;
	aresta *prox;
	int pai;
	int dist;
	int posiHeap;
	int marcado;
} vertice;

int min(int a, int b) {
	if (a <= b) {
		return 0;
	} else
		return 1;

}
int min2(int a, int b) {
	if (a <= b) {
		return a;
	} else
		return b;

}
void inicializa(vertice *G, int N) {
	int var;
	for (var = 0; var < N; var++) {
		G[var].dist = INFINITO;
		G[var].id = var;
		G[var].posiHeap = -1;
		G[var].pai = -1;
		G[var].prox = NULL;
		Qheap[var].dist = INFINITO;
		Qheap[var].id = -1;
		G[var].marcado = 0;
	}

}

int extraiMin2(vertice *G, node *S, int ini, int fim) {
	int min = INFINITO;
	int id = 0;
	int var;
	int posimenor;

	for (var = ini; var < fim; var++) {
		if (S[var].dist < min && G[S[var].id].marcado != 1) {
			id = S[var].id;
			min = S[var].dist;
			posimenor = var;
		}
	}
	//troca(S,ini,posimenor);
	//G[ini].posiInseridoLista=posimenor;
	return id;
}

int menor(int esq, int dir) {
	if (esq < dir)
		return 0; //Esquerda menor
	else
		return 1; //Direita menor
}
void troca(vertice *G, int pai, int filho) {
	int distaux, idaux;

	distaux = Qheap[pai].dist;
	idaux = Qheap[pai].id;

	//pai recebe valores do filho
	Qheap[pai].dist = Qheap[filho].dist;
	Qheap[pai].id = Qheap[filho].id;

	//Filho recebe valores do pai em aux
	Qheap[filho].dist = distaux;
	Qheap[filho].id = idaux;

	G[Qheap[filho].id].posiHeap = pai;
	G[Qheap[pai].id].posiHeap = filho;

}
/*void heapRefaz(vertice *G, int pai, int fim) {
 int menorFilho;
 //Talvez precise tratar acesso indevido de memória
 menorFilho = menor(Qheap[(2 * pai) + 1].dist, Qheap[(2 * pai) + 2].dist);
 if(fim!=0){
 //If perigoso, setando a variavel utilizada para comparaçao logica
 if (menorFilho == 0) {//Menor filho Esquerda
 menorFilho = (2 * pai) + 1;
 } else {//Menor filho Direita
 menorFilho = (2 * pai) + 2;
 }

 if (Qheap[pai].dist > Qheap[menorFilho].dist) {
 troca(pai, menorFilho);
 G[Qheap[menorFilho].id].posiHeap = pai;
 G[Qheap[pai].id].posiHeap = pai;
 heapRefaz(G, menorFilho, fim);

 }}

 }*/

void heapRefaz(vertice *G, int esq, int dir) {
	int menor;

	if ((2 * esq + 2 < dir)
			&& ((Qheap[esq].dist > Qheap[2 * esq + 1].dist)
					|| (Qheap[esq].dist > Qheap[2 * esq + 2].dist))) {
		if (Qheap[2 * esq + 1].dist <= Qheap[2 * esq + 2].dist) {
			menor = 2 * esq + 1;
		}
		if (Qheap[2 * esq + 2].dist < Qheap[2 * esq + 1].dist) {
			menor = 2 * esq + 2;
		}

		troca(G, esq, menor);
		heapRefaz(G, menor, dir);

	} else if ((2 * esq + 1 <= dir)
			&& ((Qheap[esq].dist > Qheap[2 * esq + 1].dist))) {

		troca(G, esq, 2 * esq + 1);
		heapRefaz(G, 2 * esq + 1, dir);
	}





}
int extraiMin(int max, vertice *G, int fim) {
	int topo = Qheap[0].id;
	//Remove topo do heap
	Qheap[0].dist = INFINITO;

	//retorna o vertice removido

	return topo;
}

void constroiHeap(vertice* G, int fim) {
	int i;
	for (i = ((fim + 1) / 2); i >= 0; i--) {

		heapRefaz(G, i, fim);
	}

}
void dijkstra(vertice *G, int s, int t, int N) {

	aresta *aux; //Auxiliar para receber arestas  incidentes em v
	int i;
	int v;
	int fimheap = 0;

	//Todos vertices tem dist inicial infinita com relacao a s
	//Isso eh feito na funçao inicializa chamada na main

	G[s].dist = 0; //distancia de s a s é zero
	G[s].posiHeap = 0; //Posicao d s no heap

	Qheap[fimheap].dist = 0;
	Qheap[fimheap].id = s;

	//Percorre todos vertices de G
	for (i = 0; i < N; i++) {
		v = extraiMin(N, G, fimheap); //Extrai o  i-esimo vertice mais proximo a s
		G[v].marcado = 1; //Marca v  como visitado

		//if (v == t) //Chegou no destino
		//    break;

		//Para cada vertice adjacente a v
		aux = G[v].prox;
		while (aux != NULL) {

			//Atualizar chave ou inserir no heap

			//Há necessidade de atualizar
			if ((min(G[aux->dest].dist, G[v].dist + aux->peso) == 1)
					&& G[aux->dest].marcado != 1) {
				G[aux->dest].dist = G[v].dist + aux->peso;     //Atualiza a dist

				if (G[aux->dest].posiHeap == -1) { //Tratar inserção de novo vertice no heap

					fimheap++;
					G[aux->dest].posiHeap = fimheap;

				}
				Qheap[G[aux->dest].posiHeap].dist = G[aux->dest].dist;
				Qheap[G[aux->dest].posiHeap].id = aux->dest;
			}
			//Proximo vertice adjacente
			aux = aux->prox;

		}

		constroiHeap(G, fimheap);

		if(fimheap>=1){
		if (Qheap[fimheap].dist < Qheap[fimheap-1].dist) {
			troca(G, fimheap, fimheap-1);
		}}
		fimheap--;                    //Ao extrair um elemento do heap
	}
}

void dijkstra2(vertice *G, int s, int t, int N) {
	node *S;
	S = (node*) calloc(sizeof(node), N);
	aresta *aux;
	int i;
	int v;
	int fim = 0, inicio = 0; //Variaveis de controle da fila
	//Todos vertices tem dist inicial infinita com relacao a s
	G[s].dist = 0;    //distancia de s a s é zero
	S[fim].dist = G[s].dist;
	S[fim].id = s;
	fim++;

	for (i = 0; i < N; i++) {
		v = extraiMin2(G, S, inicio, fim);
		G[v].marcado = 1;
		//inicio++;
		//S[fim++].id=v;

		//Para cada vertice adjacente a v
		aux = G[v].prox;
		while (aux != NULL) {
			G[aux->dest].dist = min2(G[aux->dest].dist, G[v].dist + aux->peso);
			if (G[aux->dest].posiHeap == -1) {
				S[fim].id = aux->dest;
				S[fim].dist = G[aux->dest].dist;
				G[aux->dest].posiHeap = fim;
				fim++;

			} else {
				S[G[aux->dest].posiHeap].id = aux->dest;
				S[G[aux->dest].posiHeap].dist = G[aux->dest].dist;
			}
			aux = aux->prox;
		}

	}

}
void insere(vertice *Gbipar, int x, int y, int peso) {

	aresta*aux;
	aux = (aresta*) malloc(sizeof(aresta) * 1);
	aux->origem = x;
	aux->dest = y;
	aux->peso = peso;
	aux->prox = Gbipar[x].prox;
	Gbipar[x].prox = aux;

}
void imprime(vertice *Gbipar, int N) {
	int i;
	aresta *aux;
	for (i = 0; i < 2 * N; i++) {
		aux = Gbipar[i].prox;
		printf("%d: ", Gbipar[i].id);
		while (aux != NULL) {

			printf("dest %d-> peso%d ", aux->dest, aux->peso);
			aux = aux->prox;
		}
		printf("\n");

	}

}
int main() {
	int N, M;
	int i, u, v, peso;
	vertice *Gbipar;
	scanf("%d %d", &N, &M);
	Qheap = (node*) malloc(sizeof(node) * 2 * N);
	Gbipar = (vertice*) malloc(sizeof(vertice) * 2 * N);
	//Cria grafo bipartido dado um vertice x crio o vertice x'
	//Para cada aresta x y faco (x',y) e (y', x)
	inicializa(Gbipar, N * 2);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &v, &peso);
		//Aresta (x,y) -> (x',y),(x,y')
		insere(Gbipar, u - 1, v + N - 1, peso);
		insere(Gbipar, u + N - 1, v - 1, peso);
		//Aresta (y,x) -> (y',x),(y,x')
		insere(Gbipar, v - 1, u + N - 1, peso);
		insere(Gbipar, v + N - 1, u - 1, peso);
	}

	//imprime(Gbipar,N);
	if (N > 8000) {        //Dijkstra com heap
		dijkstra(Gbipar, 0, N - 1, 2 * N);
	} else {
		//Dijkstra com fila de prioridade
		dijkstra2(Gbipar, 0, N - 1, 2 * N);
	}

	if (Gbipar[N - 1].dist < INFINITO)
		printf("%d", Gbipar[N - 1].dist);
	else
		printf("-1");
	return 0;
}
