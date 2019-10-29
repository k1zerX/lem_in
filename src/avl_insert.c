/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_str_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:28:01 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:09:15 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_avl_str	*avl_str_insert(t_avl_str *root, t_avl_str *node, \
		int (*cmp)(char *a, char *b))
{
	if (!root)
		return (node);
	if ((*cmp)(node->key, root->key) < 0)
		root->left = avl_str_insert(root->left, node, cmp);
	else
		root->right = avl_str_insert(root->right, node, cmp);
	return (avl_str_balance(root));
}
