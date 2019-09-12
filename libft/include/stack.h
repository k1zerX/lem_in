/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:56:48 by kbatz             #+#    #+#             */
/*   Updated: 2019/02/05 02:12:41 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft.h"

typedef struct			s_stack
{
	t_elem				*start;
	size_t				len;
}						t_stack;

t_stack					*ft_stack_new(void);
t_elem					*ft_stack_pop(t_stack *stack);
void					ft_stack_push(t_stack *stack, t_elem *tmp);

#endif
