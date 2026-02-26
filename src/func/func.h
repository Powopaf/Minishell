/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:21:54 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/26 21:53:40 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_H
# define FUNC_H

# include "../../struct.h"

void	ft_exit(char **args, t_shell *sh);
int		echo(char **args, t_shell *sh);
int		pwd(char **args, t_shell *sh);
int		cd(t_shell *sh, char **args);
int		env(char **args, t_shell *sh);
int		export(char **args, t_shell *sh);
int		unset(char **args, t_shell *sh);

/**
 * @brief compile an error message, ex : program "cd", argument strerror(errno)
 * gives "cd: error: "
 */
char	*error_mess(char *program, char *argument);

char	*get_cwd(t_shell *sh);

void	sort_ascii(char **s);

int		varcmp(char *s1, char *s2);

char	*create_entry(t_shell *sh, char *var, char *value);

int		is_valid_var_name(t_shell *sh, char *s);

int		printout_env_line(t_shell *sh, char *s);

char	*export_err_var(char *s);

#endif
