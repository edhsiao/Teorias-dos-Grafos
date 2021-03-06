#include <stdio.h>
#include <stdlib.h>
#define free -1

int imprime_vet(int vet[],int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d\t",vet[i]);
    printf("\n");
}
int test_match(int **matriz, int i, int *visitado, int *aux,int n)
{
    int j;
    printf("visitado:\t");
    imprime_vet(visitado,n);
    printf("aux:\t\t");
    imprime_vet(aux,n);
    printf("\n");
    for (j = 0; j < n; j++)
    {
        printf("testando %d->%d\n",i,j);
        if (matriz[i][j] && !visitado[j])
        {
            visitado[j] = 1;

            if (aux[j] < 0 || test_match(matriz, aux[j], visitado, aux,n))
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

int max_match(int **matriz,int m,int n)
{

    int aux[n];
    int matching = 0;
    int i,j;
    for(i = 0 ; i < n; i++)
        aux[i]= free;

    for (i = 0; i < m; i++)
    {
        int visitado[n];
        for (j = 0; j < n; j++)
            visitado[j] = 0;

        if (test_match(matriz, i, visitado, aux,n) == 1)
            matching++;
    }

    return matching;
}


int main()
{
    int n,m,l;
    int i,j,c,b;

    scanf("%d %d %d",&n,&m,&l);
    int **matriz = (int**)malloc(m * sizeof(int*));

    for (i = 0; i < m; i++)
    {
        matriz[i] = (int*) malloc(n * sizeof(int));
        for (j = 0; j < n; j++)
            matriz[i][j] = 0;
    }
    for(i = 0; i < l ; i++)
    {
        scanf("%d %d",&c,&b);
        matriz[c][b] = 1;
    }

//    for(i = 0; i < n; i++)
//    {
//        for(j = 0; j < m; j++)
//        {
//            printf("%d ", matriz[i][j]);
//        }
//        printf("\n");
//    }

    printf("%d",max_match(matriz,m,n));

    return 0;
}
