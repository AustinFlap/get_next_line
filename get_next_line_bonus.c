/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:24:13 by avieira           #+#    #+#             */
/*   Updated: 2020/02/04 05:33:12 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*append_line(char *buff, char *line, int *new_line)
{
	int l_to_end;
	int l_buff;
	char *temp_line;
	char *temp_substr;
	
	l_to_end = ft_strl_spec(buff, '\n');
	l_buff = ft_strl_spec(buff, 0);
	temp_substr = ft_substr(buff, 0, l_to_end);
	temp_line = ft_strjoin(line, temp_substr);
	free(line);
	free(temp_substr);
	line = temp_line;
	*new_line = (buff[l_to_end] == '\n') ? 1 : 0;
	ft_memcpy(buff, buff + l_to_end + *new_line, l_buff - l_to_end - *new_line + 1);
	return (line);
}


int		get_next_line(int fd, char **line)
{
	static char		buff[MAX_FD][BUFFER_SIZE + 1];
	int				ret;
	int				new_line;

	if (!line || !(MAX_FD > fd))
		return (-1);
	*line = ft_strdup("");
	new_line = 0;
	while (!new_line)
	{
		if (!*buff[fd])
		{
			if ((ret = read(fd, buff[fd], BUFFER_SIZE)) == -1)
				return (ret);
			buff[fd][ret] = 0;
		}
		*line = append_line(buff[fd], *line, &new_line);
		if (ret == 0)
			new_line = 1;
	}
	if (!ret)
		return (0);
	return (1);
}
/*
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(void)
{
	int fd = open("files/42_char", O_RDONLY);
	char *line = 0;
	while (get_next_line(fd, &line))
		printf("%s\n", line);
	printf("%s\n", line);
}*/
