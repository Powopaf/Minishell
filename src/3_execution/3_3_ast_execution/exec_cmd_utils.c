/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 16:24:31 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 01:02:40 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/3_execution/3_3_ast_execution/exec.h"
#include "./src/6_cleaning/clean_shell.h"
#include <stdlib.h>
#include <unistd.h>

void	clean_exit_forked_cmd(t_ast *node, char *cmd, char **args, char **envp)
{
	int	status;

	status = node->shell->status;
	if (cmd)
		free(cmd);
	if (args)
		ft_free_array_strs(&args);
	if (envp)
		ft_free_array_strs(&envp);
	clean_shell(node->shell);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(status);
}
