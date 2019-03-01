/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 20:05:39 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/04 22:02:32 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	res;
	long	buf;
	char	sign;

	buf = 0;
	res = 0;
	sign = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = str[i++] == '-';
	while (ft_isdigit(str[i]))
	{
		buf = res;
		res = res * 10 + (str[i++] - '0');
		if (buf > 0 && buf > res)
			return (sign ? 0 : -1);
	}
	return ((int)res);
}
