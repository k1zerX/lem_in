/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:23:48 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/08 18:18:24 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	apa_fill_f(unsigned char *str, unsigned long m, int len, int k)
{
	int		i;
	int		l;

	i = -1;
	while (++i < len + k)
		str[i] = 0;
	l = 1;
	i = -1;
	while (++i < len)
	{
		if (m & 1)
			str[len + k - 1 - i] += 1;
		++l;
		m >>= 1;
		apa_mul(5, str, len + k, &l);
	}
	i = -1;
	while (++i < (k >> 1))
		apa_mul(25, str, len + k, &l);
	if (k & 1)
		apa_mul(5, str, len + k, &l);
}

void	apa_else(int *k, t_float f, t_float_ip *parts)
{
	*k += 1;
	parts->i = f.parse.m >> (M_LEN - *k);
	parts->i_len = *k;
	parts->f_len = count_len(f.parse.m);
	parts->f = f.parse.m >> (M_LEN - parts->f_len);
	parts->f_len -= *k;
	parts->f &= ~(~((unsigned long)0) << parts->f_len);
	*k = -1;
}

void	apa_if(int *k, t_float f, t_float_ip *parts)
{
	if (*k > M_LEN)
	{
		*k += 1;
		parts->i = f.parse.m;
		parts->i_len = M_LEN;
		parts->f = 0;
		parts->f_len = 0;
		*k -= M_LEN;
	}
	else if (*k < 0)
	{
		parts->i = 0;
		parts->i_len = 0;
		parts->f_len = count_len(f.parse.m);
		parts->f = f.parse.m >> (M_LEN - parts->f_len);
	}
	else
		apa_else(k, f, parts);
}

char	*apa_get(t_float f, t_float_ip parts, int il, int k)
{
	unsigned char	*str;

	if (!(str = malloc((3 + il + parts.f_len + ((k > 0) ? (0) : (-++k))) \
		* sizeof(unsigned char))))
		exit(1);
	str[0] = (f.parse.s) ? '-' : '+';
	apa_fill_i(str + 1, parts.i, il, k);
	str[1 + il] = '.';
	apa_fill_f(str + 1 + il + 1, parts.f, parts.f_len, -k);
	str[1 + il + 1 + parts.f_len + ((k > 0) ? (0) : (-k))] = 0;
	return (ft_to_char(str, 3 + il + parts.f_len + ((k > 0) ? (0) : (-k))));
}

char	*apa_float(long double n)
{
	t_float		f;
	t_float_ip	parts;
	int			k;
	int			il;

	f.val = n;
	if (!(~f.parse.e))
	{
		if (f.parse.m)
			return ("NaN");
		else if (f.parse.s)
			return ("-inf");
		else
			return ("inf");
	}
	k = f.parse.e - ~(~((unsigned)0) << (E_LEN - 1));
	apa_if(&k, f, &parts);
	il = (int)((((parts.i_len) ? (parts.i_len) : (1)) + ((k < 0) ? (0) : (k))) \
		* 0.30103) + 2;
	return (apa_get(f, parts, il, k));
}
