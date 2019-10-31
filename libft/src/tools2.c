/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 16:15:28 by etuffleb          #+#    #+#             */
/*   Updated: 2019/09/07 16:21:50 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ultra_itoa(long long int n, int base, char is_signed, \
		const char *digits)
{
	char					*str;
	int						len;
	char					sign;
	unsigned long long int	nbr;

	if (base < 2)
		return (NULL);
	if (is_signed && (sign = n < 0))
		nbr = ~(unsigned long long int)n + 1;
	else
		nbr = n;
	len = itoa_len(nbr, base) + 1;
	if ((str = malloc((len + 1) * sizeof(*str))))
	{
		str[len] = 0;
		str[0] = (sign) ? ('-') : ('+');
		str[--len] = digits[nbr % base];
		while ((nbr /= base) > 0)
			str[--len] = digits[nbr % base];
	}
	return (str);
}

void		ft_intfill(char *str, char *nbr, t_format f, int len)
{
	int		i;

	i = -1;
	if (!f.minus && !f.zero)
		while (++i < f.width)
			*str++ = ' ';
	if (f.plus)
		*str++ = *nbr;
	i = -1;
	if (!f.minus && f.zero)
		while (++i < f.width)
			*str++ = '0';
	i = -1;
	while (++i < f.precision)
		*str++ = '0';
	i = -1;
	while (++i < len)
		*str++ = *(++nbr);
	i = -1;
	if (f.minus)
		while (++i < f.width)
			*str++ = ' ';
}

void		ft_strfill(char *str, char *s, t_format f, int len)
{
	int		i;
	char	c;

	c = (f.zero) ? ('0') : (' ');
	i = -1;
	if (!f.minus)
		while (++i < f.width)
			*str++ = c;
	i = -1;
	while (++i < len)
		*str++ = *(s++);
	i = -1;
	if (f.minus)
		while (++i < f.width)
			*str++ = c;
}

void		reformat(t_format *f, const char *restrict format)
{
	if (*format == '-')
		f->minus = 1;
	else if (*format == '+')
		f->plus = 1;
	else if (*format == ' ')
		f->space = 1;
	else if (*format == 'L')
		f->l_big = 1;
	else if (*format == 'l')
		++(f->type);
	else if (*format == 'h')
		--(f->type);
}

t_format	format(const char *restrict format, int len)
{
	t_format	f;

	ft_bzero(&f, sizeof(f));
	f.precision = -1;
	while (--len >= 0)
	{
		if (*format == '#')
			f.sharp = 1;
		else if (*format == '.')
		{
			++format;
			--len;
			f.precision = mini_atoi(&format, &len);
		}
		else if (*format == '0')
			f.zero = 1;
		else if (ft_isdigit(*format))
			f.width = mini_atoi(&format, &len);
		else
			reformat(&f, format);
		++format;
	}
	return (f);
}
