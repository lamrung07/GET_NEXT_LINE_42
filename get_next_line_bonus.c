/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulam <ngulam@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 20:56:52 by ngulam            #+#    #+#             */
/*   Updated: 2025/12/04 21:12:40 by ngulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	res = ft_strdup(newline + 1);
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

char	*ft_getfull(int fd, char	*buffer_line, char	*buffer)
{
	int		r;

	r = 1;
	while (r)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			free(buffer);
			free(buffer_line);
			return (NULL);
		}
		if (r == 0)
			break ;
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
	static char	*buffer_line[1024];
	char		*res;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer_line[fd]);
		buffer_line[fd] = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer_line[fd] = ft_getfull(fd, buffer_line[fd], buffer);
	if (!buffer_line[fd])
		return (NULL);
	res = ft_get_line(buffer_line[fd]);
	buffer_line[fd] = ft_update(buffer_line[fd]);
	return (res);
}

// int	main(void)
// {
// 	int fd = open("helloworld.txt", O_RDONLY);
//  int fd1 = open("Daoduckinh.txt", O_RDONLY);
//  int fd2 = open("Tho.txt", O_RDONLY);
// 	int r = 1;
// 	printf("%s", get_next_line(fd));
//  printf("%s", get_next_line(fd2));
//  printf("%s", get_next_line(fd1));
//  printf("%s", get_next_line(fd1));
//  printf("%s", get_next_line(fd2));
//  printf("%s", get_next_line(fd));
//  printf("%s", get_next_line(fd));
//  printf("%s", get_next_line(fd1));
//  close(fd);
//  close(fd1);
//  close(fd2);
// 