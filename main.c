#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/*
 André Guimarães Jorge - R.A: 22118115-9
 João Victor da Silva Couto - R.A: 22118022-7
*/

int **leituraMatriz(int n){
    int i,**m;
    m = malloc(sizeof(int *)*n);
    for(i=0;i<n;i++){
        m[i] = malloc(sizeof(int)*n);
    }
    return m;
}

void desalocaMatriz(int **m, int n){
    int i;
    for(i=0;i<n;i++){
        free(m[i]);
    }
    free(m);
}

int** multi_matriz(int **m1,int **m2, int numv){
    int i,j,k;
    int soma;
    int **mr = leituraMatriz(numv);
    for (i=0;i<numv;i++){
        for(j=0;j<numv;j++){
            soma = 0;
            for(k=0;k<numv;k++){
                soma += m1[i][k] * m2[k][j];
            }
            mr[i][j] = soma;
        }
    }
    return mr;
}

void passeio(int **m_cubo, int numv){
    int i,j;
    int maior = 0;
    
    for(i=0;i<numv;i++){
        for(j=i;j<numv;j++){
            if(m_cubo[i][j] > maior){
                maior = m_cubo[i][j];
            }  
        }
    }
    printf("O maior numero de passeios de tamanho 3 no grafo é %d\n",maior);
    if(maior > 0){
    	printf("Ocorrem entre os vértices:\n");
	    for(i=0;i<numv;i++){
	        for(j=i;j<numv;j++){
	            if(m_cubo[i][j] == maior){
	                printf("v%d e v%d\n",i+1,j+1);
	            }
	        }
	    }	
	}
}

void graus(int **m, int numv){
    int i,j,soma,aux;
    int vetor_graus[numv];
    for(i=0;i<numv;i++){
            soma = 0;
        for(j=0;j<numv;j++){
            soma += m[i][j];
        }
        vetor_graus[i] = soma;
    }

    for(i=0;i<numv;i++){
        for(j=0;j<numv-1;j++){
            if(vetor_graus[j] < vetor_graus[j+1]){
                aux = vetor_graus[j];
                vetor_graus[j] = vetor_graus[j+1];
                vetor_graus[j+1] = aux;
            }
        }
    }
    printf("Graus do grafo em ordem não crescente: ");
    for(i=0;i<numv;i++){
        printf("%d  ",vetor_graus[i]);
    }
    puts("");
}

int contaArestas(int **m, int numv){
    int i,j;
    int a = 0;

    for(i=0;i<numv;i++){
       for(j=i;j<numv;j++){
            a+=m[i][j];
       }
    }
    printf("Arestas do grafo: %d\n",a);
    return a;
}

void dfs(int **adj, int numv, int ini, int *visitado, int cont){
    int i,j;
    
    visitado[ini] = cont;

    for(i=0;i<numv;i++){
        if(adj[ini][i] != -1){
            if(!visitado[adj[ini][i]]){
                dfs(adj,numv,adj[ini][i],visitado,cont+1);
            }
        }
    }
}


int buscaGrafo(int ini, int *visitado, int numv, int **adj){
    int cont = 1;
    int i;
    for(i=0;i<numv;i++){
        visitado[i] = 0;
    }
    dfs(adj,numv,ini,visitado,cont);

    for(i=0;i<numv;i++){
        if(visitado[i] == 0){
            return 1;
        }
    }
    return 0;

}

void tipoGrafo(int **m, int numv, int a, int conexo){
    int i,j,soma = 0;
    int arestamult = 0;
    int laco = 0;


    for(i=0;i<numv-1;i++){
        for(j=1+i;j<numv;j++){
            if(m[i][j] > 1){
                printf("Aresta múltipla entre os vértices v%d e v%d\n",i+1,j+1);
                arestamult = 1;
            }
        }
    }
    puts("");
    for(i=0;i<numv;i++){
        for(j=0;j<numv;j++){
            if(m[i][i] != 0){
                printf("Laço no vértice v%d\n",i+1);
                laco=1;
                break;
            }
        }
    }
    puts("");

    if(laco == 0 && arestamult == 0){
        if(a == numv *(numv - 1)/2){
            printf("O grafo é completo, pois é um grafo simples onde todo vértice é adjacente a todos os outros vértices!\n");
        }
        else{
            printf("O grafo é simples, pois não existem arestas múltiplas ou laços!\n");
        }
    }
    else{
        printf("O grafo não é simples!\n");
    }

    if(conexo == 0){
        printf("O grafo é conexo!\n");
        if(laco == 0 && arestamult ==0){
        	if(a == numv - 1){
            	printf("O grafo é uma árvore!\n");
        	}	
		}
    }
    else{
        printf("O grafo é desconexo!\n");
    }

}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"Portuguese");
    int i,j,numv,arestas,num,cont = 0;
    int conexo;
    int **matriz;
    int **matriz_quad;
    int **matriz_cubo;
    FILE *arq;

    if((arq = fopen("A.txt","r")) == NULL){
        printf("Erro na abertura do arquivo!");
        exit(1);
        system("pause");
    }

    while((fscanf(arq,"%d",&num))!= EOF){
        cont++;
    }
    rewind(arq);
    numv = sqrt(cont);
    matriz = leituraMatriz(numv);

    printf("========= Algoritmo de Grafos ============\n\n");
    printf(" Análise do Grafo:\n\n");

    for(i=0;i<numv;i++){
        for(j=0;j<numv;j++){
            fscanf(arq,"%d",&matriz[i][j]);
        }
    }
    matriz_quad = multi_matriz(matriz,matriz,numv);
    matriz_cubo = multi_matriz(matriz,matriz_quad,numv);
    
    int visitado[numv];
    int**adj = leituraMatriz(numv);

    for(i=0;i<numv;i++){
        for(j=0;j<numv;j++){
            adj[i][j] = -1;
        }
    }

    for(i=0;i<numv;i++){
        for(j=0;j<=numv;j++){
            if(matriz[i][j] != 0){
                adj[i][j] = j;
            }
        }
    }
    fclose(arq);

    conexo = buscaGrafo(0,visitado,numv,adj);
    puts("");
    graus(matriz,numv);
    puts("");
    arestas = contaArestas(matriz,numv);
    puts("");
    tipoGrafo(matriz,numv,arestas,conexo);
    puts("");
    passeio(matriz_cubo,numv);
    desalocaMatriz(matriz_quad,numv);
    desalocaMatriz(matriz_cubo,numv);
    desalocaMatriz(matriz,numv);
    system("pause");
    return 0;
}




