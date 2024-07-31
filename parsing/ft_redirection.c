#include "../minishell.h"


void	redirection(t_data *data)
{
	int i;
	int j;
	int passed;
	char **reds_in;
	char **reds_out;
	char **cmds;

	reds_in = ft_split("< <<", ' ');
	reds_out = ft_split("> >>", ' ');
	passed = -1;
	while (data)
	{
		i = 0;
		cmds = NULL;
		while (data->args && data->args[i])
		{
			j = 0;
			while (reds_in[j])
			{
				if (ft_strncmp(data->args[i], reds_in[j], 2) == 0)
				{
					passed = 1;
					data->in_files = add_last(&data->in_files,
							make_new(data->args[i], data->args[i + 1]));
					i++;
				}
				j++;
			}
			j = 0;
			while (reds_out[j])
			{
				if (ft_strncmp(data->args[i], reds_out[j], 2) == 0)
				{
					passed = 1;
					data->out_files = add_last(&data->out_files,
							make_new(data->args[i], data->args[i + 1]));
					i++;
				}
				j++;
			}
			if (passed == -1)
				cmds = ft_tablejoin(cmds, data->args[i]);
			passed = -1;
			i++;
		}
		free_table(data->args);
		data->args = ft_tabledup(cmds);
		free_table(cmds);
		data = data->next;
	}
}
