/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_s.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:02:28 by etuffleb          #+#    #+#             */
/*   Updated: 2019/08/04 19:18:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	f_s(va_list ap, t_format f)
{
	char	*s;
	char	*str;
	int		len;

	s = va_arg(ap, char *);
	if (!s)
		s = "(null)";
	len = ft_strlen(s);
	if (f.minus)
		f.zero = 0;
	if (f.precision != -1 && f.precision < len)
		len = f.precision;
	f.width -= len;
	if (f.width < 0)
		f.width = 0;
	if (!(str = malloc((f.width + len) * sizeof(*str))))
		exit(1);
	ft_strfill(str, s, f, len);
	write(1, str, f.width + len);
	free(str);
	return (f.width + len);
}
