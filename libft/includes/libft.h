/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:24:41 by pierre            #+#    #+#             */
/*   Updated: 2024/09/05 16:01:46 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <fcntl.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	int				len;
}			t_list;

// mandatory gnl

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

//libft
void	*ft_memset(void *set, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memccpy(void *dest, const void *src, int c, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*ft_strndup(char *s, int n);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
double	ft_atoi(const char *nptr);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_toupper(int c);
int		ft_tolower(int c);
void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
char	*ft_strnew(size_t size);
void	ft_strdel(char **as);
void	ft_strclr(char *s);
void	ft_striter(char *s, void (*f)(char *));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmap(char const *s, char (*f)(char));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strequ(char const *s1, char const *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(long n, int fd);
t_list	*ft_lstnew_b(void *content, int len);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast_b(t_list *lst);
void	ft_lstadd_back_b(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_atoi_base(char *str, char *base, int base_len);

// printf

typedef struct s_disp
{
	int	flag;
	int	precision;
	int	format;
}		t_disp;

int		ft_printf(const char *str, ...);
int		displayer(const char *str, va_list valist);
int		disp_formats(va_list valist, t_disp frm);
int		format_x(long u, int c, t_disp data);
int		is_match(char c, char *match);
void	to_hex(unsigned long nbr, int (*f)(int));
int		format_s(char *str, t_disp data);
int		format_p(void *p, t_disp data);
int		numb_len(long num, int base);
int		numb_len_ul(unsigned long num, int base);
int		format_d_i(long nbr, t_disp data, int is_neg);
int		format_u(long l, t_disp data);
int		displayer_aux(int n, va_list valist, t_disp data);
int		next_disp(const char *str);
t_disp	init_disp(const char *str);
int		disp_padding(t_disp data, int padding, int is_neg);
int		disp_space(int precision);
int		disp_str_n(char *str, int precision);
int		format_c(char c, t_disp data);
int		next_disp(const char *str);
int		get_format(const char *str);

//gnl &bonus
// char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
char	*get_line_mine(char *str);
char	*get_buffer_line(char *buffer, int fd);
char	*reset_buffer(char	*buffer);
char	*ft_strjoinaux(char *buffer, char *str);
// void	ft_lstcleargnl(t_list **lst);

// char	*get_next_line(int fd);
// int		contains_nextline(char *s);
// int		add_node(t_list **lst, int len, char *buffer);
// char	*get_string(t_list *lst);
// int		get_total_length(t_list *lst);
// int		ft_setter(char *buffer);

//  math
int		ft_pow(int i, int pow);
double	ft_atof(const char *string);

void	clear_wordar(char **str);

#endif
