/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_f.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:54:56 by etuffleb          #+#    #+#             */
/*   Updated: 2019/09/08 18:01:02 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			float_strlen(char *nbr)
{
	int		i;

	i = 0;
	while (nbr[i] != '.')
		++i;
	return (i);
}

void		ft_floatround(char *nbr, int precision)
{
	int		i;

	if ((i = ft_find_dot(nbr)) < 0)
		return ;
	precision += i;
	if (nbr[precision + 1] >= '5')
	{
		while (precision)
		{
			if (nbr[precision] == '.')
				--precision;
			if (++nbr[precision] > '9')
				nbr[precision] = '0';
			else
				return ;
			--precision;
		}
	}
}

void		ft_floatfill(char *str, char *nbr, t_format f, int len)
{
	int		i;

	i = -1;
	if (!f.zero && !f.minus)
		while (++i < f.width)
			*str++ = ' ';
	if (f.plus)
		*str++ = *nbr;
	i = -1;
	if (f.zero)
		while (++i < f.width)
			*str++ = '0';
	while (len--)
		*str++ = *++nbr;
	i = -1;
	while (*++nbr && ++i < f.precision)
		*str++ = *nbr;
	if (f.precision == 0 && f.sharp)
		*str++ = *nbr;
	while (++i < f.precision)
		*str++ = '0';
	i = -1;
	if (!f.zero && f.minus)
		while (++i < f.width)
			*str++ = ' ';
}

static int	f_counter(char *nbr, t_format f)
{
	char	*str;
	int		len;

	len = float_strlen(nbr) - 1;
	f.width -= len + f.plus + f.precision + (f.precision == 0 && f.sharp);
	if (f.width < 0)
		f.width = 0;
	str = malloc((f.plus + f.width + len + f.precision + \
		(f.precision == 0 && f.sharp)) * sizeof(*str));
	if (!str)
		exit(1);
	ft_floatfill(str, nbr, f, len);
	write(1, str, f.plus + f.width + len + f.precision + \
		(f.precision == 0 && f.sharp));
	free(str);
	free(nbr);
	return (f.plus + f.width + len + f.precision + \
		(f.precision == 0 && f.sharp));
}

int			f_f(va_list ap, t_format f)
{
	long double		n;
	char			*nbr;

	if (f.l_big)
		n = va_arg(ap, long double);
	else
		n = va_arg(ap, double);
	nbr = apa_float(n);
	if (f.precision == -1)
		f.precision = 6;
	ft_floatround(nbr, f.precision);
	ft_treatment(nbr);
	if (f.minus)
		f.zero = 0;
	if (f.precision)
		++f.precision;
	if (n < 0)
		f.plus = 1;
	if (!f.plus && f.space && (f.plus = 1))
		*nbr = ' ';
	if (f.zero)
		f.space = 0;
	return (f_counter(nbr, f));
}
