/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:28:07 by mzdrodow          #+#    #+#             */
/*   Updated: 2025/11/28 20:28:08 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

t_data	*g_data;

void	free_data(void)
{
	ft_printf("\r%d%% | bytes: %d/%d\n", (g_data->bytes_send * 100)
		/ g_data->bytes_size, g_data->bytes_send, g_data->bytes_size);
	free(g_data->message);
	free(g_data);
	exit(0);
}

void	send_bit(void)
{
	if (!g_data->finished)
	{
		if ((g_data->buffer >> (7 - g_data->buffer_size)) & 1)
			kill(g_data->pid, SIGUSR1);
		else
			kill(g_data->pid, SIGUSR2);
		g_data->buffer_size++;
		if (g_data->buffer_size == 8)
		{
			g_data->buffer = *(++g_data->p);
			g_data->buffer_size = 0;
			g_data->bytes_send++;
			if (!g_data->buffer)
				g_data->finished = 1;
		}
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGUSR1)
		send_bit();
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (1);
	g_data = malloc(sizeof(t_data));
	g_data->pid = ft_atoi(argv[1]);
	g_data->message = ft_strdup(argv[2]);
	g_data->p = g_data->message;
	g_data->buffer = *g_data->p;
	g_data->bytes_size = (int)ft_strlen(g_data->message);
	g_data->bytes_send = 0;
	g_data->finished = 0;
	g_data->buffer_size = 0;
	signal(SIGUSR1, signal_handler);
	send_bit();
	while (1)
	{
		ft_printf("\r%d%% | bytes: %d/%d", (g_data->bytes_send * 100)
			/ g_data->bytes_size, g_data->bytes_send, g_data->bytes_size);
		if (g_data->finished)
			free_data();
	}
	return (0);
}
