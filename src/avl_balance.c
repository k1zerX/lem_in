/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_balance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:24:00 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/25 20:49:39 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

static char		bfactor(t_node *node)
{
	return (HEIGHT(node->right) - HEIGHT(node->left));
}

static void		fixheight(t_node *node)
{
	unsigned char	hl;
	unsigned char	hr;

	hl = HEIGHT(node->left);
	hr = HEIGHT(node->right);
	node->height = (hl > hr) ? (hl) : (hr) + 1;
}

static t_node	*rotl(t_node *node)
{
	t_node	*tmp;

	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	fixheight(node);
	fixheight(tmp);
	return (tmp);
}

static t_node	*rotr(t_node *node)
{
	t_node	*tmp;

	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	fixheight(node);
	fixheight(tmp);
	return (tmp);
}

t_node			*avl_balance(t_node *node)
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
