#include <stdio.h>
#include <stdlib.h>
#define free -1

char test_match(char **matriz, int i, char *visitado, char *aux,int m)
{
    int j;

    for (j = 0; j < m; j++)
    {
        if (matriz[i][j] && !visitado[j])
        {
            visitado[j] = 1;

            if (aux[j] < 0 || test_match(matriz, aux[j], visitado, aux,m))
            {
                aux[j] = i;
                //printf("\n\t achou %d->%d\n\n",i,j);
                return 1;
            }
        }
    }
    return 0;
}

int max_match(char **matriz,int n,int m)
{

    char aux[m];
    int matching = 0;
    int i,j;
    for(i = 0 ; i < m; i++)
        aux[i]= free;

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

    char matriz[n][m]
    for (i = 0; i < m; i++)
    {
        matriz[i] = (int*) malloc(m * sizeof(int));
        for (j = 0; j < m; j++)
            matriz[i][j] = 0;
    }
    char m


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

    printf("%d",max_match(matriz,n,m));

    return 0;
}
