/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_u.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 20:48:35 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/07 17:43:26 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		u_counter(unsigned long long int n, char *nbr, t_format f)
{
	int		len;
	char	*str;

	len = ft_strlen(nbr) - 1;
	if (n == 0 && f.precision == 0)
		len = f.precision;
	f.precision -= len;
	if (f.precision < 0)
		f.precision = 0;
	f.width -= f.precision + len + f.plus;
	if (f.width < 0)
		f.width = 0;
	if (!(str = malloc((f.width + f.precision + len + f.plus) * sizeof(*str))))
		exit(1);
	ft_intfill(str, nbr, f, len);
	write(1, str, f.width + f.precision + len + f.plus);
	free(str);
	free(nbr);
	return (f.width + f.precision + len + f.plus);
}

int		f_u(va_list ap, t_format f)
{
	unsigned long long int	n;
	char					*nbr;

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
	nbr = ft_ultra_itoa(n, 10, 0, "0123456789");
	return (u_counter(n, nbr, f));
}
