/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:36:17 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/06 15:50:10 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "../error/err.h"
#include "../../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

static int	write_heredoc(t_shell *sh, t_redir *redir, int fd)
{
	char	*line;
	size_t	len;

	while (1)
	{
		ft_putstr_fd(PROMPT_HD, 1);
		line = ft_get_next_line(sh->stdin_fd);
		if (!line)
		{
			error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE);
			return (EXIT_FAILURE);
		}
		len = ft_strlen(line);
		if (len > 0 && !ft_strncmp(line, redir->eofkw, ft_strlen(redir->eofkw))
			&& line[ft_strlen(redir->eofkw)] == '\n')
		{
			free(line);
			return (EXIT_SUCCESS);
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (EXIT_SUCCESS);
}

int	heredoc(t_shell *sh, t_redir *redir)
{
	int		fd;
	char	*hdfile;
	char	*id;

	//signals ?????

	id = ft_ptoa(redir->eofkw);
	if (!id)
		return (error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE), EXIT_FAILURE);
	hdfile = ft_strjoin(HEREDOC, id);
	free(id);
	if (!hdfile)
		return (error(sh, "malloc", MALLOC_ERR, EXIT_FAILURE), EXIT_FAILURE);
	fd = open(hdfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
		return (free(hdfile),
			error(sh, "here_doc", strerror(errno), EXIT_FAILURE), EXIT_FAILURE);
	redir->fd_in = open(hdfile, O_RDONLY);
	if (redir->fd_in < 0)
		return (free(hdfile),
			error(sh, "here_doc", strerror(errno), EXIT_FAILURE), EXIT_FAILURE);
	unlink(hdfile);
	free(hdfile);
	if (write_heredoc(sh, redir, fd) == EXIT_FAILURE)
		return (FAIL);
	return (EXIT_SUCCESS);
}
