/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:36:17 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/12 18:15:31 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "../signal/signal_handling.h"
#include "heredoc.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int	write_heredoc(t_shell *sh, t_redir *redir, int fd)
{
	char	*line;
	size_t	len;

	setup_heredoc_signals();
	while (1)
	{
		ft_putstr_fd(PROMPT_HD, 1);
		line = ft_get_next_line(sh->stdin_fd);
		if (!line)
		{
			write(1, "\n", 1);
			warning_hd(sh);
			break ;
		}
		len = ft_strlen(line);
		if (len > 0 && !ft_strncmp(line, redir->eofkw, ft_strlen(redir->eofkw))
			&& line[ft_strlen(redir->eofkw)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (setup_signals(sh), close(fd), EXIT_SUCCESS);
}

static int	heredoc(t_shell *sh, t_redir *redir)
{
	int		fd;
	char	*hdfile;
	char	*id;

	id = ft_ptoa(redir->eofkw);
	if (!id)
		return (error(sh, "malloc", MALLOC_ERR, -EXIT_FAILURE), EXIT_FAILURE);
	hdfile = ft_strjoin(HEREDOC, id);
	free(id);
	if (!hdfile)
		return (error(sh, "malloc", MALLOC_ERR, -EXIT_FAILURE), EXIT_FAILURE);
	fd = open(hdfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
		return (free(hdfile), error(sh, "here_doc", strerror(errno),
				EXIT_FAILURE), -EXIT_FAILURE);
	redir->fd_in = open(hdfile, O_RDONLY);
	if (redir->fd_in < 0)
		return (free(hdfile), error(sh, "here_doc", strerror(errno),
				EXIT_FAILURE), -EXIT_FAILURE);
	unlink(hdfile);
	free(hdfile);
	if (write_heredoc(sh, redir, fd) == EXIT_FAILURE)
		return (FAIL);
	setup_signals(sh);
	return (EXIT_SUCCESS);
}

static void	collect_heredocs(t_shell *sh, t_redir *redir)
{
	while (redir)
	{
		if (redir->kw == REDIR_HD)
		{
			ft_close_fd(&redir->fd_in);
			heredoc(sh, redir);
		}
		redir = redir->next;
	}
}

void	handle_heredocs(t_shell *sh, t_ast *current_node)
{
	if (!current_node)
		return ;
	if (current_node->astkw == AST_CMD && current_node->args)
	{
		collect_heredocs(sh, current_node->redir);
	}
	handle_heredocs(sh, current_node->left);
	handle_heredocs(sh, current_node->right);
}
