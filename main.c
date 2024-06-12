#include "minishell.h"

char  **ft_slit(char *str, char c)
{
}

void  makenode(char *str, i, t_all *all)
{
}

void  parser(char *str, char separator, t_all *all)
{
  int i;
  int last_index;

  i = 0;
  last_index = 0;
  while (str[i])
  {
    if (str[i] == '|')
    {
      makenode(str, i, all);
    }
  }
}

int main(void)
{
  char *str;
  t_all all;
  t_malloc malloc_list;

  malloc_list = (t_malloc) malloc(sizeof(t_malloc));
  all = (t_all)allocator(sizeof(t_all), 1, &malloc_list);
  all.malloc_list = malloc_list;
  while (1) {
    str = readline("$ ");
    parser(str, '|', &all);
  }
}
