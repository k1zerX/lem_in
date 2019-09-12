/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_balance.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 23:24:00 by kbatz             #+#    #+#             */
/*   Updated: 2019/09/11 23:51:16 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			bfactor(t_avl_node *node)
{
	return (((node->right) ? ((int)node->right->height) : (0)) - \
			((node->left) ? ((int)node->left->height) : (0)));
}

static void			ft_fixheight(t_avl_node *node)
{
	unsigned char	hl;
	unsigned char	hr;

	hl = (node->left) ? (node->left->height) : (0);
	hr = (node->right) ? (node->right->height) : (0);
	node->height = (hl > hr) ? (hl) : (hr) + 1;
}

static t_avl_node	*ft_rotl(t_avl_node *node)
{
	t_avl_node	*tmp;

	tmp = node->right;
	node->right = tmp->left;
	tmp->left = node;
	ft_fixheight(node);
	ft_fixheight(tmp);
	return (tmp);
}

static t_avl_node	*ft_rotr(t_avl_node *node)
{
	t_avl_node	*tmp;

	tmp = node->left;
	node->left = tmp->right;
	tmp->right = node;
	ft_fixheight(node);
	ft_fixheight(tmp);
	return (tmp);
}

t_avl_node			*ft_balance(t_avl_node *node)
{
	char	b;

	ft_fixheight(node);
	if ((b = bfactor(node)) == 2)
	{
		if (bfactor(node->right) < 0)
			node->right = ft_rotr(node->right);
		return (ft_rotl(node));
	}
	else if (b == -2)
	{
		if (bfactor(node->left) > 0)
			node->right = ft_rotl(node->left);
		return (ft_rotr(node));
	}
	return (node);
}
