/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 15:00:24 by kbatz             #+#    #+#             */
/*   Updated: 2019/03/04 15:42:29 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_stack		*ft_stack_new(void)
{
	t_stack		*stack;

	if (!(stack = ft_memalloc(sizeof(*stack))))
		return (NULL);
	return (stack);
}
