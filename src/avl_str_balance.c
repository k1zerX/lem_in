/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_str_balance.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:24:00 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 07:39:09 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

static char			bfactor(t_avl_str *node)
{
	return (HEIGHT(node->right) - HEIGHT(node->left));
}

static void			fixheight(t_avl_str *node)
{
	unsigned char	hl;
	unsigned char	hr;

	hl = HEIGHT(node->left);
	hr = HEIGHT(node->right);
	node->height = (hl > hr) ? (hl) : (hr) + 1;
}

static t_avl_str	*rotl(t_avl_str *node)
{
	t_avl_str	*tmp;

	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	fixheight(node);
	fixheight(tmp);
	return (tmp);
}

static t_avl_str	*rotr(t_avl_str *node)
{
	t_avl_str	*tmp;

	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	fixheight(node);
	fixheight(tmp);
	return (tmp);
}

t_avl_str			*avl_str_balance(t_avl_str *node)
{
	char	b;

	fixheight(node);
	if ((b = bfactor(node)) == 2)
	{
		if (bfactor(node->right) < 0)
			node->right = rotr(node->right);
		return (rotl(node));
	}
	else if (b == -2)
	{
		if (bfactor(node->left) > 0)
			node->left = rotl(node->left);
		return (rotr(node));
	}
	return (node);
}
