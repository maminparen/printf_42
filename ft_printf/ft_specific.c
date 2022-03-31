/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_specific.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:43:16 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 11:25:15 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_strj_next(char **str)
{
	if (*str)
	{
		free (*str);
		*str = NULL;
	}
}

char	*ft_strjoin_pf(char *s1, char *s2, int i, int f)
{
	int		k;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	k = ft_strlen_s(s1, 0) + ft_strlen_s(s2, 0);
	res = malloc(sizeof(char) * (k + 1));
	if (!res)
		return (NULL);
	while (i++ < k && s1[i])
		res[i] = s1[i];
	j = 0;
	while (*(s2 + j))
	{
		res[i + j] = *(s2 + j);
		j++;
	}
	res[i + j] = 0;
	if (s1)
		free (s1);
	if (s2 && f == 1)
		ft_strj_next(&s2);
	return (res);
}

char	*ft_char_func(char *str, t_flag *data, int len)
{
	char	*res;
	char	c;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (data->numb + 1));
	if (!res)
	{
		data->fl = -1;
		return (str);
	}
	c = ' ';
	if (data->f_zero && !data->f_minus && (data->type == 99
			|| data->type == 115 || data->type == 37))
		c = '0';
	i = data->numb - len;
	res[i] = 0;
	j = -1;
	while (j++ < i - 1)
		res[j] = c;
	if (data->numb < 0 || data->f_minus)
		res = ft_strjoin_pf(str, res, -1, 1);
	else
		res = ft_strjoin_pf(res, str, -1, 1);
	return (ft_mal_def(res, data));
}

void	ft_con_res(t_flag *data, char *buf)
{
	int	len;

	if (!buf || data->fl < 0)
		return ;
	if (data->numb < 0)
	{
		data->f_minus++;
		data->numb = -data->numb;
	}
	if (data->f_dot && data->accur < ft_strlen_s(buf, 0) && data->type == 115)
		buf[data->accur] = 0;
	len = ft_strlen_s(buf, 0);
	if (data->f_num && data->numb > len)
		buf = ft_char_func(buf, data, len);
	if (len < data->numb)
		len = data->numb;
	write (1, buf, len);
	data->len = data->len + len;
	if (buf)
	{
		free (buf);
		buf = NULL;
	}
}

void	ft_specif(t_flag *data, va_list ar)
{
	char	*buf;

	buf = NULL;
	if (data->f_num == -1 && !data->numb)
		data->numb = va_arg(ar, int);
	if (data->f_dot == -1 && !data->accur)
		data->accur = va_arg(ar, int);
	if (ft_def_fl(data))
		return ;
	if (data->type == 99)
		buf = ft_add_char(va_arg(ar, int), data);
	if (data->type == 37)
		buf = ft_add_char_pr(data);
	if (data->type == 115)
		buf = ft_add_str(va_arg(ar, char *), data);
	if (data->type == 100 || data->type == 105)
		buf = ft_add_int(va_arg(ar, int), data);
	if (data->type == 112)
		buf = ft_phexa(va_arg(ar, unsigned long long), data);
	if (data->type == 120 || data->type == 88 || data->type == 117)
		buf = ft_add_xnum(va_arg(ar, unsigned int), data);
	ft_con_res(data, buf);
}
