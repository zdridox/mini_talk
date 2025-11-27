#include <signal.h>
#include "../libft/libft.h"

typedef struct s_buffer
{
    char buffer;
    int size;
} t_buffer;

typedef struct s_data
{
    char *message;
    char *p;
    char buffer;
    int buffer_size;
    int pid;
    int bytes_size;
    int bytes_send;
} t_data;