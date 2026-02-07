/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 23:07:04 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/05 23:07:06 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_SHELL_H
# define INIT_SHELL_H

# define PROMPT_HD "> "

#include "../../struct.h"

void	initialize_shell(t_shell *shell, char **envp, char **argv);

#endif
