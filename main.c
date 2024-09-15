/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/15 21:51:19 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_spec	*get_specials(void)
{
	static t_spec	special_vars;

	return (&special_vars);
}

int	ft_lstsize(t_data *lst)
{
	if (lst == NULL)
		return (0);
	if (lst->next == NULL)
		return (1);
	return (1 + ft_lstsize(lst->next));
}

void	signal_handler(int sig)
{
	t_spec	*svars;

	svars = get_specials();
	svars->exit_status = 128 + sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	safer_signal(sig, signal_handler);
}

void	looper(void)
{
	char	*str;
	t_data	*tmp;

	str = NULL;
	while (1)
	{
		setup_signal_handler(0, signal_handler, SIG_IGN);
		str = readline("minishell $> ");
		if (str == NULL)
		{
			print_err("exit\n");
			exiter(get_specials()->exit_status);
		}
		add_history(str);
		tmp = lexer(str);
		free(str);
		if (tmp != NULL)
			execution(tmp, ft_lstsize(tmp));
		clean_pool();
		free_all_heap();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	get_specials()->exit_status = 0;
	env_table_to_list(env);
	init_shlvl();
	init_pwd_oldpwd();
	looper();
	return (0);
}
