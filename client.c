#include "so_long.h"

t_data *data;

void free_data()
{
    free(data->message);
    free(data);
    exit(0);
}

void send_bit()
{
    if ((data->buffer >> (7 - data->buffer_size)) & 1)
        kill(data->pid, SIGUSR1);
    else
        kill(data->pid, SIGUSR2);
    data->buffer_size++;
    if (data->buffer_size == 8)
    {
        data->buffer = *(++data->p);
        data->buffer_size = 0;
        data->bytes_send++;
        if (!data->buffer)
            free_data();
    }
}

void signal_handler(int sig)
{
    if (sig == SIGUSR1)
    {
        // ft_printf("\rbytes sent: %d/%d", data->bytes_send, data->bytes_size);
        send_bit();
    }
}

int main(int argc, char **argv)
{
    if (argc != 3)
        return (1);
    data = malloc(sizeof(t_data));
    data->pid = ft_atoi(argv[1]);
    data->message = ft_strdup(argv[2]);
    data->p = data->message;
    data->buffer = *data->p;
    data->bytes_size = (int)ft_strlen(data->message);
    data->bytes_send = 0;
    signal(SIGUSR1, signal_handler);
    send_bit();
    while (1)
    {
        ft_printf("\rbytes sent: %d/%d", data->bytes_send, data->bytes_size);
    }
    return (0);
}
