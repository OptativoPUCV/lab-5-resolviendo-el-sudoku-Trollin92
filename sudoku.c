#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    Node*aux = (Node*) malloc(sizeof(Node));
    int k,p,t,h;
    for(k = 1; k<10; k++){
      for(p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        
        aux->sudo[i%3][j%3] = n->sudo[i][j];
      }
      List*lista = createList();
      for(t=0;t<4;t++){
        for(h=0;h<4;t++){
          while((lista)!= NULL){
            if (aux->sudo[t][h] == lista){
              return 0;
            }
            pushFront(lista,aux->sudo[t][h]);
            lista = next(lista);
          }
        }
      }
    }
    return 1;
}

List* get_adj_nodes(Node* n){
   List* list=createList();
   Node * aux = (Node*) malloc(sizeof(Node));
   int x,y;
   int fin=0;
   for (size_t i = 0; i<9; i++){
    if (fin==1) break;
    for (size_t j = 0; j<9; j++){
      if (n->sudo[i][j] == 0){
        x=i;
        y=j;
        fin = 1;
        break;
      }
    }
   }
   for (int num = 1; num<=9; num++){
    aux = copy(n);
    aux->sudo[x][y] = num;
    if (is_valid(aux)) pushFront(list,aux);
   }
   return list;
}


int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/