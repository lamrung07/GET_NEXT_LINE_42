/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulam <ngulam@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:37:19 by ngulam            #+#    #+#             */
/*   Updated: 2025/12/04 19:47:32 by ngulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*ft_merge(char	*buffer_line, char	*buffer)
{
	char	*tmp;

	if (!buffer_line)
		tmp = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(buffer_line, buffer);
		free(buffer_line);
	}
	return (tmp);
}

char	*ft_update(char	*buffer_line)
{
	char	*res;
	char	*newline;

	newline = ft_strchr(buffer_line, '\n');
	if (!newline)
	{
		free(buffer_line);
		return (NULL);
	}
	res = ft_strdup(newline);
	free(buffer_line);
	return (res);
}

char	*ft_get_line(char	*buffer_line)
{
	char	*res;
	int		i;

	i = 0;
	if (!buffer_line[i])
		return (NULL);
	while (buffer_line[i] && buffer_line[i] != '\n')
		i++;
	if (buffer_line[i] == '\n')
		i += 1;
	res = malloc((i + 1) * sizeof(char));
	i = 0;
	while (buffer_line[i] && buffer_line[i] != '\n')
	{
		res[i] = buffer_line[i];
		i++;
	}
	if (buffer_line[i] && buffer_line[i] == '\n')
	{
		res[i] = buffer_line[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_getfull(int fd, char	*buffer_line)
{
	int		r;
	char	*buffer;

	r = 1;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	while (r)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			free(buffer);
			free(buffer_line);
			return (NULL);
		}
		buffer[r] = '\0';
		buffer_line = ft_merge(buffer_line, buffer);
		if (ft_strchr(buffer_line, '\n'))
			break ;
	}
	free(buffer);
	buffer = NULL;
	return (buffer_line);
}

char	*get_next_line(int fd)
{
	static char	*buffer_line;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer_line);
		buffer_line = NULL;
		return (NULL);
	}
	buffer_line = ft_getfull(fd, buffer_line);
	if (!buffer_line)
		return (NULL);
	res = ft_get_line(buffer_line);
	buffer_line = ft_update(buffer_line);
	return (res);
}

int	main(void)
{
	int fd = open("helloworld.txt", O_RDONLY);
	int r = 1;
	while(r <= 4)
	{	
		printf("%s", get_next_line(fd));
		r++;
	}
    close(fd);
}