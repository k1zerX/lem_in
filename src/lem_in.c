/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:30:20 by kbatz             #+#    #+#             */
/*   Updated: 2019/08/24 00:33:31 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int		main(int ac, char **av)
{
	int		ants;
	char	*str;

	gnl(0, &str, 6);
	ants = ft_atoi(str);
	free(str);
	while (gnl(0, &str, 6))
	{
		...;
		free(str);
	}
	return (0);
}
