/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibravo-m <ibravo-m@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:27:05 by ibravo-m          #+#    #+#             */
/*   Updated: 2024/05/21 14:47:45 by ibravo-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}
char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1 * sizeof(char));
	if (!new_str)
		return (NULL);
	while (s1 && s1[j])
		new_str[i++] = s1[j++];
	j = 0;
	while (s2 && s2[j] && s2[j] != '\n')
		new_str[i++] = s2[j++];
	if (s2[j] == '\n')
		new_str[i++] = '\n';
	new_str[i] = '\0';
	free(s1);
	return (new_str);
}
int	increment(char *buffer)
{
	int	new_line;
	int	i;
	int	j;

	new_line = 0;
	i = 0;
	j = 0;
	while (buffer[i])
	{
		if (new_line)
			buffer[j++] = buffer[i];
		if (buffer[i] == '\n')
			new_line = 1;
		buffer[i++] = '\0';
	}
	return (new_line);
}
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[0])
		read(fd, buffer, BUFFER_SIZE);
	while (buffer[0])
	{
		str = ft_strjoin(str, buffer);
		if (!str)
			return (NULL);
		if (increment(buffer) == 1)
			break ;
		if (read(fd, buffer, BUFFER_SIZE) < 0)
		{
			free(str);
			return (NULL);
		}
	}
	return (str);
}

int	main(void)
{
	char *line;

	FILE *file;
	file = fopen("test.txt", "r");
	if (!file)
	{
		perror("error opening file");
		return (1);
	}
	while ((line = get_next_line(fileno(file))) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("\nBUFFER_SIZE: %i\n", BUFFER_SIZE);
	fclose(file);
	return (0);
}