/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_x.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:48:58 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/08 18:23:39 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	x_counter(unsigned long long int n, char *nbr, int len, t_format f)
{
	char	*str;

	if (n == 0)
	{
		if (f.precision == 0)
			len = f.precision;
		f.sharp = 0;
	}
	f.precision -= len;
	if (f.precision < 0)
		f.precision = 0;
	f.precision += f.sharp << 1;
	f.width -= f.precision + len + f.plus;
	if (f.width < 0)
		f.width = 0;
	str = malloc((f.width + f.precision + len + f.plus) * sizeof(*str));
	if (!str)
		exit(1);
	ft_intfill(str, nbr, f, len);
	if (f.sharp)
		str[((f.minus || (!f.minus && f.zero)) ? (0) : (f.width)) + 1] = 'x';
	write(1, str, f.width + f.precision + len + f.plus);
	free(str);
	free(nbr);
	return (f.width + f.precision + len + f.plus);
}

int			f_x(va_list ap, t_format f)
{
	unsigned long long int	n;
	char					*nbr;
	int						len;

	n = va_arg(ap, unsigned long long int);
	if (f.type == FT_HH)
		n = (unsigned char)n;
	else if (f.type == FT_H)
		n = (unsigned short int)n;
	else if (f.type == FT_L)
		n = (unsigned long int)n;
	else if (f.type == FT_LL)
		n = (unsigned long long int)n;
	else
		n = (unsigned int)n;
	if (f.minus)
		f.zero = 0;
	if (f.zero)
		f.space = 0;
	f.zero = (f.precision != -1) ? (0) : (f.zero);
	f.plus = 0;
	nbr = ft_ultra_itoa(n, 16, 0, "0123456789abcdef");
	len = ft_strlen(nbr) - 1;
	return (x_counter(n, nbr, len, f));
}
