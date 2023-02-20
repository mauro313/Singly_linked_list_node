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

  //insert 10 elements in a sorted linked list node.
  for(int i=0;i<10;i++){
    sll_node_add_value_sorted(&head,rand()%50,compare_int);
  }
  
  // print all the values.
  sll_node_all_printf_recursive(head,print_int);
  printf("\n");

  //get the max and the min of a list of linked list node.
  sll_node_t* max = sll_node_max(head,compare_int);
  sll_node_t* min = sll_node_min(head,compare_int);
  
  printf("max value:");
  sll_node_printf(max,print_int);
  printf("\nmin value:");
  sll_node_printf(min,print_int);
  
  //delete all the nodes an free the memory.
  sll_node_delete_all(&head);
  return 0;    
}

//******************EXAMPLES OF PROCEDURES AND FUNCTIONS THAT USES THE IMPLEMENTATION**************//


/**
 * @brief add a element in a list of linked nodes in a sorted form.
 * 
 * @param head 
 * @param value 
 * @param compare 
 */
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


/**
 * @brief get the minimum element of a list of linked nodes.
 * 
 * @param head 
 * @param compare 
 * @return sll_node_t* 
 */
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

/**
 * @brief get the maximum element of a list of linked nodes.
 * 
 * @param head 
 * @param compare 
 * @return sll_node_t* 
 */
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

/**
 * @brief erase all nodes in a list of linked node.
 * 
 * @param head 
 */
void sll_node_delete_all(sll_node_t** head){
  if(*head != NULL){
    sll_node_delete_all(&(*head)->next);
    if(*head!=NULL){
      sll_node_free(head);
    }
  }
}

/**
 * @brief auxiliar procedure to print a element.
 * 
 * @param value 
 */
void print_int(t_elem value){
  printf(" %i ",value);    
}

/**
 * @brief auxiliar function to compare elements.
 * 
 * @param value_1 
 * @param value_2 
 * @return int 
 */
int compare_int(t_elem value_1,t_elem value_2){
  return value_1-value_2;    
}

