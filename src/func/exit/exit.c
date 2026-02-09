/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 12:23:56 by pifourni          #+#    #+#             */
/*   Updated: 2026/02/09 13:32:10 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "../../../libft/libft.h"

void	ft_exit(char **args, t_shell *sh)
{
	int	exit_code;

	exit_code = sh->status;
	if (args && *args)
	{
		exit_code = ft_atoi(*args);
	}
	sh->exit = exit_code;
}
