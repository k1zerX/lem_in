/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_infix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 23:19:42 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/25 23:19:43 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	avl_infix(t_avl_node *node, void (*f)(t_avl_node *node))
{
	if (!node)
		return ;
	avl_infix(node->left, f);
	(*f)(node);
	avl_infix(node->right, f);
}
