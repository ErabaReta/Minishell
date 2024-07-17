#include "../minishell.h"

t_data	*ft_lstlast(t_data *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

t_data  *ft_lstnew()
{
  t_data *new;

  new = (t_data *)malloc(sizeof(t_data));
  new->prev = NULL;
  new->next = NULL;

  return (new);
}

void	ft_lstadd_back(t_data **lst, t_data *new)
{
	t_data	*last;

	if (lst != NULL)
	{
		if (*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			last = ft_lstlast(*lst);
			last->next = new;
      new->prev = last;
		}
	}
}
