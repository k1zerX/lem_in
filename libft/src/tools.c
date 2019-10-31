/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/16 17:06:08 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/04 16:20:51 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_isdigit_p(char c)
{
	return (c >= '0' && c <= '9');
}

int		itoa_len(unsigned long long int nbr, int base)
{
	int		len;

	len = 1;
	while ((nbr /= base) != 0)
		++len;
	return (len);
}

void	ft_bzero_o(void *ptr, size_t size)
{
	while (size--)
		*(unsigned char *)(ptr++) = 0;
}

int		ft_strlen_n(char *str)
{
	char	*start;

	start = str;
	while (*str)
		++str;
	return (str - start);
}

int		mini_atoi(const char *restrict *format, int *len)
{
	int		res;

	res = 0;
	while (ft_isdigit(**format) && (*len)-- + 1)
		res = res * 10 + *(*format)++ - 48;
	--(*format);
	++(*len);
	return (res);
}
