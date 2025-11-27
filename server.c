#include "so_long.h"

t_buffer *buffer;

void signal_handler(int sig, siginfo_t *info, void *context)
{
    int client_pid;

    (void)context;
    client_pid = info->si_pid;
    buffer->size++;
    if (sig == SIGUSR1)
    {
        buffer->buffer = (buffer->buffer << 1) | 1;
    }
    else if (sig == SIGUSR2)
    {
        buffer->buffer = (buffer->buffer << 1) | 0;
    }
    if (buffer->size == 8)
    {
        write(1, &buffer->buffer, 1);
        buffer->buffer = 0;
        buffer->size = 0;
    }
    kill(client_pid, SIGUSR1);
}

int main()
{
    int pid;
    struct sigaction sa;

    buffer = malloc(sizeof(t_buffer));
    buffer->buffer = 0;
    buffer->size = 0;
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
