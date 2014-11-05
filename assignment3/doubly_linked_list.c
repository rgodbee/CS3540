#include "list.h"
#include <stdlib.h>
#include <assert.h>

node* create_node (void* item)
{
  node* n = malloc (sizeof (node));
  n -> item = item;
  n -> next = NULL;
  n -> prev = NULL;
  return n;
}

list* create_list()
{
  list* l = malloc (sizeof(list));
  l -> front = NULL;
  l -> rear = NULL;
  l -> size = 0;
  return l;
}

int is_empty (const list* l)
{
  assert (l != NULL);
  return l -> size == 0;
}

int size (const list* l)
{
  assert (l != NULL);
  return l -> size;
}

void append (list* l, void* item)
{
  assert (l != NULL);
  node* n = create_node (item);
  if (is_empty (l))
  {
   l -> front = n;
   l -> rear = n;
  }
  else
  {
    n -> prev = l-> rear;
    l -> rear -> next = n;
    l -> rear = n;
  }
  l -> size++;
}

void prepend (list* l, void* item)
{
  assert (l != NULL);
  node* n = create_node (item);
  if (is_empty (l))
  {
    l -> front = n;
    l -> rear = n;
  }
  else
  {
    n -> next = l -> front;
    l -> front -> prev = n;
    l -> front = n;
  }
  l -> size++;
}

int insert (list* l, void* item, int index)
{
  assert (l != NULL);
  int result = index >= 0 && index <= size(l);
  if (result)
  {
    if (index == 0)
	prepend (l, item);
    else if (index == size(l))
      append (l, item);
    else
    {
      node* temp = l -> front;
      for (int i = 0; i < index - 1; i++)
	temp = temp -> next;
      node* n = create_node (item);
      n -> next = temp -> next;
      n -> prev = temp;
      n -> next -> prev = n;
      temp -> next = n;
      l -> size++;
    }
  }
  return result;
}

int remove_from_list (list* l, int index)
{
  assert (l != NULL);
  int result = index >= 0 && index < size(l);
  if (result)
  {
    node* n;
    if (index == 0)
    {
      n = l -> front;
      l -> front = n -> next;
      l -> front -> prev = NUll;
      if (l -> front == NULL)
	l -> rear = NULL;
    }
    else
    {
      node* temp = l -> front;
      for (int i = 0; i < index - 1; i++)
	temp = temp -> next;
      n = temp -> next;
      n -> next -> prev = temp;
      temp -> next = n -> next;
      if (temp -> next == NULL)
      {
	l -> rear -> prev = NULL;
	l -> rear = temp;
      }
    }
    free (n);
    l -> size--;
  }
  return result;
}

void* get (const list* l, int index)
{
 assert (l != NULL);
 void* result = NULL;
 if (index >= 0 && index < size(l))
 {
   node* temp = l -> front;
   for (int i = 0; i < index; i++)
     temp = temp -> next;
   result = temp -> item;
 }
 return result;
}

int set (list* l, void* item, int index)
{
  assert (l != NULL);
  int result = index >= 0 && index < size(l);
  if (result)
  {
    node* temp = l -> front;
    for (int i = 0; i < index; i++)
      temp = temp -> next;
    temp -> item = item;
  }
  return result;
}

void delete_list (list* l)
{
  assert (l != NULL);
  node* n = l -> front;
  for (int i = 0; i < size(l); i++)
  {
    node* temp = n;
    n -> prev = NULL;
    n = n -> next;
    free (temp);
  }
  free (l);
}
