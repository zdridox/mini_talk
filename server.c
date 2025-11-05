#include <unistd.h>
#include <signal.h>
#include "libft.h"

char bin[9];

int binary_to_ascii(char *binary)
{
    int i;
    int value;

    i = 0;
    value = 0;
    while (i < 8)
    {
        value = value * 2 + (binary[i] - '0');
        i++;
    }
    return (value);
}

void print_ascii()
{
    char c;

    c = (char)binary_to_ascii(bin);
    write(1, &c, 1);
    bin[0] = '\0';
}

void signal_handler(int sig)
{
    int size;
    char c;

    if (ft_strlen(bin) == 8)
        print_ascii();
    size = ft_strlen(bin);
    if (sig == SIGUSR1)
        c = '1';
    else
        c = '0';
    bin[size] = c;
    bin[size + 1] = '\0';
}

int main()
{
    int pid;

    pid = getpid();
    ft_printf("pid: %d\n", pid);
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);
    while (1)
    {
    }
    return (0);
}