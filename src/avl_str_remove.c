/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_str_remove.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:50:30 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:17:56 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

static t_avl_str	*findmin(t_avl_str *node)
{
	return ((node->left) ? (findmin(node->left)) : (node));
}

static t_avl_str	*removemin(t_avl_str *node)
{
	if (!node->left)
		return (node->right);
	node->left = removemin(node->left);
	return (avl_str_balance(node));
}

t_avl_str	*avl_str_remove(t_avl_str *root, char *key, \
		int (*cmp)(char *a, char *b))
{
	int		buf;
	t_avl_str	*l;
	t_avl_str	*r;
	t_avl_str	*min;

	if (!root)
		return (NULL);
	if ((buf = (*cmp)(key, root->key)) < 0)
		root->left = avl_str_remove(root->left, key, cmp);
	else if (buf > 0)
		root->right = avl_str_remove(root->right, key, cmp);
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
		return (avl_str_balance(min));
	}
	return (avl_str_balance(root));
}
