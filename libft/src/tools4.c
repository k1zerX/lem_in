/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 19:44:42 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/08 18:07:12 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_len(unsigned long a)
{
	int		i;

	i = -1;
	while (++i < M_LEN)
		if (a & (1 << i))
			break ;
	return (M_LEN - i);
}

void	apa_mul(int power, unsigned char *str, int len, int *l)
{
	int		i;
	int		buf;

	buf = 0;
	i = len;
	while (--i >= 0 && len - i <= *l)
	{
		str[i] *= power;
		str[i] += buf;
		buf = str[i] / 10;
		str[i] -= buf * 10;
		if ((len - i == *l) && buf)
			++*l;
	}
}

char	*ft_strcpy(char *dst, const char *src)
{
	char	*tmp;

	tmp = dst;
	while (*src)
		*dst++ = *src++;
	*dst = 0;
	return (tmp);
}

int		ft_find_dot(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '.')
			return (tmp - str);
		++tmp;
	}
	return (-1);
}

void	ft_treatment(char *nbr)
{
	int		i;
	int		j;

	i = 0;
	while (nbr[i] && nbr[i] != '0')
		++i;
	j = i;
	while (nbr[j] == '0' && (nbr[j + 1] != '.' && nbr[j + 1]))
		++j;
	ft_strcpy(nbr + i, nbr + j);
}
