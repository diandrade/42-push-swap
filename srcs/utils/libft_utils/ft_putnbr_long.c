#include "push_swap.h"

void	ft_putnbr_long(long n)
{
	char digit;

	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
		ft_putnbr_long(n / 10);
	digit = (n % 10) + '0';
	write(1, &digit, 1);
}