/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:32:12 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/06 13:32:15 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_CMD_H
# define PARSER_CMD_H

# include "../../../struct.h"

char	*parse_cmd(t_shell *sh, t_ast *node);
char	*get_env(t_shell *sh, char *var_name);

#endif
