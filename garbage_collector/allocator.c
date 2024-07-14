#include "../minishell.h"

void  *allocator(int size, int time, t_malloc *malloc_list)
{
  void *ptr;
  t_malloc *new;

  ptr = malloc(size * time);
  if (ptr == NULL)
      return (NULL);
  new = new_node(ptr);
  add_front(&malloc_list, new);
  return (ptr);
}
