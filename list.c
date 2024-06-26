#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
  List* list = (List*)malloc(sizeof(List));
  list->head = NULL;
  list->tail = NULL;
  list->current = NULL;
  return list;
}

void * firstList(List * list) {
  if(list == NULL || list->head == NULL)
    return NULL;
  list->current = list->head;
  return list->current->data;
}

void * nextList(List * list) {
  if(list == NULL || list->current == NULL || list->current->next == NULL)
    return NULL;
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if(list == NULL || list->head == NULL)
    return NULL;
  while(list->current->next != NULL)
    list->current =  list->current->next;
  return list->current->data;
}

void * prevList(List * list) {
  if(list == NULL || list->current == NULL || list->current->prev == NULL)
    return NULL;
  list->current = list->current->prev;
  return list->current->data; 
}

void pushFront(List * list, void * data) 
{
  Node *newNode = createNode(data);
  newNode->data = data;
  newNode->prev = NULL;
  newNode->next = list->head;
  if(list->head)
    list->head->prev = newNode;
  list->head = newNode;
  if(list->tail == NULL)
    list->tail = newNode;
}

void pushBack(List * list, void * data) {
  Node *aux = list->head;
  while(aux->next != NULL)
    aux = aux->next;
  list->current = list->tail;
  if(list->current != NULL)
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node *newNode = createNode(data);
  newNode->prev = list->current;
  newNode->next = list->current->next;
  newNode->prev->next = newNode;
  list->tail = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  Node *left = list->current->prev;   
  Node *right = list->current->next;
  if(left != NULL)
    left->next = right;
  else
    list->head = right;
  if(right != NULL)
    right->prev = left;
  else
    list->tail = left;
  
  
  void *dato = list->current->data;
  free(list->current);
  list->current=NULL;
  
  return dato;
}

  


void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}