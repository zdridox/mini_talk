#include <unistd.h>
#include <signal.h>
#include "libft.h"

char *char_to_bin(char c)
{
    int i;
    char *out;

    out = malloc(9);
    if (!out)
        return (NULL);
    i = 7;
    while (i >= 0)
    {
        if ((c >> i) & 1)
            out[7 - i] = '1';
        else
            out[7 - i] = '0';
        i--;
    }
    return (out[8] = '\0', out);
}

char *str_to_bin(char *str)
{
    char *res;
    char *bin_char;
    int buff_size;

    buff_size = (ft_strlen(str) * 8) + 1;
    res = malloc(buff_size);
    if (!res)
        return (NULL);
    res[0] = '\0';
    while (*str)
    {
        bin_char = char_to_bin(*str);
        ft_strlcat(res, bin_char, buff_size);
        free(bin_char);
        str++;
    }
    return (res);
}

int main(int argc, char **argv)
{
    int pid;
    char *binary_to_send;
    char *p;

    if (argc != 3)
        return (1);
    pid = ft_atoi(argv[1]);
    binary_to_send = str_to_bin(argv[2]);
    p = binary_to_send;
    while (*p)
    {
        if (*p == '1')
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        usleep(100);
        p++;
    }
    free(binary_to_send);
    return (0);
}