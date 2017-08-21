    #include <stdio.h>
    #include <stdlib.h>

    struct grafo
    {
        int nro_vertices;
        int** listaAdj;
        int* grau;
    };

    typedef struct grafo Grafo;

    Grafo* cria_Grafo(int nro_vertices,int grau_max);
    int insereAresta(Grafo* gr, int orig, int dest);
    //void imprime_listaAdj(Grafo *gr);
    int dfs_Grafo(Grafo *gr,int N, int ini, int fim);
    int dfs(Grafo *gr, int ini,int fim, int *visitado, int cont);


    Grafo* cria_Grafo(int nro_vertices,int grau_max)
    {
        Grafo *gr;
        gr = (Grafo*) malloc(sizeof(struct grafo));
        if(gr != NULL)
        {
            int i;
            gr->nro_vertices = nro_vertices;

            gr->grau = (int*) calloc(nro_vertices,sizeof(int));

            gr->listaAdj = (int**) malloc(nro_vertices * sizeof(int*));

            for(i = 0; i < nro_vertices; i++)
                gr->listaAdj[i] = (int*) malloc(grau_max* sizeof(int));

        }
        return gr;
    }


    int insereAresta(Grafo* gr, int orig, int dest)
    {
        if(gr == NULL)
            return 0;
        if(orig < 0 || orig >= gr->nro_vertices)
            return 0;
        if(dest < 0 || dest >= gr->nro_vertices)
            return 0;

        gr->listaAdj[orig][gr->grau[orig]] = dest;

        gr->grau[orig]++;

    }

    //void imprime_listaAdj(Grafo *gr)
    //{
    //    if(gr == NULL)
    //        return;
    //
    //    int i, j;
    //    for(i = 0; i < gr->nro_vertices; i++)
    //    {
    //        printf("%d: ", i);
    //        for(j = 0; j < gr->grau[i]; j++)
    //        {
    //            printf("%d, ", gr->listaAdj[i][j]);
    //        }
    //        printf("\n");
    //    }
    //}

    int dfs(Grafo *gr, int ini,int fim, int *visitado, int cont)
    {
        int i;
        visitado[ini] = cont;
        int flag;

        if (ini == fim)
            return 1;

        for(i = 0; i < gr->grau[ini]; i++)
        {

            if (visitado[gr->listaAdj[ini][i]] == 0 ) //vizinho nao visitado
            {
                flag = dfs(gr,gr->listaAdj[ini][i],fim,visitado,cont + 1);
                if (flag == 1 )
                    return 1;
            }
            else
                flag = 0 ; //todos vizinho visitado
        }

        return flag;
    }

    int dfs_Grafo(Grafo *gr,int N, int ini, int fim)
    {
        int cont = 1,result;

        int *vis =  (int*) calloc(N,sizeof(int));

        result = dfs(gr,ini,fim,vis,cont);

        free(vis);
        return result;

    }


    int main()
    {

        int N,M,u,v,P;
        int i;
        scanf("%d %d", &N,&M);

        Grafo* gr = cria_Grafo(N,M);

        for (i = 0 ; i < M; i++)
        {
            scanf("%d %d",&u,&v);
            insereAresta(gr,u,v);
        }

    //    insereAresta(gr,0,1);
    //    insereAresta(gr,1,0);
    //    insereAresta(gr,1,2);
    //    insereAresta(gr,2,4);
    //    insereAresta(gr,4,3);
    //    insereAresta(gr,3,2);

    //   imprime_listaAdj(gr)

        scanf("%d",&P);

        for(i = 0; i < P ; i++)
        {
            scanf("%d %d",&u,&v);

            if ((dfs_Grafo(gr,N,u,v) == 1) && (dfs_Grafo(gr,N,v,u)) == 1)
                printf("1\n");
            else
                printf("0\n");
        }

        return 0;
    }
