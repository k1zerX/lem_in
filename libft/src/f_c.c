/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 23:09:42 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/04 19:18:06 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	f_c(va_list ap, t_format f)
{
	char	c;
	char	*str;

	c = va_arg(ap, int);
	if (f.minus)
		f.zero = 0;
	if (--f.width < 0)
		f.width = 0;
	if (!(str = malloc((f.width + 1) * sizeof(*str))))
		exit(1);
	ft_strfill(str, &c, f, 1);
	write(1, str, f.width + 1);
	free(str);
	return (f.width + 1);
}
