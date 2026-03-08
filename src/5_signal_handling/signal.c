/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flomulle <flomulle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 11:11:19 by flomulle          #+#    #+#             */
/*   Updated: 2026/03/08 10:03:31 by flomulle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "signal_handling.h"

void	ignore_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	signal_handler(int sig)
{
	(void)sig;
	g_signal = SIGINT;
	write(1, "\n", 2);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(t_shell *sh)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	struct termios		term;

	if (!sh->tty)
		return ;
	sa_int.sa_handler = signal_handler;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
	restore_terminal_settings(sh);
	ft_memset(&term, 0, sizeof(struct termios));
	if (tcgetattr(STDIN_FILENO, &term) == 0)
	{
		term.c_cc[VQUIT] = _POSIX_VDISABLE;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
}
