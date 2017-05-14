#include <stdio.h>

typedef struct s_test
{
	unsigned char	i;
	char			pad1[7];
	char			*a;
	char			b;
	char			pad2[3];
	int				c;
	long			d;
}				t_test;

void printnum(int n, int b) // fonction de convertion d'un nombre en base b
{
	int r;

	if (n < b)
		printf("%d", n);
	else
	{
		r = n % b;
		printnum(n/b, b);
		printf("%d", r);;
	}
}

int	main()
{
	t_test	test; // Declaration de la structure

	test.i = 0; // Declaration et initialisation de la variable i a 0
	do			// Boucle jusqu'a la limite de i et affichage de i
	{
		printf("\033[31mSizeof(t_test) = %zu\033[39m,\
	\033[35mValue = %d\033[39m,\
	\033[36mBinary = ",\
	sizeof(t_test), test.i);
		printnum(test.i, 2);
		printf("\033[0m\n");
		test.i++;
	}
	while (test.i > 0);
}
