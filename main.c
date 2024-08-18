/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/08/17 20:21:36 by ayechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_spec	*get_specials()
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

void signal_handler(int sig)
{
	t_spec *svars = get_specials();
	// (void)info;
	// (void)context;

	svars->exit_status = 128 + sig;
	
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line ("", 0);
		rl_redisplay();
	}
}

void	looper()
{
	char *str;
	t_data *tmp;
	t_spec *svars = get_specials();

	str = NULL;
	while (1)
	{
		setup_signal_handler(0, signal_handler, SIG_IGN);
		str = readline("minishell $> ");
		if (str == NULL)
		{
			print_err("exit\n");
			exiter(svars->exit_status);
		}
		add_history(str);
		tmp = lexer(str);
		free(str);
		if (tmp != NULL)
			execution(tmp, ft_lstsize(tmp));
		free_all_heap();
	}

}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_spec *special_vars;
	
	(void)special_vars;
	special_vars = get_specials();
	special_vars->exit_status = 0;
	special_vars->shlvl = 0;
	env_table_to_list(env);
	printf("shlvl = %s\n", env_search("SHLVL")->value);
	special_vars->shlvl = ft_atoi(env_search("SHLVL")->value) + 1;
	env_search("SHLVL")->value = ft_itoa(special_vars->shlvl, 1);
	looper();
	return (0);
}
