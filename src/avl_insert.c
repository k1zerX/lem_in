/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:28:01 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/11 23:43:22 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_node	*avl_insert(t_node *root, t_node *node, \
		int (*cmp)(T_AVL_KEY a, T_AVL_KEY b))
{
	if (!root)
		return (node);
	if ((*cmp)(node->AVL_KEY, root->AVL_KEY) < 0)
		root->left = avl_insert(root->left, node, cmp);
	else
		root->right = avl_insert(root->right, node, cmp);
	return (avl_balance(root));
}
