#include <stdio.h>
#include <stdlib.h>



typedef struct elem_Grafo
{
    int x;
    int peso;
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

 void displayGraph(tipoGrafo *gr)
{
    int i;
    for (i = 0; i < gr->nro_vertices; i++)
    {
        elem_Grafo* noAux = gr->vet[i].head;

        printf("\n%d: ", i+1);
        while (noAux)
        {
            printf("%d->", noAux->x+1);
            noAux  = noAux->prox;
        }
        printf("NULL\n");
    }
}

 int main()
 {
    int n,m,l;
    int i;
    scanf("%d %d %d",&n,&m,&l);
    tipoGrafo* gr = cria_Grafo(n);

    //for(i = 0; i < m;i++)
   //     scanf("%d",&)

    int u,v;
    for (i = 0 ; i < m; i++)
    {
        scanf("%d %d",&u,&v);
        insereAresta(gr,u-1,v-1);
        displayGraph(gr);
    }

   /* insereAresta(gr,1-1,2-1);
    insereAresta(gr,1-1,3-1);
    insereAresta(gr,2-1,5-1);
    insereAresta(gr,3-1,5-1);
    insereAresta(gr,3-1,6-1);
    insereAresta(gr,4-1,6-1);
    insereAresta(gr,5-1,7-1);
    insereAresta(gr,6-1,7-1);
    displayGraph(gr);*/
    int e,a,b;
    char c;

    for (i = 0; i < l ; i++)
    {
        scanf("%d",&c);
        switch (c)
        {
        case 'P':
            scanf("%d",&e);
//            pergunta(gr,e);
            break;
        case 'T':
            scanf("%d %d",&a,&b);
  //          troca(gr,a,b);
        }
    }
    return 0;
 }
