/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eouhrich <eouhrich@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:01:08 by eouhrich          #+#    #+#             */
/*   Updated: 2024/05/30 15:43:36 by eouhrich         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*deviser(char **big_string)
{
	int		newl_i;
	char	*rest;
	char	*tmp;

	newl_i = ft_strlen(*big_string, 1);
	if (newl_i == -1)
		rest = ft_strdup("");
	else
	{
		rest = ft_substr(*big_string, newl_i + 1, ft_strlen(*big_string, 2));
		tmp = *big_string;
		*big_string = ft_substr(*big_string, 0, newl_i + 1);
		free(tmp);
	}
	return (rest);
}

int	reader(char **buffer, int *readed, char **big_string, int fd)
{
	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (*buffer == NULL)
		return (0);
	*readed = read(fd, *buffer, BUFFER_SIZE);
	if (*buffer == NULL || *readed <= 0)
	{
		free(*buffer);
		if (*readed == 0 && *big_string != NULL)
			return (1);
		free(*big_string);
		return (0);
	}
	buffer[0][*readed] = '\0';
	*big_string = ft_strjoin(*big_string, *buffer);
	if (ft_strlen(*buffer, 1) != -1 || *readed != (ssize_t)BUFFER_SIZE)
	{
		free(*buffer);
		return (1);
	}
	free(*buffer);
	return (2);
}

int	rester(char **big_string, char **rest)
{
	*big_string = ft_strjoin(*big_string, *rest);
	free(*rest);
	if (*big_string == NULL)
		return (0);
	*rest = NULL;
	if (ft_strlen(*big_string, 1) != -1)
	{
		*rest = deviser(big_string);
		if (*rest == NULL || *big_string == NULL)
			return (0);
		if (ft_strlen(*rest, 2) == 0)
		{
			free(*rest);
			*rest = NULL;
		}
		big_string[0][ft_strlen(*big_string, 2)] = '\0';
		return (1);
	}
	return (2);
}

int	return_handler(char **big_string, char **rest, char **buffer, int fd)
{
	int	readed;
	int	returned;

	*big_string = NULL;
	if (*rest != NULL)
	{
		returned = rester(big_string, rest);
		if (returned == 0)
			return (0);
		if (returned == 1)
			return (1);
	}
	readed = 1;
	while (readed > 0)
	{
		returned = reader(buffer, &readed, big_string, fd);
		if (returned == 1)
			break ;
		if (returned == 0)
			return (0);
	}
	*rest = deviser(big_string);
	if (*rest == NULL)
		return (0);
	return (2);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*big_string;
	int			returned;
	static char	*rest[1048576];

	if (BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT_MAX || fd < 0 || 1048576 <= fd)
		return (NULL);
	returned = return_handler(&big_string, &rest[fd], &buffer, fd);
	if (returned == 0)
		return (NULL);
	if (returned == 1)
		return (big_string);
	if (ft_strlen(rest[fd], 2) == 0)
	{
		free(rest[fd]);
		rest[fd] = NULL;
	}
	big_string[ft_strlen(big_string, 2)] = '\0';
	return (big_string);
}
