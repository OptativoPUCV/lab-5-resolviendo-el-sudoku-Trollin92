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
    for(int i=0; i<9; i++){
        int seen[10] = {0};
        for(int j=0; j<9; j++){
            int val = n->sudo[i][j];
            if(val != 0){
                if(seen[val]) return 0;
                seen[val] = 1;
            }
        }
    }
    for(int j=0; j<9; j++){
        int seen[10] = {0};
        for(int i=0; i<9; i++){
            int val = n->sudo[i][j];
            if(val != 0){
                if(seen[val]) return 0;
                seen[val] = 1;
            }
        }
    }
    for(int box_i=0; box_i<3; box_i++){
        for(int box_j=0; box_j<3; box_j++){
            int seen[10] = {0};
            for(int i=0; i<3; i++){
                for(int j=0; j<3; j++){
                    int val = n->sudo[box_i*3 + i][box_j*3 + j];
                    if(val != 0){
                        if(seen[val]) return 0;
                        seen[val] = 1;
                    }
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
    if (is_valid(aux)) pushBack(list,aux);
   }
   return list;
}


int is_final(Node* n){
  if(!is_valid(n)) return 0;
  for (size_t i = 0; i<9; i++){
    for (size_t j = 0; j<9; j++){
      if (n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *D=createStack();
  push(D,initial); //canned laughter
  while(!is_empty(D)){
    Node*aux = top(D);    // Me parece que está malo el pop para usarlo en pilas :(
    pop(D);
    (*cont)++;
    if (is_final(aux)) return aux;
    List *listaNodos = get_adj_nodes(aux);
    Node* nodoAdj = first(listaNodos);
    while (nodoAdj != NULL) {
      push(D, nodoAdj);
      nodoAdj = next(listaNodos);
    }
    free(aux);
    free(listaNodos);
  }
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