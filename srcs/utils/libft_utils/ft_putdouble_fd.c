#include "push_swap.h"

void	ft_putdouble_fd(double n, int precision, int fd)
{
	long	int_part;
	double	frac_part;

	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	int_part = (long)n;
	ft_putnbr_long_fd(int_part, fd);
	write(fd, ".", 1);
	frac_part = n - (double)int_part;
	while (precision-- > 0)
	{
		frac_part *= 10;
		int_part = (long)frac_part;
		ft_putnbr_long_fd(int_part, fd);
		frac_part -= int_part;
	}
}