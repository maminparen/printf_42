/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:43:11 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 11:04:27 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct s_flag
{
	int		f_minus;
	int		f_zero;
	int		f_num;
	int		numb;
	int		f_dot;
	int		accur;
	int		f_space;
	int		resh;
	int		plus;
	char	*res;
	int		sys_len;
	int		nb;
	char	*parc_flags;
	int		type;
	int		len;
	int		fl;
}				t_flag;

char	*ft_chr_mod(char c, t_flag *data, char x);
char	*ft_add_char(char c, t_flag *data);
char	*ft_add_char_pr(t_flag *data);
char	*ft_add_str(char *str, t_flag *data);

int		ft_find_number(t_flag *data, char ***str);
int		ft_find_accur(t_flag *data, char ***str);
int		ft_is_flag(char **st, t_flag *data);
int		ft_def_fl(t_flag *data);
void	ft_flags_find(t_flag *data);

int		ft_size_p(unsigned long long c, int sys);
void	ft_str_nbr_p(unsigned long long nb, int size, char *res, char *sys);
char	*ft_itoa_m_p(unsigned long long n, char *sys, t_flag *data);
char	*ft_phexa(unsigned long long num, t_flag *data);
void	ft_write_len(t_flag *data, int fl);

void	ft_init_data(t_flag *data);
void	ft_clear_data(t_flag *data);
int		find_param(char c);
int		ft_strlen_s(const char *str, char c);
int		ft_helper(t_flag *data, const char ***form, char **res);

char	*ft_mal_def(char *str, t_flag *data);
int		ft_save_chars(const char **form, t_flag *data);
int		ft_parc_param(const char **form, t_flag *data);
int		ft_theend(t_flag *data);
int		ft_printf(const char *form, ...);

void	ft_strj_next(char **str);
char	*ft_strjoin_pf(char *s1, char *s2, int i, int f);
char	*ft_char_func(char *str, t_flag *data, int len);
void	ft_con_res(t_flag *data, char *buf);
void	ft_specif(t_flag *data, va_list ar);

void	ft_modint(t_flag *data, int n, int size, char *res);
int		ft_size_di(int c, int sys, t_flag *data);
void	ft_nbr_rec(int nb, int size, char *sys, t_flag *data);
char	*ft_itoa_pf(int n, char *sys, t_flag *data);
char	*ft_add_int(int num, t_flag *data);

int		ft_size_xuo(unsigned int c, int sys, t_flag *data);
void	ft_str_nbr_xuo(unsigned int nb, int size, char *res, char *sys);
char	*ft_itoa_m_xuo(unsigned int n, char *sys, t_flag *data, int i);
char	*ft_add_xnum(unsigned int num, t_flag *data);
void	ft_space_for_int(t_flag *data, int num, char *res);

#endif
