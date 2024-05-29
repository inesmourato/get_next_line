/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibravo-m <ibravo-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:27:05 by ibravo-m          #+#    #+#             */
/*   Updated: 2024/05/29 15:30:35 by ibravo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_buffer(int fd, char *left_c, char *buffer);
static char	*set_line(char *line_buffer);

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*left_c;
	char		*text;

	left_c = NULL;
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	text = fill_buffer(fd, left_c, buffer);
	free(buffer);
	buffer = NULL;
	if (!text)
		return (NULL);
	left_c = set_line(text);
	return (text);
}

static char	*fill_buffer(int fd, char *left_c, char *buffer)
{
	ssize_t	b_read;
	char	*tmp;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(left_c);
			return (NULL);
		}
		else if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		if (!left_c)
			left_c = ft_strdup("");
		tmp = left_c;
		left_c = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left_c);
}

static char	*set_line(char *line_buffer)
{
	ssize_t	i;
	char	*left_c;

	i = 0;
	while (line_buffer[i] != '\n' && line_buffer[i] != '\0')
		i++;
	if (line_buffer[i] == 0 && line_buffer[i + 1] == 0)
		return (NULL);
	left_c = ft_substr(line_buffer, i + 1, ft_strlen(line_buffer) - i);
	if (*left_c == 0)
	{
		free(left_c);
		return (NULL);
	}
	return (left_c);
}

// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	fd = open("test.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// }