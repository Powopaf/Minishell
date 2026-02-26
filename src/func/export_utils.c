/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:43:23 by flomulle          #+#    #+#             */
/*   Updated: 2026/02/26 18:24:07 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../error/err.h"
#include "func.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	varcmp(char *s1, char *s2)
{
	while (*s1 && *s1 != '=' && *s2 && *s2 != '=' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if ((*s1 == '=' || *s1 == '\0') && (*s2 == '=' || *s2 == '\0'))
		return (0);
	return (*s1 - *s2);
}

char	*create_entry(t_shell *sh, char *var, char *value)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(var, "=\"");
	if (!tmp)
		return (error(sh, "export", strerror(errno), -FAIL), NULL);
	entry = ft_strjoin(tmp, value);
	entry = ft_strjoin_char(entry, '\"', 1, 1);
	free(tmp);
	return (entry);
}

char	*export_err_var(char *s)
{
	char	*tmp;
	char	*err;

	tmp = ft_strjoin("`", s);
	err = ft_strjoin(tmp, "\'");
	free(tmp);
	return (err);
}

int	is_valid_var_name(t_shell *sh, char *s)
{
	size_t	i;

	if (!s)
		return (0);
	if (!ft_isalpha(*s) && *s != '_')
	{
		error(sh, error_mess("export", export_err_var(s)),
			"not a valid identifier", -FAIL);
		return (0);
	}
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!ft_isalnum(s[i]) && s[i] != '_')
		{
			error(sh, error_mess("export", export_err_var(s)),
				"not a valid identifier", -FAIL);
			return (0);
		}
		i++;
	}
	return (1);
}

int	printout_env_line(t_shell *sh, char *s)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin("export ", s);
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
