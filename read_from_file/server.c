/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:28:11 by mzdrodow          #+#    #+#             */
/*   Updated: 2025/11/30 22:04:55 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

t_buffer	g_buffer;
int file_fd;
int shown_start_message = 0;

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
		write(file_fd, &g_buffer.buffer, 1);
		g_buffer.buffer = 0;
		g_buffer.size = 0;
	}

	// if(shown_start_message == 0) {
	// 	ft_printf("started downloading.");
	// 	shown_start_message = 1;
	// }

	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	int					pid;
	struct sigaction	sa;

	g_buffer.buffer = 0;
	g_buffer.size = 0;
	file_fd = open("downloaded", O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, 0644);
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
