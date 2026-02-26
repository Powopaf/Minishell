/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:37:44 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 12:42:57 by flomulle         ###   ########.fr       */
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

void	sort_ascii(char **s)
{
	size_t	i;
	size_t	j;
	char	*tmp;

	if (!s || !*s)
		return ;
	i = 0;
	j = 1;
	while (s[i])
	{
		while (s[j])
		{
			if (ft_strcmp(s[i], s[j]) > 0)
			{
				tmp = s[i];
				s[i] = s[j];
				s[j] = tmp;
			}
			j++;
		}
		i++;
		j = i + 1;
	}
}
