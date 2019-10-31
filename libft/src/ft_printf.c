/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 21:20:44 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/08 19:39:50 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_conv			g_conv[] =
{
	{'c', &f_c},
	{'s', &f_s},
	{'p', &f_p},
	{'d', &f_d},
	{'i', &f_i},
	{'o', &f_o},
	{'u', &f_u},
	{'x', &f_x},
	{'X', &f_big_x},
	{'f', &f_f},
	{'%', &f_percent},
	{0, NULL}
};

int		ft_while(va_list ap, const char *restrict *str, int *len, char **start)
{
	int		i;
	int		res;

	res = 0;
	*len = -1;
	while ((*str)[++*len])
	{
		i = -1;
		while (g_conv[++i].conv)
			if (g_conv[i].conv == (*str)[*len])
			{
				res += (*g_conv[i].f)(ap, format(*str, *len));
				break ;
			}
		if (g_conv[i].conv)
			break ;
	}
	if (!(*str)[*len])
		*start = NULL;
	else if (1 && (*str += *len + 1))
		*start = (char *)*str;
	*len = 0;
	return (res);
}

int		ft_printf(const char *restrict str, ...)
{
	va_list		ap;
	int			len;
	int			res;
	char		*start;

	va_start(ap, str);
	len = 0;
	start = (char *)str;
	res = 0;
	while (*str)
		if (*str++ == '%')
		{
			if (!*str)
				break ;
			if (len > 0)
				write(1, start, len);
			res += len;
			res += ft_while(ap, &str, &len, &start);
		}
		else
			++len;
	write(1, start, len);
	res += len;
	va_end(ap);
	return (res);
}
