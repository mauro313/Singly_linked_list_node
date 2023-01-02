#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "singly_linked_list_node.h"

void print_int(t_elem value);
int compare_int(t_elem value_1,t_elem value_2);
sll_node_t* sll_node_min(sll_node_t* head,int (*compare)(t_elem,t_elem));
sll_node_t* sll_node_max(sll_node_t* head,int (*compare)(t_elem,t_elem));
void sll_node_add_value_sorted(sll_node_t** head,t_elem value,int(*compare)(t_elem,t_elem));
void sll_node_delete_all(sll_node_t** head);


int main(void){
  sll_node_t* head = NULL;
  
  srand(time(NULL));

  //inserto 10 valores de forma ordenanda
  for(int i=0;i<10;i++){
    sll_node_add_value_sorted(&head,rand()%50,compare_int);
  }
  //imprimo todos los valores
  sll_node_all_printf_recursive(head,print_int);
  
  //obtengo el maximo y el minimo y los imprimo
  sll_node_t* max = sll_node_max(head,compare_int);
  sll_node_t* min = sll_node_min(head,compare_int);
  
  printf("max value:");
  sll_node_printf(max,print_int);
  printf("\nmin value:");
  sll_node_printf(min,print_int);
  
  //elimino los nodos
  sll_node_delete_all(&head);
  return 0;    
}

//******************ejemplos de procedimientos y funciones del uso de dicha implementacion***************//


//procedimiento para insertar un nodo en una lista de forma ordenada. Forma recursiva
void sll_node_add_value_sorted(sll_node_t** head,t_elem value,int (*compare)(t_elem,t_elem)){
  if(*head != NULL && compare(sll_node_get_value(*head),value)<0){
    sll_node_add_value_sorted(sll_node_get_next_referece(*head),value,compare);  
  }
  else{
    sll_node_t* new_node = sll_node_new(value);
    if(*head!=NULL){
      sll_node_t** auxiliar = head;
      sll_node_link_node(&new_node,*auxiliar);
      *auxiliar = new_node; 
    }
    else{
      *head = new_node;  
    }
  }
}


// retorna al minimo de una lista. Forma recursiva
sll_node_t* sll_node_min(sll_node_t* head,int(*compare)(t_elem,t_elem)){
  sll_node_t* result = NULL;
  if(head != NULL){
    result = head; 
    sll_node_t* auxiliar = sll_node_min(head->next,compare);
    if((auxiliar!=NULL) && (compare(auxiliar->value,result->value)<0)){
      result = auxiliar; 
    }
  }
  return result;
}

// retorna el maximo de una lista. Forma recursiva.
sll_node_t* sll_node_max(sll_node_t* head,int(*compare)(t_elem,t_elem)){
  sll_node_t* result = NULL;
  if(head!=NULL){
    result = head;
    sll_node_t* auxiliar = sll_node_max(head->next,compare);
    if((auxiliar!=NULL) && (compare(auxiliar->value,result->value)>0)){
      result = auxiliar;   
    }
  }
  return result;
}

// procedimiento para eliminar todos los nodos de una lista y liberar la memoria reservada
void sll_node_delete_all(sll_node_t** head){
  if(*head != NULL){
    sll_node_delete_all(&(*head)->next);
    if(*head!=NULL){
      sll_node_free(head);
    }
  }
}

void print_int(t_elem value){
  printf(" %i ",value);    
}

int compare_int(t_elem value_1,t_elem value_2){
  return value_1-value_2;    
}

