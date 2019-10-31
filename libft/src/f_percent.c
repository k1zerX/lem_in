/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_percent.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 00:02:13 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/04 16:54:14 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	f_percent(va_list ap, t_format f)
{
	char	*str;

	(void)ap;
	if (f.minus)
		f.zero = 0;
	if (--f.width < 0)
		f.width = 0;
	if (!(str = malloc((f.width + 2) * sizeof(*str))))
		exit(1);
	ft_strfill(str, "%", f, 1);
	write(1, str, f.width + 1);
	free(str);
	return (f.width + 1);
}
