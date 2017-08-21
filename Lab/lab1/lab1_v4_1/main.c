#include <stdio.h>
#include <stdlib.h>


struct grafo
{
    int nro_vertices;
    int nro_aresta;
    int** adj;
};
typedef struct grafo *Grafo;


int **cria_matrixAdj(int r, int c)
{
    int i,j;
    int **t = malloc(r*sizeof(int*));
    for (i = 0; i < r; i++)
        t[i] = malloc (c * sizeof (int));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = 0;
    return t;
}

Grafo inicializa_grafo(int n,int m)
{
    Grafo gr = malloc(sizeof *gr);
    gr->nro_vertices = n;
    gr->nro_aresta = m;
    gr->adj = cria_matrixAdj(n,n);
    return gr;
}

void insereAresta(Grafo gr,int v,int w)
{
    //gr->adj[v][w] = 1;
    gr->adj[w][v] = 1;
}


void imprime_matrizAdj(Grafo gr)
{
    int i, j;
    printf("   1\t2\t3\t4\t5\t6\t7 \n");
    printf("-------------------------------------------------\n");
    for(i = 0; i < gr->nro_vertices; i++)
    {
        printf("%d| ", i+1);
        for(j = 0; j < gr->nro_vertices; j++)
        {
//            if (gr->adj[i][j] == NULL)
//                printf("NULL\t");
//            else
            printf("%d\t", gr->adj[i][j]);
        }
        printf("\n");
    }
}

int dfs(Grafo gr,int n,int x, int visitado[],int maior,int peso [])
{
    int j,k,i= x;
//    printf("novo dfs\n");
//    printf("\n%d",i);
//    printf("\n");
    visitado[i] = 1;
//    for (k = 0; k < n ; k++)
//        printf("%d ", visitado[k]);
//
//    printf("\n");


    for (j = 0; j < n; j++)
    {
//       printf("i = %d\t j = %d\n",i,j);
//        printf("gr->adj[%d][%d] = %d \n",i,j, gr->adj[i][j]);
        if (visitado[j] == 0 && gr->adj[i][j] == 1)
        {
            if(maior <= peso[j])
            {
                maior = peso[j];
//                printf("novo maior1 = %d\n",maior);
                maior = dfs(gr,n,j,visitado,maior,peso);
            }
            else
//            printf("novo maior2 = %d\n",maior);
                maior = dfs(gr,n,j,visitado,maior,peso);
        }
    }

    return maior;
}

Grafo troca (Grafo gr,int x,int y)
{
    int i;

    for (i = 0; i < gr->nro_vertices; i++)
    {
        int tmp1 = gr->adj[i][x];
        gr->adj[i][x] = gr->adj[i][y];
        gr->adj[i][y] = tmp1;
    }

    for (i = 0; i < gr->nro_vertices; i++)
    {
        int tmp2 = gr->adj[x][i];
        gr->adj[x][i] = gr->adj[y][i];
        gr->adj[y][i] = tmp2;
    }

    return gr;
}

int main()
{
    int n,m,l;
    int i;

    printf("digite n,m,k:\n");
    scanf("%d %d %d",&n,&m,&l);

//    n = 7;
//    m = 8;
//    l = 9;

    int *visitado;

//    for (i = 0; i < n ; i++)
//        printf("%d ", visitado[i]);

//    printf("\n");
//
//    printf("\n");


    int peso[n-1];
//    printf("Ler os pesos: \n");

//    for (i = 0; i < n ; i++)
//        scanf("%d",&peso[i]);

    peso[0] = 18;
    peso[1] = 14;
    peso[2] = 13;
    peso[3] = 23;
    peso[4] = 9;
    peso[5] = 15;
    peso[6] = 4;


//    peso[0] = 60;
//    peso[1] = 50;
//    peso[2] = 40;
//    peso[3] = 30;
//    peso[4] = 20;
//    peso[5] = 10;

    Grafo gr = inicializa_grafo(n,m);

//    int u,v;
//    for (i = 0 ; i < m; i++)
//    {
//        printf("digite arestas:\n");
//        scanf("%d %d",&u,&v);
//        insereAresta(gr,u-1,v-1);
//    }
//    insereAresta(gr,1-1,2-1);
//    insereAresta(gr,1-1,3-1);
//    insereAresta(gr,2-1,5-1);
//    insereAresta(gr,3-1,5-1);
//    insereAresta(gr,3-1,6-1);
//    insereAresta(gr,4-1,6-1);
//    insereAresta(gr,5-1,7-1);
//    insereAresta(gr,6-1,7-1);

    insereAresta(gr,1-1,4-1);
    insereAresta(gr,1-1,3-1);
    insereAresta(gr,4-1,5-1);
    insereAresta(gr,3-1,5-1);
    insereAresta(gr,3-1,6-1);
    insereAresta(gr,2-1,6-1);
    insereAresta(gr,5-1,7-1);
    insereAresta(gr,6-1,7-1);

//    insereAresta(gr,4-1,1-1);
//    insereAresta(gr,4-1,3-1);
//    insereAresta(gr,1-1,5-1);
//    insereAresta(gr,3-1,5-1);
//    insereAresta(gr,3-1,6-1);
//    insereAresta(gr,2-1,6-1);
//    insereAresta(gr,5-1,7-1);
//    insereAresta(gr,6-1,7-1);
//
//    insereAresta(gr,7-1,1-1);
//    insereAresta(gr,7-1,3-1);
//    insereAresta(gr,2-1,6-1);
//    insereAresta(gr,3-1,5-1);
//    insereAresta(gr,3-1,6-1);
//    insereAresta(gr,1-1,5-1);
//    insereAresta(gr,5-1,4-1);
//    insereAresta(gr,6-1,4-1);


//    insereAresta(gr,1-1,5-1);
//    insereAresta(gr,1-1,4-1);
//    insereAresta(gr,3-1,6-1);
//    insereAresta(gr,2-1,5-1);
//    insereAresta(gr,4-1,5-1);

    imprime_matrizAdj(gr);

    int e,a,b;
    char c;

    for (i = 0; i < l ; i++)
    {
        printf("digite 'P' ou 'T':\n");
        scanf(" %c",&c);
        switch (c)
        {
        case 'P':
            scanf("%d",&e);
            int maior = -1;
            visitado = (int*)calloc(n, sizeof(int));
            maior = dfs(gr,n,e-1,visitado,maior,peso);
            //   printf("maior final = %d\n",maior);
            if(maior == -1 || maior == peso[e])
                printf("*\n");
            else
                printf("%d\n",maior);
            break;
        case 'T':
            scanf("%d %d",&a,&b);
            troca(gr,a-1,b-1);
            printf("nova MATRIZ:\n");
            imprime_matrizAdj(gr);
        }
    }

    return 0;
}

