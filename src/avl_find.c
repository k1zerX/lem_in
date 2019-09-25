/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:49:55 by etuffleb          #+#    #+#             */
/*   Updated: 2019/09/25 20:49:57 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

t_node	*avl_find(t_node *root, T_AVL_KEY key, \
				int (*cmp)(T_AVL_KEY a, T_AVL_KEY b))
{
	int			buf;

	while (root)
		if ((buf = (*cmp)(key, root->AVL_KEY)) < 0)
			root = root->left;
		else if (buf > 0)
			root = root->right;
		else
			break ;
	return (root);
}
