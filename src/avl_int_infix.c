/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avl_int_infix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:50:09 by etuffleb          #+#    #+#             */
/*   Updated: 2019/10/29 19:26:09 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "avl.h"

void	avl_int_infix(t_avl_int *root, void (*f)(t_avl_int *root))
{
	if (!root)
		return ;
	avl_int_infix(root->left, f);
	(*f)(root);
	avl_int_infix(root->right, f);
}
