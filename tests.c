#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	binary_to_ascii(char *binary)
{
	int	i;
	int	value;

	i = 0;
	value = 0;
	while (i < 8)
	{
		value = value * 2 + (binary[i] - '0');
		i++;
	}
	return (value);
}

char	*binary_to_str(char *bin) // USELESS
{
	char bin_char[8];
	char *res;
	int size;
	int i;
	int k;

	k = 0;
	i = 0;
	size = strlen(bin) / 8; // ZAKAZANA FUNKCJA!
	res = malloc(size + 1);
	if (!res)
		return (NULL);
	while (*bin)
	{
		bin_char[i++] = *bin++;
		if (i == 8)
		{
			res[k++] = binary_to_ascii(bin_char);
			i = 0;
		}
	}
	return (res[k] = '\0', res);
}

int	main(void)
{
	char	bin[] = "0110110101100001011100100110010101101011";
    char *str = binary_to_str(bin);

	printf("string from binary %s is %s", bin, str);
    free(str);
	return (0);


    // JAK DOSTANIESZ BIT Z SYGNALU DODAWAJ DO BIN CHAR JAK MA 8 TO NA ASCII I WRITUJ TO I TYLE KLASA
}
