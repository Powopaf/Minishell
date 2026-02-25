/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:37:44 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/25 17:25:23 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include <sys/stat.h>
#include "../../struct.h"
#include <unistd.h>
#include "../exec/parser_cmd/parser_cmd.h"

char	*error_mess(char *program, char *argument)
{
	char	*prog;
	char	*sep;

	sep = ft_strdup(": ");
	prog = ft_strdup(program);
	prog = ft_strjoin_free(&prog, &sep, 1);
	argument = ft_strjoin_free(&prog, &argument, 3);
	argument = ft_strjoin_free(&argument, &sep, 3);
	return (argument);
}

char	*get_cwd(t_shell *sh)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
		return (cwd);
	cwd = get_env(sh, "PWD");
	if (!cwd)
		return (ft_strdup("/"));
	return (cwd);
}
