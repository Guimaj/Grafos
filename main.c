#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

/*
 André Guimarães Jorge - R.A: 22118115-9
 João Victor da Silva Couto - R.A: 22118022-7
*/

int **leituraMatriz(int linhas){
    int i,**matriz;
    matriz = malloc(sizeof(int *)*linhas);
    for(i=0;i<linhas;i++){
        matriz[i] = malloc(sizeof(int)*linhas);
    }
    return matriz;
}

void desalocaMatriz(int **matriz, int linhas){
    int i;
    for(i=0;i<linhas;i++){
        free(matriz[i]);
    }
    free(matriz);
}

int** multi_matriz(int **m1,int **m2, int numVertices){
    int i,j,k;
    int soma;
    int **m_resultante = leituraMatriz(numVertices);
    for (i=0;i<numVertices;i++){
        for(j=0;j<numVertices;j++){
            soma = 0;
            for(k=0;k<numVertices;k++){
                soma += m1[i][k] * m2[k][j];
            }
            m_resultante[i][j] = soma;
        }
    }
    return m_resultante;
}

void passeio(int **m_cubo, int numVertices){
    int i,j;
    int maior = 0;
    
    for(i=0;i<numVertices;i++){
        for(j=i;j<numVertices;j++){
            if(m_cubo[i][j] > maior){
                maior = m_cubo[i][j];
            }  
        }
    }
    printf("O maior numero de passeios de tamanho 3 no grafo é %d\n",maior);
    if(maior > 0){
    	printf("Ocorrem entre os vértices:\n");
	    for(i=0;i<numVertices;i++){
	        for(j=i;j<numVertices;j++){
	            if(m_cubo[i][j] == maior){
	                printf("v%d e v%d\n",i+1,j+1);
	            }
	        }
	    }	
	}
}


void bubbleSort(int *vetor_graus, int numVertices){
    int aux,i,j = 0;
    for(i=0;i<numVertices;i++){
        for(j=0;j<numVertices-1;j++){
            if(vetor_graus[j] < vetor_graus[j+1]){
                aux = vetor_graus[j];
                vetor_graus[j] = vetor_graus[j+1];
                vetor_graus[j+1] = aux;
            }
        }
    }
}



void graus(int **matriz, int numVertices){
    int i,j,soma;
    int vetor_graus[numVertices];
    for(i=0;i<numVertices;i++){
            soma = 0;
        for(j=0;j<numVertices;j++){
            soma += matriz[i][j];
        }
        vetor_graus[i] = soma;
    }

    bubbleSort(vetor_graus, numVertices);

    printf("Graus do grafo em ordem não crescente: ");
    for(i=0;i<numVertices;i++){
        printf("%d  ",vetor_graus[i]);
    }
    puts("");
}

int contaArestas(int **matriz, int numVertices){
    int i,j;
    int arestas = 0;

    for(i=0;i<numVertices;i++){
       for(j=i;j<numVertices;j++){
            arestas += matriz[i][j];
       }
    }
    printf("Arestas do grafo: %d\n",arestas);
    return arestas;
}

void dfs(int **adj, int numVertices, int ini, int *visitado, int cont){
    int i,j;
    
    visitado[ini] = cont;

    for(i=0;i<numVertices;i++){
        if(adj[ini][i] != -1){
            if(!visitado[adj[ini][i]]){
                dfs(adj,numVertices,adj[ini][i],visitado,cont+1);
            }
        }
    }
}


int buscaGrafo(int ini, int *visitado, int numVertices, int **adj){
    int cont = 1;
    int i;
    for(i=0;i<numVertices;i++){
        visitado[i] = 0;
    }
    dfs(adj,numVertices,ini,visitado,cont);

    for(i=0;i<numVertices;i++){
        if(visitado[i] == 0){
            return 1;
        }
    }
    return 0;

}

void tipoGrafo(int **matriz, int numVertices, int arestas, int conexo){
    int i,j,soma = 0;
    int arestamult = 0;
    int laco = 0;


    for(i=0;i<numVertices-1;i++){
        for(j=1+i;j<numVertices;j++){
            if(matriz[i][j] > 1){
                printf("Aresta múltipla entre os vértices v%d e v%d\n",i+1,j+1);
                arestamult = 1;
            }
        }
    }
    puts("");
    for(i=0;i<numVertices;i++){
        for(j=0;j<numVertices;j++){
            if(matriz[i][i] != 0){
                printf("Laço no vértice v%d\n",i+1);
                laco=1;
                break;
            }
        }
    }
    puts("");

    if(laco == 0 && arestamult == 0){
        if(arestas == numVertices *(numVertices - 1)/2){
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
        	if(arestas == numVertices - 1){
            	printf("O grafo é uma árvore!\n");
        	}	
		}
    }
    else{
        printf("O grafo é desconexo!\n");
    }

}

FILE* abreArquivo(){
    FILE *arq;
     if((arq = fopen("A.txt","r")) == NULL){
        printf("Erro na abertura do arquivo!");
        exit(1);
    }
    return arq;
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL,"Portuguese");
    int i,j,numVertices,arestas,cont,num = 0;
    int conexo;
    int **matriz;
    int **matriz_quad;
    int **matriz_cubo;
    FILE* arq = abreArquivo();

    while((fscanf(arq,"%d",&num))!= EOF){
        cont++;
    }
    rewind(arq);
    numVertices = sqrt(cont); 
    matriz = leituraMatriz(numVertices);
    
    printf("========= Algoritmo de Grafos ============\n\n");
    printf(" Análise do Grafo:\n\n");

    for(i=0;i<numVertices;i++){
        for(j=0;j<numVertices;j++){
            fscanf(arq,"%d",&matriz[i][j]);
        }
    }
    matriz_quad = multi_matriz(matriz,matriz,numVertices);
    matriz_cubo = multi_matriz(matriz,matriz_quad,numVertices);
    
    int visitado[numVertices];
    int**adj = leituraMatriz(numVertices);

    for(i=0;i<numVertices;i++){
        for(j=0;j<numVertices;j++){
            adj[i][j] = -1;
        }
    }

    for(i=0;i<numVertices;i++){
        for(j=0;j<=numVertices;j++){
            if(matriz[i][j] != 0){
                adj[i][j] = j;
            }
        }
    }
    fclose(arq);

    conexo = buscaGrafo(0,visitado,numVertices,adj);
    puts("");
    graus(matriz,numVertices);
    puts("");
    arestas = contaArestas(matriz,numVertices);
    puts("");
    tipoGrafo(matriz,numVertices,arestas,conexo);
    puts("");
    passeio(matriz_cubo,numVertices);
    desalocaMatriz(matriz_quad,numVertices);
    desalocaMatriz(matriz_cubo,numVertices);
    desalocaMatriz(matriz,numVertices);
    system("pause");
    return 0;
}