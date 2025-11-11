/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulam <ngulam@student.42lehavre.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 10:07:47 by ngulam            #+#    #+#             */
/*   Updated: 2025/11/10 16:16:39 by ngulam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int main()
{
	int fd;
	char buf[255];
	
	fd = open("helloworld.txt", O_RDONLY);
	buf = get_next_line(fd);
	buf[chars_read] = '\0';
	printf("buf->%s\n", buf);
	return 0;
}
