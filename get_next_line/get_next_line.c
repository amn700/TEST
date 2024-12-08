/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 16:58:55 by marvin            #+#    #+#             */
/*   Updated: 2024/12/08 05:36:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_append(int fd, char *st_buffer, char *buffer)
{
	int		bytes_read;
	char	*temp;

	while (1)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		if (st_buffer == NULL)
			temp = ft_strjoin("", buffer);
		else
			temp = ft_strjoin(st_buffer, buffer);
		free(st_buffer);
		if (temp == NULL)
			return (st_buffer = NULL, NULL);
		st_buffer = temp;
		if (ft_strchr(st_buffer, '\n') != -1)
			break ;
	}
	return (st_buffer);
}

char	*ft_copy_until_new_line(char *st_buffer, char *line)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (st_buffer[len] && st_buffer[len] != '\n')
		len++;
	if (st_buffer[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	while (st_buffer[i] && st_buffer[i] != '\n')
	{
		line[i] = st_buffer[i];
		i++;
	}
	if (st_buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_copy_after_newline(char *st_buffer)
{
	int		i;
	int		j;
	char	*new_st_buffer;
	int 	len;

	i = 0;
	j = 0;
	len = ft_strlen(st_buffer);
	while (st_buffer[i] && st_buffer[i] != '\n')
		i++;
	if (st_buffer[i] == '\n')
		i++;
	if (i == len)
		return (free(st_buffer), st_buffer = NULL, NULL);
	new_st_buffer = malloc(len - i + 1);
	if (new_st_buffer)
	{
		while (st_buffer[i + j] && st_buffer[i] != '\n')
		{
			new_st_buffer[j] = st_buffer[i + j];
			j++;
		}
		new_st_buffer[j] = '\0';
	}
	return (free(st_buffer), st_buffer = NULL, new_st_buffer);
}

char	*get_next_line(int fd)
{
	static char	*st_buffer;
	char		*buffer;
	char		*line;

	buffer = NULL;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, buffer, 0) < 0)
		return (free(st_buffer), st_buffer = NULL, NULL);
	buffer = malloc (BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	st_buffer = ft_read_and_append(fd, st_buffer, buffer);
	free(buffer);
	buffer = NULL;
	if (!st_buffer)
		return (NULL);
	line = ft_copy_until_new_line(st_buffer, line);
	if (!line)
		return (NULL);
	
	st_buffer = ft_copy_after_newline(st_buffer);
	return (line);
}

// int main ()
// {
//     int fd = open("test.txt", O_RDONLY);
//     printf("%s", get_next_line(fd));
//     printf("%s", get_next_line(fd));

// }

// int main ()
// {
//     static char    *st_buffer = NULL;
//     char           *line = NULL;
//     char           *buffer = NULL;

//     int fd = open("test.txt", O_RDONLY);
//     if (fd < 0 || BUFFER_SIZE <= 0)
//         return (0);

//     buffer = malloc(BUFFER_SIZE + 1);
//     if (buffer == NULL)
//         return (0);
//     // int i = 0;
//     // while (i < BUFFER_SIZE)
//     // {
//     //     buffer[i] = 'a';
//     //     i++;
//     // }
//     // buffer[BUFFER_SIZE] = '\0';
//     // printf("%s\n%i\n", buffer , i);

//     st_buffer = ft_read_and_append(fd, st_buffer, buffer);
//     // printf("%s\n", st_buffer);
//     if (st_buffer == NULL)
//         return (0);

//     line = ft_copy_until_new_line(st_buffer, line);
//     printf("%s\n", line);
//     st_buffer = ft_copy_after_newline(st_buffer);
//     printf("%s\n", st_buffer);
//     // close(fd);
//     return (0);
// }
