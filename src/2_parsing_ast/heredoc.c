/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 09:36:17 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/07 13:24:59 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/2_parsing_ast/heredoc.h"
#include "./src/3_execution/3_1_expansion/expand.h"
#include "./src/5_signal_handling/signal_handling.h"
#include "./src/7_error_handling/err.h"
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	expand_hd_line(t_shell *sh, t_redir *redir, char **line)
{
	char	*expand;

	if (!redir->quoted)
	{
		expand = expand_str(sh, *line);
		if (expand)
		{
			free(*line);
			*line = expand;
		}
	}
}

static int	heredoc_null(t_shell *sh, char *line, int *block_null)
{
	size_t	len;

	len = ft_strlen(line);
	if (line && len > 0 && line[len - 1] == '\n')
	{
		(*block_null) = 0;
		return (0);
	}
	if (line && len > 0 && line[len - 1] != '\n')
	{
		(*block_null) = 1;
		return (0);
	}
	if (!line && (*block_null))
		return (2);
	if (!line && !(*block_null))
	{
		if (g_signal != SIGINT)
			warning_hd(sh);
		return (1);
	}
	return (0);
}

static int	write_heredoc(t_shell *sh, t_redir *redir, int fd)
{
	char	*line;
	int		block_null;

	block_null = 0;
	while (1)
	{
		if (!block_null)
			ft_putstr_fd(PROMPT_HD, 1);
		line = ft_get_next_line(sh->stdin_fd);
		if (heredoc_null(sh, line, &block_null) == 1)
			break ;
		if (heredoc_null(sh, line, &block_null) == 2)
			continue ;
		if (ft_strlen(line) > 0 && !ft_strncmp(line, redir->eofkw,
				ft_strlen(redir->eofkw))
			&& line[ft_strlen(redir->eofkw)] == '\n')
		{
			free(line);
			break ;
		}
		expand_hd_line(sh, redir, &line);
		write(fd, line, ft_strlen(line));
		free(line);
	}
	return (close(fd), 1);
}

static int	heredoc(t_shell *sh, t_redir *redir)
{
	int		fd;
	char	*hdfile;
	char	*id;

	id = ft_ptoa(redir->eofkw);
	if (!id)
		return (error(sh, "malloc", strerror(errno), -FAIL), 0);
	hdfile = ft_strjoin(HEREDOC, id);
	free(id);
	if (!hdfile)
		return (error(sh, "malloc", strerror(errno), -FAIL), 0);
	fd = open(hdfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd < 0)
		return (free(hdfile), error(sh, "here_doc", strerror(errno), -FAIL), 0);
	redir->fd_in = open(hdfile, O_RDONLY);
	if (redir->fd_in < 0)
		return (free(hdfile), error(sh, "here_doc", strerror(errno), -FAIL), 0);
	unlink(hdfile);
	free(hdfile);
	setup_heredoc_signals();
	write_heredoc(sh, redir, fd);
	setup_signals(sh);
	return (1);
}

void	handle_heredocs(t_shell *sh, t_ast *current_node)
{
	t_redir	*redir;

	if (!current_node)
		return ;
	redir = current_node->redir;
	while (redir)
	{
		if (redir->kw == REDIR_HD)
		{
			ft_close_fd(&redir->fd_in);
			heredoc(sh, redir);
			if (g_signal == SIGINT)
				break ;
		}
		redir = redir->next;
	}
}
