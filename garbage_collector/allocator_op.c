#include "../minishell.h"

void	add_front(t_malloc **list, t_malloc *node)
{
	t_malloc	*tmp;

	tmp = *list;
	if (tmp == NULL)
		tmp = node;
	else
	{
		node->next = *list;
    *list = node;
	}
}
t_malloc	*new_node(void *ptr)
{
	t_malloc	*new;

	new = (t_malloc *)malloc(sizeof(t_malloc));
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

void	free_allocator(t_malloc **list)
{
	t_malloc	*tmp;

	tmp = *list;
	printf("in %p\n", tmp);
	while (*list)
	{
		free(tmp->ptr);
		*list = (*list)->next;
		free(tmp);
		tmp = *list;
	}
}
