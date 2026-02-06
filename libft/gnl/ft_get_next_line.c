/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:58:12 by flomulle          #+#    #+#             */
/*   Updated: 2026/01/04 20:55:44 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"
#include "../libft.h"
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

char	*read_to_store(int fd, char *stored)
{
	char	*buf;
	ssize_t	bytesread;

	buf = (char *)malloc(sizeof(*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytesread = 1;
	while (bytesread > 0 && !strchr_gnl(stored, '\n'))
	{
		bytesread = read(fd, buf, BUFFER_SIZE);
		if (bytesread == -1)
			break ;
		buf[bytesread] = '\0';
		stored = strjoin_gnl(stored, buf);
		if (!stored)
			break ;
	}
	free(buf);
	if (bytesread == -1)
	{
		if (stored)
			free (stored);
		return (NULL);
	}
	return (stored);
}

char	*extract_line(char *stored)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stored[0])
		return (NULL);
	while (stored[i] && stored[i] != '\n')
		i++;
	if (stored[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (stored[i] && stored[i] != '\n')
	{
		line[i] = stored[i];
		i++;
	}
	if (stored[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_check_null(char *s)
{
	if (!s)
		return (NULL);
	if (!*s)
	{
		free(s);
		return (NULL);
	}
	return (s);
}

char	*clean_store(char *stored)
{
	char	*newstoring;
	size_t	i;
	size_t	j;

	i = 0;
	while (stored[i] && stored[i] != '\n')
		i++;
	if (!stored[i])
		return (free(stored), NULL);
	newstoring = malloc(sizeof(char) * (strlen_gnl(stored) - i + 1));
	if (!newstoring)
	{
		free(stored);
		return (NULL);
	}
	i++;
	j = 0;
	while (stored[i])
		newstoring[j++] = stored[i++];
	newstoring[j] = '\0';
	free(stored);
	newstoring = ft_check_null(newstoring);
	return (newstoring);
}

char	*ft_get_next_line(int fd)
{
	static char	*stored[FD_MAX];
	char		*line;

	if (fd < 0 || fd >= FD_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	stored[fd] = read_to_store(fd, stored[fd]);
	if (!stored[fd])
		return (NULL);
	line = extract_line(stored[fd]);
	stored[fd] = clean_store(stored[fd]);
	return (line);
}
