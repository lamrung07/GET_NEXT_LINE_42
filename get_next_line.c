/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulam <ngulam@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:37:19 by ngulam            #+#    #+#             */
/*   Updated: 2025/11/12 18:12:42 by ngulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);
int		ft_newline(char	*str);

// char	*ft_resetline(static char *last)
// {
// 	last = 
// }

char	*ft_line(char **line, int fd)
{
	int		r;
	char	*buffer;

	r = 1;
	while (r > 0)
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
		{
			free(buffer);
			return (NULL);
		}
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		*line = ft_strjoin(*line, buffer);
		if (ft_strchr(buffer, '\n'))
		{
			return (ft_strchr(buffer, '\n'));
			break ;
		}
		free(buffer);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*last;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!last)
	{
		line = malloc(1 * sizeof(char));
		line[0] = '\0';
	}
	else
		line = last;
	last = ft_line(&line, fd);
	return (line);
}


int	main()
{
	int fd = open("helloworld.txt", O_RDONLY);
	int r = 1;
	while(r > 0)
		r = printf("%s",get_next_line(fd));
    close(fd);
	return(0);
}