#include <stdio.h>
#include <stdlib.h>


struct grafo
{
    int nro_vertices;
    int** adj;
};
typedef struct grafo *Grafo;

int **cria_matrixAdj(int n)
{
    int i,j;
    int **t = malloc(n * sizeof(int*));
    for (i = 0;i < n; i++)
        t[i] = malloc (n * sizeof (int));

    for (i = 0;i < n; i++)
        for (j = 0;j < n; j++)
                t[i][j] = 0;
    return t;
}

Grafo inicializa_grafo(int n)
{
    Grafo gr = malloc(sizeof *gr);
    gr->nro_vertices = n;
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
            printf("%d\t", gr->adj[i][j]);
        printf("\n");
    }
}

int dfs(Grafo gr,int n,int x, int visitado[],int maior,int peso [])
{
    int j,i= x;
    visitado[i] = 1;

    for (j = 0; j < n; j++)
    {
        if (visitado[j] == 0 && gr->adj[i][j] == 1)
        {
            if(maior <= peso[j])
            {
                maior = peso[j];
                maior = dfs(gr,n,j,visitado,maior,peso);
            }
            else
            maior = dfs(gr,n,j,visitado,maior,peso);
        }
    }

    return maior;
}

Grafo troca (Grafo gr,int x,int y)
{
    int i;
    int pi = gr->adj[x][y],po = gr->adj[y][x];

    for (i = 0;i < gr->nro_vertices;i++)
    {
        int tmp1 = gr->adj[i][x];
        gr->adj[i][x] = gr->adj[i][y];
        gr->adj[i][y] = tmp1;

        int tmp2 = gr->adj[x][i];

        gr->adj[x][i] = gr->adj[y][i];
        gr->adj[y][i] = tmp2;
    }

    gr->adj[x][y] = pi;
    gr->adj[y][x] = po;

    return gr;
}

int main()
{
    int n,m,l;
    int i;
    int *visitado;

    scanf("%d %d %d",&n,&m,&l);

    int peso[n-1];

    for (i = 0; i < n ; i++)
        scanf("%d",&peso[i]);


    Grafo gr = inicializa_grafo(n);

    int u,v;
    for (i = 0 ; i < m; i++)
    {
        scanf("%d %d",&u,&v);
        insereAresta(gr,u-1,v-1);
    }

    int e,a,b;
    char c;

    for (i = 0; i < l ; i++)
    {
        scanf(" %c",&c);
        switch (c)
        {
        case 'P':
            scanf("%d",&e);
            int maior = -1;
            visitado = (int*)calloc(n, sizeof(int));
            maior = dfs(gr,n,e-1,visitado,maior,peso);
            if(maior == -1 || maior == peso[e])
                printf("*\n");
            else
                printf("%d\n",maior);
            break;
        case 'T':
            scanf("%d %d",&a,&b);
            troca(gr,a-1,b-1);

        }
    }

    return 0;
}

