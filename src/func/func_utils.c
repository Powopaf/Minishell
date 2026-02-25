/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:37:44 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 00:10:47 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../struct.h"
#include "../exec/parser_cmd/parser_cmd.h"
#include <sys/stat.h>
#include <unistd.h>

char	*error_mess(char *program, char *argument)
{
	char	*prog;
	char	*sep;
	char	*arg;

	sep = ft_strdup(": ");
	prog = ft_strdup(program);
	arg = ft_strdup(argument);
	prog = ft_strjoin_free(&prog, &sep, 3);
	arg = ft_strjoin_free(&prog, &arg, 3);
	return (arg);
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
