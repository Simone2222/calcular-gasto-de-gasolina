#include <stdio.h>
#include <stdlib.h>
#include <math.h>


float custo;
float *custos   = NULL;
int origem , destino , vertices= 0;


void menu_mostrar (void);
void grafo_criar();
 void grafo_procurar(void);
 void dijkstra(int vertices, int origem, int destino, float *custos); 


int main(int argc, char**argv) {
  int opt = -1;
  do{
    menu_mostrar();
    scanf("%d", &opt);
    switch(opt){
      case 1:
       grafo_criar();
      break;
      case 2:
        if(vertices > 0 ){
          grafo_procurar();
        }
      break;
    }
    }while(opt != 0 );
  return 0;
}



void menu_mostrar(void){
  printf("algoritmo de dijkstra\n");
  printf("opcoes: \n");
  printf("\t 1 - adicionar um grafo\n");
  printf("\t 2 - procurar os menores caminhos no grafo\n");
  printf("\t 3 - sair do programa \n");

  }

void grafo_criar(void){
  do{
    printf("inserir o numero de vertices");
    scanf("%d", &vertices);
  }while(vertices < 3);

  if(!custos){
    free(custos);
  }
 custos=(float*)malloc(sizeof(float)*vertices*vertices);
  if(custos ==NULL){
    printf("memoria insuficiente");
    exit(-1);
  }


  for(int i = 0; i <= vertices * vertices; i++){
    custos[i]= -1;
 
    }
  
  do {
    system("clear");
    printf("entre com as arestas:\n");
    do {
      printf("origem 'entre 1 e %d ou 0 para sair' ", vertices);
      scanf("%d", &origem);
    } while (origem < 0 || origem > vertices);
    if(origem){
     do{
       printf("destino 'entre 1 e %d, menos %d' " , vertices, origem);
       scanf("%d" , &destino);
     }while (destino < 1 || destino > vertices || destino == origem);
  do{
    printf("custo positivo do vertice %d para o vertice %d: " , origem , destino);
    scanf("%f" , &custo);
  } while (custo < 0 );
    custos[(origem-1) * vertices + destino-1] = custo;
    }
  } while(origem);
}

  void grafo_procurar(void){
    int i, j;
    system("clear");
    printf("lista dos menores caminhos no grafo dado:\n");
    for(i=1; i<= vertices; i++){
      for(j=1; j<=vertices; j++){
        dijkstra(vertices, i, j,custos);
      }
    }
  }
 
void dijkstra(int vertices, int origem, int destino, float *custos){
    int i, v, cont=0;
   int *ant, *tmp;
   int *z;
    double min;
    double dist[vertices];

  
   ant= (int*) calloc (vertices, sizeof(int *));
   if(ant == NULL){
     printf("Erro: Memoria Insuficiente");
     exit(-1);
   }
   tmp= (int *) calloc (vertices, sizeof(int *));
   if (tmp == NULL){
     printf("Erro: Memoria Insuficiente");
     exit(-1);
   }
   z = (int *) calloc (vertices, sizeof(int *));
   if (z == NULL){
      printf("Erro: Memoria Insuficiente");
     exit(-1);
     }

    for(i=0; i < vertices; i++){
     if(custos[(origem-1) * vertices + i] !=-1){
    ant[i]=origem -1;
    dist[i]= custos[(origem -1)* vertices + i];
  }else {
    ant[i] = -1;
    dist[i]= HUGE_VAL;
  }
  z[i]= 0 ;
}

    z[origem-1] = 1;
    dist[origem-1] =  0;   
  
 
  do {
    min = HUGE_VAL;
    for (i=0; i<vertices; i++){
      if(!z[i]){
        if(dist[i] >= 0 && dist[i]< min){
          min = dist[i]; v=i;
        }
      }
    }
  
    if(min != HUGE_VAL && v != destino - 1 ){
      z[v] = 1;
      for(i=0; i< vertices; i++){
        if(!z[i]){
          if(custos[v*vertices+i] != -1 && dist[v]+custos[v*vertices+i] < dist[i]){
            dist[i]= dist[v] + custos[v*vertices+i];
            ant[i] = v;
          }
        }
      }
    }
  } while( v !=destino -1 && min != HUGE_VAL);


    printf("\t de %d para %d : \t", origem, destino);
    if(min == HUGE_VAL){
      printf("não existe\n");
      printf("\t custo \t- \n");
    } else {
      i = destino;
      i = ant[i-1];
      while(i != -1){
        tmp[cont]= i +1;
        cont++;
        i= ant[i];
      }
      for (i=cont; i>0; i--){
        printf("%d ->", tmp[i-1]);
        }
      printf("%d", destino);
        printf("\n\tcusto: %.3lf\n" , dist[destino-1]);
      }
  }