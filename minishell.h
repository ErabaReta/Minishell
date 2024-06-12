#ifndef MINISHELL_H

#include <readline/readline.h>

typedef struct s_malloc {
  void *ptr;
  struct s_malloc *next;
}               t_malloc;
typedef struct s_list
{
  struct list *prev;
  char *centent;
  struct list *next;
}             t_list;

typedef struct s_all {
  t_malloc  *malloc_list;
  t_list    *list;
};

void  add_front(t_malloc **list, t_malloc *node);
t_malloc *new_node(void *ptr);
void  *allocator(int size, int time, t_malloc *malloc_list)
void  free_allocator(t_malloc **list)

#endif // !MINISHELL_H
