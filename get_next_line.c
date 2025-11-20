/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulam <ngulam@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 09:37:19 by ngulam            #+#    #+#             */
/*   Updated: 2025/11/20 18:00:05 by ngulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s);
int		ft_newline(char	*str);

static	char	*ft_line(char **line, int fd, char	*buffer)
{
	int		r;

	r = 1;
	while (r)
	{
		if (!buffer)
			return (NULL);
		r = read(fd, buffer, BUFFER_SIZE);
		buffer[r] = '\0';
		if (r <= 0)
			break ;
		*line = ft_strjoin(*line, buffer);
		if (ft_strchr(buffer, '\n'))
			return (ft_strchr(buffer, '\n'));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*last;
	char		*buffer;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free (last);
		free (buffer);
		return (NULL);
	}
	if (last == NULL)
		line = "";
	else
		line = ft_strdup(last);
	last = ft_strdup(ft_line(&line, fd, buffer));
	free(buffer);
	buffer = NULL;
	return (line);
}

// int	main(void)
// {
// 	int fd = open("helloworld.txt", O_RDONLY);
// 	int r = 1;
// 	while(r)
// 	{	
// 		r = printf("%s", get_next_line(fd));
// 	}
//     close(fd);
// }