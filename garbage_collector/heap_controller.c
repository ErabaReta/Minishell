/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_controller.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:48:12 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/07 12:33:34 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_heap	**get_heap()
{
	static t_heap	*head;
	
	return (&head);
}

// add front
void	add_to_heap(t_heap *new)
{
	t_heap **heap;

	heap = get_heap();
	if (new != NULL)
	{
		new->next = *heap;
		*heap = new;
	}
}

// allocat memory and save to free later, returns pointer (void *) to the allocated memory
void	*mallocate(size_t	size)
{
	t_heap	*new;

	new = (t_heap *)malloc(sizeof(t_heap)); // TODO protect fail
	new->ptr = malloc(size);// TODO protect fail
	add_to_heap(new);
	return (new->ptr);
}

// free all alloccated memory by heap controller
void	free_all_heap()
{
	t_heap	**heap;
	t_heap	*tmp;

	clean_pool();//<- close all fd opened
	heap = get_heap();
	while (*heap != NULL)
	{
		tmp = *heap;
		(*heap) = (*heap)->next;
		free(tmp->ptr);
		free(tmp);
	}	
}
// free specefic ptr allocated by heap controller(still on test phase)
void	ft_free(void *ptr)
{
	t_heap	**heap;
	t_heap	*tmp;
	t_heap	*to_delete;
	
	heap = get_heap();
	tmp = *heap;
	if (tmp == NULL)
		return ;
	if (ptr == tmp->ptr)
	{
		*heap = tmp->next;
		free(tmp->ptr);
		free(tmp);
		return ;
	}
	while (tmp != NULL && tmp->next != NULL)
	{
		if (tmp->next->ptr == ptr)
		{
			to_delete = tmp->next;
			tmp->next = tmp->next->next;
			free(to_delete->ptr);
			free(to_delete);
			return ;
		}
		tmp = tmp->next;
	}
}
// == for testing ============================================================
// #include <stdio.h>

// int main()
// {
// 	int **matrix;

// 	matrix = (int **)mallocate(sizeof(int *) * 10);
// 	for (int i =0;i < 10; i++)
// 	{
// 		matrix[i] = (int *)mallocate(sizeof(int));	
// 	}
// 	//=======================
// 	for (int i =0;i < 10; i++)
// 	{
// 		matrix[i][0] = i;	
// 	}
	
// 	for (int i =0;i < 10; i++)
// 	{
// 		printf("nbr[%d] => %d", i, matrix[i][0]);
// 	}
// 	free_all_heap();
// }