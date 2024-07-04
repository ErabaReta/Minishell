#include "../minishell.h"




//	create a liked list data out of commmand line and sets the count variable size of the lined list
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
	head = NULL; // for wall wextra werror
	while (cmds[i] != NULL)
	{
		next = (t_data *)malloc(sizeof(t_data));
		next->cmd = cmds[i];
		// next->in_rederiction = char_in_cmd(cmds[i], '<');//
		// next->out_rederiction = char_in_cmd(cmds[i], '>');//
		redirector(next, cmds[i]);
		next->next = NULL;
		if (prev == NULL)
		{
			next->prev = NULL;
			head = next;
			// printf("cmd%d => %s \n", i, head->cmd);
		}
		else
		{
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
