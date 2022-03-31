/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:42:00 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 10:42:00 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_chr_mod(char c, t_flag *data, char x)
{
	x = ' ';
	if (data->f_zero && !data->f_minus)
		x = '0';
	if (data->f_minus)
	{
		write(1, &c, 1);
		while (data->numb-- > 1)
		{
			write(1, &x, 1);
			data->len = data->len + 1;
		}
	}
	else
	{
		while (data->numb-- > 1)
		{
			write(1, &x, 1);
			data->len = data->len + 1;
		}
		write(1, &c, 1);
	}
	data->len = data->len + 1;
	return (NULL);
}

char	*ft_add_char(char c, t_flag *data)
{
	char	*res;

	if (data->numb == 0)
		data->numb = 1;
	if (c == 0 && data->numb < 0)
	{
		data->numb = -data->numb;
		data->f_minus++;
	}
	if (c == 0)
		return (ft_chr_mod(c, data, 0));
	res = malloc(sizeof(char) * 2);
	if (!res)
		return (ft_mal_def(res, data));
	res[0] = c;
	res[1] = 0;
	return (res);
}

char	*ft_add_char_pr(t_flag *data)
{
	char	*res;

	if (data->numb == 0)
		data->numb = 1;
	res = malloc(sizeof(char) * 2);
	if (!res)
		return (ft_mal_def(res, data));
	res[0] = '%';
	res[1] = 0;
	return (res);
}

char	*ft_add_str(char *str, t_flag *data)
{
	char	*res;
	char	*buf;
	int		i;

	if (!str)
	{
		buf = "(null)";
		res = malloc(sizeof(char) * 7);
		if (!res)
			return (ft_mal_def(res, data));
		i = -1;
		while (i++ < 7)
			res[i] = buf[i];
		return (res);
	}
	i = ft_strlen_s(str, 0) + 1;
	res = malloc(sizeof(char) * i);
	if (!res)
		return (ft_mal_def(res, data));
	while (--i != -1)
		res[i] = str[i];
	return (res);
}
