/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 18:04:27 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/04 20:51:05 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_swap(void *a, void *b, size_t size)
{
	while (size-- > 0)
	{
		*(unsigned char *)a ^= *(unsigned char *)b;
		*(unsigned char *)b ^= *(unsigned char *)a;
		*(unsigned char *)a++ ^= *(unsigned char *)b++;
	}
}
