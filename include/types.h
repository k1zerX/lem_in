/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbatz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:54:24 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/29 19:29:37 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_ctnr	t_ctnr;
typedef struct s_elem	t_elem;

typedef struct s_avl_str	t_avl_str;
typedef struct s_avl_int	t_avl_int;
typedef struct s_edge		t_edge;
typedef struct s_state		t_state;
typedef struct s_room		t_room;
typedef union u_content		t_content;
typedef enum e_type			t_type;

typedef struct	s_path	t_path;
typedef struct	s_ants	t_ants;
typedef struct	s_ant	t_ant;

#endif
