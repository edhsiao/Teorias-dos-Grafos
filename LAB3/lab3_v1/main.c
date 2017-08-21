#include <stdio.h>
#include <stdlib.h>
#define TAM 64
#define FALSE 0
#define TRUE 1
typedef struct elem_Grafo
{
    int x;
    struct elem_Grafo* prox;
} elem_Grafo;

typedef struct listaAdj
{
    elem_Grafo *head;
} listaAdj;

typedef struct tipoGrafo
{
    int nro_vertices;
    listaAdj* vet;
} tipoGrafo;

struct item
{
    int valor;
    struct item *lig;
};
typedef struct item tipoItem;

struct fila
{
    tipoItem *ini;
    tipoItem *fim;
};
typedef struct fila tipoFila;

elem_Grafo* novoElem(int item);
tipoGrafo* criaGrafo(int n);
void insereAresta(tipoGrafo* gr, int a, int b);

void cria_Fila(tipoFila *f);
void recria_Fila(tipoFila *f);
int verif_vazio (tipoFila *f);
int insereFila (tipoFila *f, int valor);
int removeFila(tipoFila *f, int *p);
void mov_cavalo(tipoGrafo* gr,int lin,int col);
void busca(int num);
void busca_largura (tipoGrafo* gr,int lin,int col,int linha_fim, int col_fim);

int matriz[8][8];
int aux[TAM],vis[TAM];
int busca_lin,busca_col;


elem_Grafo* novoElem(int item)
{
    elem_Grafo* novoNo = (elem_Grafo*)(malloc(sizeof(elem_Grafo)));
    novoNo->x = item;
    novoNo->prox = NULL;
    return novoNo;
}

tipoGrafo* criaGrafo(int n)
{
    int i;
    tipoGrafo* gr = (tipoGrafo *)(malloc(sizeof(tipoGrafo)));
    gr->nro_vertices = n;

    gr->vet = (listaAdj *)malloc(n * sizeof(struct listaAdj));

    for (i = 0; i < n; i++)
        gr->vet[i].head = NULL;
    return gr;
}

void insereAresta(tipoGrafo* gr, int a, int b)
{
    elem_Grafo* aux = novoElem(b);
    aux->prox = gr->vet[a].head;
    gr->vet[a].head = aux;
}

void cria_Fila(tipoFila *f)
{
    f->ini = NULL;
    f->fim = NULL;
}

int verif_vazio (tipoFila *f)
{
    if (f->ini == NULL)
        return TRUE;
    else
        return FALSE;
}

void recria_Fila(tipoFila *f)
{
    cria_Fila(f);
}

int insereFila (tipoFila *f, int valor)
{
    tipoItem *auxItem;
    auxItem = malloc(sizeof(tipoItem));

    if (auxItem == NULL)
        return FALSE;

    auxItem->valor = valor;

    auxItem->lig = NULL;

    if (verif_vazio(f))
        f->ini = auxItem;
    else
        f->fim->lig = auxItem;

    f->fim = auxItem;

    return TRUE;
}

int removeFila(tipoFila *f, int *p)
{
    tipoItem *auxItem;

    if (verif_vazio(f))
        return FALSE;

    auxItem = f->ini;

    *p = auxItem->valor;

    f->ini = auxItem->lig;

    if (f->ini == NULL)
        f->fim = NULL;

    return TRUE;
}

void busca(int num)
{
    busca_lin = num / 8;
    if (num <= 7)
        busca_col = num;
    else if (num >= 8 && num <= 15)
        busca_col = num - 8;
    else if (num >= 16 && num <= 23)
        busca_col = num - 16;
    else if (num >= 24 && num <= 31)
        busca_col = num - 24;
    else if (num >= 32 && num <= 39)
        busca_col = num - 32;
    else if (num >= 40 && num <= 47)
        busca_col = num - 40;
    else if (num >= 48 && num <= 55)
        busca_col = num - 48;
    else if (num >= 56 && num <= 63)
        busca_col = num - 56;
}


void mov_cavalo(tipoGrafo* gr,int lin,int col)
{
	 if ((lin - 1 > -1) && (col - 2 > -1))
        insereAresta(gr,matriz[lin][col],matriz[lin - 1][col - 2]);
    if ((lin + 1 < 8) && (col - 2 > -1))
        insereAresta(gr,matriz[lin][col],matriz[lin + 1][col - 2]);
	if ((lin + 1 < 8) && (col + 2 < 8))
        insereAresta(gr,matriz[lin][col],matriz[lin + 1][col + 2]);
    if ((lin - 1 > -1) && (col + 2 < 8))
        insereAresta(gr,matriz[lin][col],matriz[lin - 1][col + 2]);
    if ((lin + 2 < 8) && (col - 1 > - 1))
        insereAresta(gr,matriz[lin][col],matriz[lin + 2][col - 1]);
    if ((lin + 2 < 8) && (col + 1 < 8))
        insereAresta(gr,matriz[lin][col],matriz[lin + 2][col + 1]);
    if ((lin - 2 > -1) && (col + 1 < 8))
        insereAresta(gr,matriz[lin][col],matriz[lin - 2][col + 1]);
    if ((lin - 2 > -1) && (col - 1 > -1))
        insereAresta(gr,matriz[lin][col],matriz[lin - 2][col - 1]);

}

void busca_largura (tipoGrafo* gr,int lin,int col,int linha_fim, int col_fim)
{
    int p;
    int chegou = TRUE;

    elem_Grafo* temp;

    tipoFila fila;
    cria_Fila(&fila);

    vis[matriz[lin][col]]= TRUE;

    insereFila(&fila,matriz[lin][col]);

    aux[matriz[lin][col]] = FALSE;

    while(!verif_vazio(&fila) && chegou == TRUE)
    {
        removeFila(&fila,&p);
        busca(p);
        mov_cavalo(gr,busca_lin,busca_col);
        temp = gr->vet[p].head;

        while(temp != NULL)
        {
            if(vis[temp->x] == FALSE)
            {
                vis[temp->x] = TRUE;

                insereFila(&fila,temp->x);

                aux[temp->x] = aux[p] + 1;

                if(matriz[linha_fim][col_fim] == temp->x)
                {
                    chegou = FALSE;
                    printf("%d",aux[temp->x]);
                    break;
                }
            }
            temp = temp->prox;
        }
    }
}
int main()
{
    tipoGrafo* gr = criaGrafo(TAM);

    char lin_ini,col_ini;
    int lin_fim,col_fim;
    int i,j,k = 0;

    scanf("%c%d %c%d",&lin_ini,&lin_fim,&col_ini,&col_fim);


    lin_ini = lin_ini - 'a';
    lin_fim = lin_fim - 1;

    col_ini = col_ini - 'a';
    col_fim = col_fim - 1;


    for (i = 0;i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            matriz[i][j] = k;
            k++;
        }
    }

    for(i = 0; i < TAM; i++)
        vis[i] = FALSE;

    if((col_fim == lin_fim) && (lin_ini == col_ini))
        //posicao inicial = fim
        printf("0");
    else
        busca_largura(gr,lin_fim,lin_ini,col_fim,col_ini);

    return 0;
}
