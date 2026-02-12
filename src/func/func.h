/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:21:54 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/12 19:43:53 by pifourni         ###   ########.fr       */
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

#endif
