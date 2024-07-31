#include "../minishell.h"


void	*quotes(char *str, int *start, int *end)
{
	int i;
	char quote;
	char *betwen_quotes;

	i = 0;
	quote = '\0';
	betwen_quotes = NULL;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			*start = i;
			*end = *start;
			break ;
		}
		i++;
	}
	while (str[i] != quote)
	{
		if (str[i] == '\0')
		{
			printf("quotes not closed\n");
			break ;
		}
		i++;
	}
	if (str[i] == quote && quote != '\0')
	{
		*end = i;
		betwen_quotes = ft_substr(str, *start, i - *start);
	}
	return (betwen_quotes);
}

char	*quotes_remove(char *str)
{
	int begin;
	char quote;
	int start;
	int end;
	char *cmd;
	char *mini_cmd;
	int i; // for testing whiles

	begin = 0;
	i = 0;
	start = 0;
	end = 0;
	cmd = NULL;
	while (str[start])
	{
		mini_cmd = NULL;
		if (str[start] == '\"' || str[start] == '\'')
		{
			quote = str[start];
			start++;
			end = start;
			while (str[end] != quote && str[end])
				end++;
			if (str[end] == '\0')
				return (NULL);
			mini_cmd = ft_substr(str, start - 1, (end - start) + 2);
			start = end + 1;
			cmd = ft_strnjoin(cmd, mini_cmd, 0);
			free(mini_cmd);
		}
		else
		{
			cmd = ft_strnjoin(cmd, str + start, 1);
			start++;
		}
	}
	if (cmd == NULL)
		return (str);
	return (cmd);
}
