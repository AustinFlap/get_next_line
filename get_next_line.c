/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:24:13 by avieira           #+#    #+#             */
/*   Updated: 2020/02/03 05:19:40 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int		get_len_to_end(char *str)
{
	int				l;

	l = 0;
	while (*str && *str++ != '\n')
		l++;
	return (l);
}

char	*append_line(char *buff, char *stock, int ret)
{
	int len;
	char *temp_stock;
	char *temp_substr;
	int		new_line;

	len = get_len_to_end(buff);
	temp_stock = stock;
	temp_substr = ft_substr(buff, 0, len);
	stock = ft_strjoin(temp_stock, temp_substr);
	if (temp_stock)
		free(temp_stock);
	if (temp_substr)
		free(temp_substr);
	new_line = (buff[len] == '\n') ? 1 : 0;
	ft_memmove(buff, buff + len + new_line, ret - len - new_line);
	buff[ret - len - new_line] = 0;
	if (new_line)
		return (stock);
	return (0);
}


int		get_next_line(int fd, char **line)
{
	static char		buff[MAX_FD][BUFFER_SIZE];
	char			*stock;
	int				ret;

	if (!line || !(MAX_FD > fd))
		return (-1);
	stock = ft_strdup("");
	printf("|%p|\n", stock);
	*line = 0;
	while (!*line)
	{
		if (!*buff[fd])
		{
			if (!((ret = read(fd, buff[fd], BUFFER_SIZE)) > 0))
				return (ret);
			buff[fd][ret] = 0;
		}
		*line = append_line(buff[fd], stock, ret);
	}
	return (1);
}

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(void)
{
	int fd = open("files/mix_marge2", O_RDONLY);
	char *line = 0;

	while (get_next_line(fd, &line))
		printf("%s\n", line);
}
