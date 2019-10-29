/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_int_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:50:30 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:26:08 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

static t_avl_int	*findmin(t_avl_int *node)
{
	return ((node->left) ? (findmin(node->left)) : (node));
}

static t_avl_int	*removemin(t_avl_int *node)
{
	if (!node->left)
		return (node->right);
	node->left = removemin(node->left);
	return (avl_int_balance(node));
}

t_avl_int	*avl_int_remove(t_avl_int *root, int key, \
		int (*cmp)(int a, int b))
{
	int		buf;
	t_avl_int	*l;
	t_avl_int	*r;
	t_avl_int	*min;

	if (!root)
		return (NULL);
	if ((buf = (*cmp)(key, root->key)) < 0)
		root->left = avl_int_remove(root->left, key, cmp);
	else if (buf > 0)
		root->right = avl_int_remove(root->right, key, cmp);
	else
	{
		l = root->left;
		r = root->right;
		free(root);
		if (!r)
			return (l);
		min = findmin(r);
		min->right = removemin(r);
		min->left = l;
		return (avl_int_balance(min));
	}
	return (avl_int_balance(root));
}
