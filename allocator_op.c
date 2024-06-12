#include "minishell.h"

void  add_front(t_malloc **list, t_malloc *node)
{
  t_malloc *tmp;

  tmp = *list;
  if (*tmp == NULL)
    *tmp = node;
  else {
    *tmp->prev = node;
    node->next = *list;
  }
}
t_malloc *new_node(void *ptr)
{
  t_malloc *new;

  new = (t_malloc *)malloc(sizeof(t_malloc));
  new->prev = NULL;
  new->ptr = ptr;
  new->next = NULL;
  return (new);
}

void  free_allocator(t_malloc **list)
{
  t_malloc *tmp;

  tmp = *list;
  while (*list)
  {
    free(tmp->ptr);
    free(tmp);
    *list = *list->next;
    tmp = *list;
  }
}

