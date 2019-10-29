/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_int_insert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:28:01 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:26:08 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_avl_int	*avl_int_insert(t_avl_int *root, t_avl_int *node, \
		int (*cmp)(int a, int b))
{
	if (!root)
		return (node);
	if ((*cmp)(node->key, root->key) < 0)
		root->left = avl_int_insert(root->left, node, cmp);
	else
		root->right = avl_int_insert(root->right, node, cmp);
	return (avl_int_balance(root));
}
