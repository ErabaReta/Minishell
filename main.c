/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayechcha <ayechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:01:09 by eouhrich          #+#    #+#             */
/*   Updated: 2024/09/13 17:21:31 by ayechcha         ###   ########.fr       */
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
	t_spec	*special_vars;
	t_env	*env_node;
	int		new_shlvl;

	(void)ac;
	(void)av;
	(void)special_vars;
	special_vars = get_specials();
	special_vars->exit_status = 0;
	env_table_to_list(env);
	env_node = env_search("SHLVL");
	if (env_node == NULL)
	{
		env_lst_addback(env_new_node(ft_strdup2("SHLVL"), ft_strdup2("1")));
	}
	else
	{
		new_shlvl = ft_atoi(env_node->value);
		if (new_shlvl <= 0)
			new_shlvl = 0;
		if (new_shlvl >= 999)
		{
			print_err("minishell: warning: shell level (");
			print_err(ft_itoa(new_shlvl + 1, 0));
			print_err(") too high, resetting to 1\n");
			new_shlvl = 0;
		}
		free(env_node->value);
		env_node->value = ft_itoa(new_shlvl + 1, 1);
	}
	env_node = env_search("PWD");
	special_vars->pwd = getcwd(NULL, 0);
	if (special_vars->pwd == NULL)
	{
		perror("minishell: error retrieving current directory: getcwd: cannot access parent directories");
	}
	else if (env_node == NULL)
	{
		env_lst_addback(env_new_node(ft_strdup2("PWD"),
				ft_strdup2(special_vars->pwd)));
	}
	else
	{
		free(env_node->value);
		env_node->value = ft_strdup2(special_vars->pwd);
	}
	env_node = env_search("OLDPWD");
	if (env_node == NULL)
		env_lst_addback(env_new_node(ft_strdup2("OLDPWD"), NULL));
	looper();
	return (0);
}
