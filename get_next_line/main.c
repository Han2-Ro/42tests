/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrother <hrother@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:59:26 by hrother           #+#    #+#             */
/*   Updated: 2023/10/02 18:50:55 by hrother          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void	readfile(const char *filename)
{
	int		fd;
	char	*line;

	line = "";
	fd = open(filename, O_RDONLY);
	while (line)
	{
		line = get_next_line(fd);
		printf("'%s'\n", line);
		free(line);
	}
	close(fd);
}

void	readfiles(char **filenames, int count)
{
	int		fds[count];
	char	*line;
	int		i;
	int		all_null;

	i = 0;
	line = "";
	while (i < count)
	{
		fds[i] = open(filenames[i], O_RDONLY);
		i++;
	}
	all_null = 0;
	while (!all_null)
	{
		all_null = 1;
		i = 0;
		while (i < count)
		{
			line = get_next_line(fds[i]);
			printf("'%s'\n", line);
			all_null  &= line == NULL;
			free(line);
			i++;
		}
	}
	i = 0;
	while (i < count)
	{
		close(fds[i]);
		i++;
	}
}

void	read_fd(int fd)
{
	char	*line;

	line = "";
	while (line)
	{
		line = get_next_line(fd);
		printf("'%s'\n", line);
	}
}

int	main(void)
{
	int fd = open("1.txt", O_RDONLY);
	char *line = get_next_line(fd);
	printf("'%s'\n", line);
	free(line);
	//char *filenames[] = {"testfile", "testfile2", "one_line_no_nl.txt", "many_lines.txt"};
	//readfiles(filenames, 4);
	//readfile("1.txt");
	//readfile("2.txt");
	//readfile("testfile2");
	//printf("'%s'\n", get_next_line(100));
	//printf("'%s'\n", get_next_line(-3));
	//printf("'%s'\n", get_next_line(42));
	//read_fd(42);
	//read_fd(0);
}
