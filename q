/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:59:18 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 08:24:00 by kbatz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "types.h"
# include "read.h"
# include "avl.h"
# include "ctnr.h"

struct							s_path
{
	t_ctnr						*path;
	int							len;
	int							ants;
};

struct							s_ants
{
	t_ant						*start;
	t_ant						*end;
};

struct							s_ant
{
	t_elem						*room;
	t_ant						*next;
	int							ind;
};

struct							s_my_queue
{
	t_qelem						*start;
	t_qelem						*end;
};

struct							s_qelem
{
	t_qelem						*next;
	t_avl_str					*room;
	t_avl_str					*edge_in;
};

struct							s_state_list
{
	t_list_elem					*start;
	t_list_elem					*end;
};

struct							s_list_elem
{
	t_list_elem					*next;
	t_state						*state;
};

struct							s_min
{
	int							min;
	int							ind;
};

void							print_map(t_str_list_elem *start);
void							free_str_list(t_str_list *term);
t_str_list						*is_valid_map(t_read *term);
t_qelem			*queue_pop(t_my_queue *queue);
void			queue_push(t_my_queue *queue, t_avl_str *room, \
					t_avl_str *edge_in);
void			del_elem(t_elem *elem);
t_elem			*new_elem(t_avl_str *edge);
void			del_avl_str(t_avl_str *node);
t_content		new_edge(t_avl_str *room, t_state *state, unsigned char n);
t_state			*new_state(void);
t_content		new_room(void);
t_avl_str		*new_avl_str(char *key, t_content c);
void			ft_exit(void);
void			del_sols(t_path **sols, int n);
void			smart_free(t_avl_str *room);
void			smart_free_rec(t_avl_str *root, t_my_queue *q, t_state_list *l);
void			list_add(t_state_list *list, t_state *state);
void			del_list(t_state_list *list);
void			all_not_dijkstra_fill(t_avl_str *edge_in, \
					t_my_queue *queue, t_avl_str *start, int *len);
void			all_not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, \
					t_avl_str *start, int *len);
void			all_abcdefghijk(t_avl_str *edge_out, t_my_queue *queue, \
					t_avl_str *start, int *len);
void			reset(t_avl_str *start);
void			reset_suffix(t_avl_str *root, t_my_queue *queue);
void			not_dijkstra(t_avl_str *start);
void			not_dijkstra_fill(t_avl_str *room, t_avl_str *edge_in, \
				t_my_queue *queue);
void			not_dijkstra_suffix(t_avl_str *root, t_my_queue *queue, \
					char flag);
void			abcdefghijk(t_avl_str *edge_out, t_my_queue *queue);
void			all_not_dijkstra(t_avl_str *start, t_avl_str *end, int len);
void			check_shortest(t_avl_str *end);
void			check_shortest_rec(t_avl_str *edge_out);
void			path_invert(t_avl_str *end);
void			path_invert_rec(t_avl_str *node);
void			edge_reverse(t_avl_str *edge);
void			move_ants(t_ants *ingame);
void			move_ants_if(t_ant **tmp, t_ant **prev, t_ants *ingame);
void			add_ant(t_ants *ingame, t_elem *start);
void			find_paths(t_avl_str *start, t_avl_str *end, \
					t_path **sols, int len);
void			find_paths_cycle(t_path *tmp, t_avl_str *start);
void            init_edges(t_read *term, char **arr, char *s_n, char *e_n);
int             push_edges(t_read *term, char *str, t_str_list *str_list);
t_avl_str       *init_node(t_read *term, char *str, int *is_start);

#endif
