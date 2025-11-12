/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulam <ngulam@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:37:19 by ngulam            #+#    #+#             */
/*   Updated: 2025/11/11 21:49:12 by ngulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dest, char *src, size_t size);
int		ft_newline(char	*str);

void	ft_line(char **line, int fd)
{
	int		r;
	char	*buffer;

	while (r > 0)
	{
		buffer = malloc((BUFFER_SIZE + 1)* sizeof(char));
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
		*line = ft_strjoin(*line, buffer);
		if (ft_newline(buffer))
			break;
	}
}

char	*get_next_line(int fd)
{
	char		*line;
	// static int	last;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		// free(buffer);
		return (NULL);
	}
	line = "";
	ft_line(&line, fd);
	return (line);
}


int	main(void)
{
	int fd = open("helloworld.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
    close(fd);
}