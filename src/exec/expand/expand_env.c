/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 15:23:05 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/17 11:39:19 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

char	*collect_env_var(t_shell *sh, char *var_name)
{
	char	*var;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen(var_name);
	while (sh->envp && sh->envp[i])
	{
		if (!ft_strncmp(var_name, sh->envp[i], len) && sh->envp[i][len] == '=')
		{
			var = ft_substr(sh->envp[i], len + 1,
					ft_strlen(sh->envp[i]) - (len + 1));
			if (!var)
				error(sh, "malloc", MALLOC_ERR, -FAIL);
			return (var);
		}
		i++;
	}
	var = ft_strdup("");
	if (!var)
		error(sh, "malloc", MALLOC_ERR, -FAIL);
	return (var);
}
