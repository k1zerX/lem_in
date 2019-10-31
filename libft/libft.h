/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etuffleb <etuffleb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:48:49 by kbatz             #+#    #+#             */
/*   Updated: 2019/10/31 07:01:37 by etuffleb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>
# include <stdio.h>

# define FT_HH		-2
# define FT_H		-1
# define FT_L		1
# define FT_LL		2
# define M_LEN		64
# define E_LEN		15
# define LOG_PR		0.000001
# define LOG_ADD_PR	1000000

# define FT_ABS(x) (x < 0 ? -(x) : x)
# define FT_SIGN(x) (x < 0 ? -1 : 1)
# define FT_MIN(a,b) ((a) < (b) ? (a) : (b))
# define FT_MAX(a,b) ((a) > (b) ? (a) : (b))

# define GNL_BUFF 30

typedef struct			s_sq_elem
{
	void				*content;
	size_t				content_size;
	struct s_sq_elem	*next;
}						t_sq_elem;

typedef struct			s_queue
{
	t_sq_elem			*start;
	t_sq_elem			*end;
	size_t				len;
}						t_queue;

typedef struct			s_stack
{
	t_sq_elem			*start;
	size_t				len;
}						t_stack;

typedef struct			s_file
{
	char				*line;
	int					fd;
}						t_file;

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

int						gnl(const int fd, char **line);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
int						ft_isspace(int c);
int						ft_tolower(int c);
int						ft_toupper(int c);
t_list					*ft_lstnew(void const *content, size_t content_size);
void					ft_lstdelone(t_list **alst, \
								void (*del)(void *, size_t));
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
double					ft_log(double n);
void					ft_bzero(void *s, size_t n);
void					*ft_memalloc(size_t size);
void					*ft_memccpy(void *dst, \
								const void *src, int c, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dst, \
								const void *src, size_t n);
void					ft_memdel(void **ap);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *b, int c, size_t len);
void					*ft_realloc(void *src, size_t size, long dif);
void					ft_swap(void *a, void *b, size_t size);
void					ft_putchar(char c);
void					ft_putchar_fd(char c, int fd);
void					ft_putendl(char const *s);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr(int n);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr(char const *s);
void					ft_putstr_fd(char const *s, int fd);
t_sq_elem				*ft_new_sq_elem(void *content, \
								size_t content_size, char copy);
t_sq_elem				*ft_queue_pop(t_queue *queue);
void					ft_queue_push(t_queue *queue, t_sq_elem *tmp);
t_queue					*ft_queue_new(void);
t_stack					*ft_stack_new(void);
t_sq_elem				*ft_stack_pop(t_stack *stack);
void					ft_stack_push(t_stack *stack, t_sq_elem *tmp);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
char					*ft_strcat(char *s1, const char *s2);
char					*ft_strchr(const char *s, int c);
void					ft_strclr(char *s);
int						ft_strcmp(char *s1, char *s2);
char					*ft_strcpy(char *dst, const char *src);
void					ft_strdel(char **as);
char					*ft_strdup(const char *s1);
int						ft_strequ(char const *s1, char const *s2);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dst, \
								const char *src, size_t size);
size_t					ft_strlen(const char *s);
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s, \
								char (*f)(unsigned int, char));
char					*ft_strncat(char *s1, \
								const char *s2, size_t n);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strncpy(char *dst, const char *src, size_t len);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strnew(size_t size);
char					*ft_strnstr(const char *haystack, \
								const char *needle, size_t len);
char					*ft_strrchr(const char *s, int c);
char					**ft_strsplit(char const *s, char c);
char					*ft_strstr(const char *haystack, const char *needle);
char					*ft_strsub(char const *s, \
								unsigned int start, size_t len);
char					*ft_strtrim(char const *s);
char					*ft_itoa_base(int n, int base);

typedef struct			s_format
{
	unsigned char		sharp	: 1;
	unsigned char		zero	: 1;
	unsigned char		minus	: 1;
	unsigned char		plus	: 1;
	unsigned char		space	: 1;
	unsigned char		l_big	: 1;
	int					width;
	int					precision;
	char				type;
}						t_format;

typedef struct			s_conv
{
	char				conv;
	int					(*f)(va_list ap, t_format f);
}						t_conv;

typedef struct			s_parsed_float
{
	unsigned long		m	: M_LEN;
	unsigned short		e	: E_LEN;
	unsigned short		s	: 1;
}						t_parsed_float;

typedef union			u_float
{
	t_parsed_float		parse;
	long double			val;
}						t_float;

typedef struct			s_float_ip
{
	unsigned long		i;
	int					i_len;
	unsigned long		f;
	int					f_len;
}						t_float_ip;

char					*ft_ultra_itoa(long long int n, int base, \
							char is_signed, const char *digits);
t_format				format(const char *restrict format, int len);
void					reformat(t_format *f, const char *restrict format);
int						count_len(unsigned long a);
void					apa_mul(int power, unsigned char *str, int len, int *l);
char					*apa_float(long double n);
void					ft_intfill(char *str, char *nbr, t_format f, int len);
void					ft_strfill(char *str, char *s, t_format f, int len);
int						ft_strlen_n(char *str);
int						ft_ascii(char *s, t_format f);
int						f_percent(va_list ap, t_format f);
int						f_s(va_list ap, t_format f);
int						f_c(va_list ap, t_format f);
int						f_p(va_list ap, t_format f);
int						f_d(va_list ap, t_format f);
int						f_i(va_list ap, t_format f);
int						f_o(va_list ap, t_format f);
int						f_u(va_list ap, t_format f);
int						f_x(va_list ap, t_format f);
int						f_big_x(va_list ap, t_format f);
int						f_f(va_list ap, t_format f);
int						ft_printf(const char *restrict str, ...);
void					ft_bzero(void *ptr, size_t size);
int						mini_atoi(const char *restrict *format, int *len);
char					ft_isdigit_p(char c);
int						itoa_len(unsigned long long int nbr, int base);
char					*ft_strcpy(char *dst, const char *src);
int						ft_find_dot(char *str);
void					ft_treatment(char *nbr);
void					apa_fill_i(unsigned char *str, unsigned long m, \
							int len, int k);
char					*ft_to_char(unsigned char *str, size_t len);

#endif
