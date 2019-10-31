/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 18:17:09 by etuffleb          #+#    #+#             */
/*   Updated: 2019/09/08 18:22:41 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_to_char(unsigned char *str, size_t len)
{
	char	*res;
	char	*buf;

	if (!(res = malloc(len * sizeof(char))))
		exit(1);
	buf = res;
	while (len--)
	{
		*buf = *str;
		if (*buf >= 0 && *buf <= 9)
			*buf += 48;
		++buf;
		++str;
	}
	return (res);
}

void	apa_fill_i(unsigned char *str, unsigned long m, int len, int k)
{
	int		i;
	int		l;

	i = -1;
	while (++i < len)
		str[i] = 0;
	l = 1;
	i = M_LEN;
	while (--i >= 0)
	{
		apa_mul(2, str, len, &l);
		if (m & ((unsigned long)1 << i))
			str[len - 1] += 1;
	}
	i = -1;
	while (++i < (k >> 2))
		apa_mul(16, str, len, &l);
	i = -1;
	while (++i < (k & 3))
		apa_mul(2, str, len, &l);
}
