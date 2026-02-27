/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 09:56:55 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/27 10:33:50 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int	append_to_var(t_shell *sh, char *var, char *value)
{
	size_t	i;
	char	*new_entry;

	i = 0;
	while (sh->envp[i])
	{
		if (!varcmp(sh->envp[i], var))
		{
			new_entry = ft_strjoin(sh->envp[i], value);
			if (!new_entry)
				return (error(sh, "export", strerror(errno), -FAIL), 0);
			free(sh->envp[i]);
			sh->envp[i] = new_entry;
			return (1);
		}
		i++;
	}
	if (!new_entry_to_env(sh, var, value))
		return (0);
	return (1);
}

int	append_env_var(t_shell *sh, char *arg)
{
	char	*equal;
	char	*var;
	char	*value;
	int		status;

	equal = ft_strchr(arg, '=');
	var = ft_strndup(arg, equal - arg - 1);
	value = ft_strdup(equal + 1);
	if (!is_valid_var_name(sh, var))
		status = 1;
	else
		status = !append_to_var(sh, var, value);
	return (free(var), free(value), status);
}
