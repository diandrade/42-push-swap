#include "push_swap.h"

void	ft_putnbr_long_fd(long n, int fd)
{
	unsigned long nb;
	char c;

	if (n < 0)
	{
		write(fd, "-", 1);
		nb = (unsigned long)(-n);
	}
	else
		nb = (unsigned long)n;
	if (nb >= 10)
		ft_putnbr_long_fd((long)(nb / 10), fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}