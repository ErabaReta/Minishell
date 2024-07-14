#include "../minishell.h"

int quote_checker(char *str)
{
  int i;
  int founded;

  founded = 0;
  i = 0;
  while (str[i])
  {
    if (str[i] == '\"')
      founded++;
    else if (str[i] == '\'')
      founded++;
    i++;
  }
  if (founded % 2 == 0)
    return (1);
  else
    return (0);
}

int lexer(char *str)
{
  int i;
  char **words;

  i = 0;
  if (quote_checker(str) == 0)
    printf("Syntax Error\n");
  words = ft_split(str, ' ');
  while (words[i])
  {
    printf("%s\n", words[i]);
    if (ft_strncmp(words[i], "|", 2) == 0)
      if (words[i + 1] == NULL)
        printf("Syntax Error\n");
    i++;
  }
  return (0);
}

