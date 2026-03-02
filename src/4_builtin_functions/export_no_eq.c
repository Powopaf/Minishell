/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_eq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 14:10:26 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/02 14:32:37 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./src/4_builtin_functions/func.h"
#include "./src/7_error_handling/err.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	printout_env_line_no_eq(t_shell *sh, char *s)
{
	char	*line;
	char	*tmp;
	char	*var_eq;

	var_eq = ft_strdup(s);
	tmp = ft_strjoin("export ", var_eq);
	if (var_eq)
		free(var_eq);
	if (!tmp)
		return (error(sh, "export", strerror(errno), -FAIL), 0);
	line = ft_strjoin(tmp, "\n");
	free(tmp);
	if (!line)
		return (error(sh, "export", strerror(errno), -FAIL), 0);
	if (write(STDOUT_FILENO, line, ft_strlen(line)) < 0)
		return (error(sh, "export", strerror(errno), -FAIL), 0);
	free(line);
	return (1);
}

static int	new_entry_no_eq_to_env(t_shell *sh, char *var)
{
	size_t	i;
	char	**new_env;

	new_env = malloc((ft_strslen(sh->envp) + 2) * sizeof(char *));
	if (!new_env)
		return (error(sh, "export", strerror(errno), -FAIL), 0);
	i = 0;
	while (i < ft_strslen(sh->envp))
	{
		new_env[i] = sh->envp[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
		error(sh, "export", strerror(errno), -FAIL);
	new_env[i + 1] = NULL;
	free(sh->envp);
	sh->envp = new_env;
	return (1);
}

int	add_no_eq_to_env(t_shell *sh, char *var)
{
	size_t	i;

	i = 0;
	while (sh->envp[i])
	{
		if (!varcmp(sh->envp[i], var))
			return (1);
		i++;
	}
	if (!new_entry_no_eq_to_env(sh, var))
		return (0);
	return (1);
}
