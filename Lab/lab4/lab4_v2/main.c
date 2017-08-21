#include <stdio.h>
#include <stdlib.h>


void imprime_vet(int vet[],int m)
{
    int i;
    for (i = 0; i < m; i++)
        printf("%d\t",vet[i]);
    printf("\n");
}
int test_match(int **matriz, int i, int *visitado, int *aux,int m)
{
    int j;
    printf("visitado:\t");
    imprime_vet(visitado,m);
    printf("aux:\t\t");
    imprime_vet(aux,m);
    printf("\n");
    for (j = 0; j < m; j++)
    {
        printf("testando %d->%d\n",i,j);
        if (matriz[i][j] && !visitado[j])
        {
            visitado[j] = 1;

            if (aux[j] < 0 || test_match(matriz, aux[j], visitado, aux,m))
            {
                aux[j] = i;
                printf("\n\t achou %d->%d\n\n",i,j);
                return 1;
            }
        }
        printf("\n\t falhou %d->%d\n\n",i,j);
    }
    return 0;
}

int max_match(int **matriz,int n,int m)
{

    int aux[m];
    int matching = 0;
    int i,j;
    for(i = 0 ; i < m; i++)
        aux[i]= -1;
    printf("\n!!!aux:\t\t");
    imprime_vet(aux,m);
    for (i = 0; i < n; i++)
    {
        int visitado[m];
        for (j = 0; j < m; j++)
            visitado[j] = 0;

        if (test_match(matriz, i, visitado, aux,m) == 1)
            matching++;
    }

    return matching;
}


int main()
{
    int n,m,l;
    int i,j,c,b;

    scanf("%d %d %d",&n,&m,&l);
    int **matriz = (int**)malloc(n * sizeof(int*));

    for (i = 0; i < m; i++)
    {
        matriz[i] = (int*) malloc(m * sizeof(int));
        for (j = 0; j < m; j++)
            matriz[i][j] = 0;
    }
    for(i = 0; i < l ; i++)
    {
        scanf("%d %d",&c,&b);
        matriz[c][b] = 1;
    }

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    printf("%d",max_match(matriz,n,m));

    return 0;
}
