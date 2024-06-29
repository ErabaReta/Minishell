#include "../minishell.h"

t_data	*mini_parsing(char *cmd_line, int *count)
{
	char **cmds;
	int i;
	t_data	*prev;
	t_data	*next;
	t_data	*head;

	cmds = ft_split(cmd_line, '|');
	i = 0;
	prev = NULL;
	*count = 0;
	while (cmds[i] != NULL)
	{
		next = (t_data *)malloc(sizeof(t_data));
		next->cmd = cmds[i];
		next->next = NULL;
		if (prev == NULL)
		{
			// next->prev = NULL;
			head = next;
			// printf("cmd%d => %s \n", i, head->cmd);
		}
		else
		{
			// next->prev = prev;
			prev->next = next;
		}
			prev = next;
		*count += 1;
		i++;
	}
		// printf("===========================================\n");
		// t_data *tmp = head;
		// for (int j = 1; tmp != NULL;j++)
		// {
		// 	printf("cmd%d => %s \n", j, tmp->cmd);
		// 	tmp = tmp->next;
		// }
		// printf("===========================================\n");
	return (head);
}
