/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:28:11 by mzdrodow          #+#    #+#             */
/*   Updated: 2025/11/29 01:44:54 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

t_buffer	g_buffer;

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	int	client_pid;

	(void)context;
	client_pid = info->si_pid;
	g_buffer.size++;
	if (sig == SIGUSR1)
	{
		g_buffer.buffer = (g_buffer.buffer << 1) | 1;
	}
	else if (sig == SIGUSR2)
	{
		g_buffer.buffer = (g_buffer.buffer << 1) | 0;
	}
	if (g_buffer.size == 8)
	{
		write(1, &g_buffer.buffer, 1);
		g_buffer.buffer = 0;
		g_buffer.size = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	g_buffer.buffer = 0;
	g_buffer.size = 0;
	pid = getpid();
	ft_printf("pid: %d\n", pid);
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
	{
		pause();
	}
	return (0);
}
