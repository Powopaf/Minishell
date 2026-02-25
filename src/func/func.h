/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:21:54 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/25 17:24:02 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "../../struct.h"

int		ft_exit(char **args, t_shell *sh);
void	echo(char **args, t_shell *sh);
void	pwd(char **args, t_shell *sh);
void	cd(t_shell *sh, char **args);
void	env(char **args, t_shell *sh);
void	export(char **args, t_shell *sh);
void	unset(char **args, t_shell *sh);

/**
 * @brief compile an error message, ex : program "cd", argument strerror(errno)
 * gives "cd: error: "
 */
char	*error_mess(char *program, char *argument);

char	*get_cwd(t_shell *sh);

#endif
