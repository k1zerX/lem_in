/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_infix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:50:09 by etuffleb          #+#    #+#             */
/*   Updated: 2019/09/25 20:50:12 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

void	avl_infix(t_node *root, void (*f)(t_node *root))
{
	if (!root)
		return ;
	avl_infix(root->left, f);
	(*f)(root);
	avl_infix(root->right, f);
}
