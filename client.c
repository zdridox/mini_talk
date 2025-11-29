/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzdrodow <mzdrodow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 20:28:07 by mzdrodow          #+#    #+#             */
/*   Updated: 2025/11/29 02:22:23 by mzdrodow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_talk.h"

t_data	*g_data;

char	*progress_bar(void)
{
	char	*bar;
	int		progress;
	int		i;
	int		j;

	i = 0;
	j = 0;
	bar = malloc(13);
	progress = ((g_data->bytes_send * 100) / g_data->bytes_size) / 10;
	bar[j++] = '[';
	while (i++ < progress)
		bar[j++] = '#';
	i = 0;
	while (i++ < 10 - progress)
		bar[j++] = '-';
	bar[11] = ']';
	bar[12] = '\0';
	return (bar);
}

void	free_data(void)
{
	char	*bar;

	bar = progress_bar();
	ft_printf("\r%d%% %s | bytes: %d/%d", (g_data->bytes_send * 100)
		/ g_data->bytes_size, bar, g_data->bytes_send, g_data->bytes_size);
	free(bar);
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
	char	*bar;

	if (argc != 3 || !*argv[2])
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
		bar = progress_bar();
		ft_printf("\r%d%% %s | bytes: %d/%d", (g_data->bytes_send * 100)
			/ g_data->bytes_size, bar, g_data->bytes_send, g_data->bytes_size);
		free(bar);
		if (g_data->finished)
			free_data();
	}
	return (0);
}
