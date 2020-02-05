/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avieira <avieira@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 18:24:13 by avieira           #+#    #+#             */
/*   Updated: 2020/02/05 22:35:02 by avieira          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*append_line(char *buff, char *stock, int *new_line)
{
	int l_to_end;
	int l_buff;
	char *temp_stock;
	char *temp_substr;
	
	l_to_end = ft_strl_spec(buff, '\n');
	l_buff = ft_strl_spec(buff, 0);
	temp_substr = ft_substr(buff, 0, l_to_end);
	temp_stock = ft_strjoin(stock, temp_substr);
	free(stock);
	free(temp_substr);
	stock = temp_stock;
	*new_line = (buff[l_to_end] == '\n') ? 1 : *new_line;
	//if (!ret)
	//	new_line = 0;
	ft_memcpy(buff, buff + l_to_end + *new_line, l_buff - l_to_end - *new_line + 1);
	return (stock);
}


int		get_next_line(int fd, char **line)
{
	static char		buff[MAX_FD][BUFFER_SIZE + 1];
	int				ret;
	int				new_line;
	char *stock;

	if (!line || !(MAX_FD > fd) || !BUFFER_SIZE)
		return (-1);
	stock = ft_strdup("");
	new_line = 0;
	while (!new_line)
	{
		if (!*buff[fd])
		{
			if (!((ret = read(fd, buff[fd], BUFFER_SIZE)) > -1))
				return (ret);
			buff[fd][ret] = 0;
			new_line = (ret < BUFFER_SIZE) ? 1 : 0;
		}
		stock = append_line(buff[fd], stock, &new_line);
		//printf("|new_line%d| |ret%d|------\n%s\n", new_line, ret, buff[fd]);
	}
	*line = stock;
	if (JESAISPAS)
	{
		printf("|ret %d|   |new_line %d|\n", ret, new_line);
		return (0);
	}
	//printf("|%d|\n",ret);
	return (1);
}

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(void)
{
	int fd = open("files/mix_marge2", O_RDONLY);
	char *line;
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
}
