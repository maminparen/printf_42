/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:43:22 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 11:22:34 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_size_xuo(unsigned int c, int sys, t_flag *data)
{
	int	result;

	result = 0;
	while (c / sys)
	{
		c = c / sys;
		result++;
	}
	if (!data->f_dot && data->numb > result && data->f_zero)
		result = data->numb - 1;
	return (result + 1);
}

void	ft_str_nbr_xuo(unsigned int nb, int size, char *res, char *sys)
{
	int	i;

	i = ft_strlen_s(sys, 0);
	if (nb / i)
		ft_str_nbr_xuo(nb / i, size - 1, res, sys);
	res[size - 1] = sys[nb % i];
	res[size] = 0;
}

char	*ft_itoa_m_xuo(unsigned int n, char *sys, t_flag *data, int i)
{
	int		size;
	char	c;
	char	*res;

	size = ft_size_xuo(n, ft_strlen_s(sys, 0), data);
	if (size < data->accur)
		size = data->accur;
	if ((data->type == 'x' || data->type == 'X') && data->resh
		&& n && data->numb != size)
		size = size + 2;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (ft_mal_def(res, data));
	c = 48;
	if (n == 0 && data->accur == 0 && data->f_dot != 0)
		c = 32;
	while (i++ < size)
		res[i] = '0';
	ft_str_nbr_xuo(n, size, res, sys);
	if ((data->type == 'x' || data->type == 'X') && data->resh && n)
	{
		res[0] = '0';
		res[1] = data->type;
	}
	return (res);
}

char	*ft_add_xnum(unsigned int num, t_flag *data)
{
	char	*res;
	int		i;

	if (data->type == 120)
		res = ft_itoa_m_xuo(num, "0123456789abcdef", data, -1);
	if (data->type == 88)
		res = ft_itoa_m_xuo(num, "0123456789ABCDEF", data, -1);
	if (data->type == 117)
		res = ft_itoa_m_xuo(num, "0123456789", data, -1);
	if (res && data->accur == 0 && num == 0 && data->numb == 0
		&& data->f_dot != 0)
		res[0] = 0;
	if (res && data->accur == 0 && num == 0 && data->numb != 0
		&& data->f_dot != 0)
	{
		i = -1;
		while (res[++i])
		{
			if (res[i] == '0')
				res[i] = ' ';
		}
	}
	return (res);
}

void	ft_space_for_int(t_flag *data, int num, char *res)
{
	if (!data->f_dot && !data->accur && data->numb && num >= 0 && data->f_space
		&& data->f_zero && !data->f_minus && ft_strlen_s(res, 0) >= data->numb)
	{
		if (res[0] == '0')
			res[0] = ' ';
		else
			ft_write_len(data, 0);
	}
	if (data->f_space && !data->f_dot && !data->accur && data->numb && num > 0
		&& ft_strlen_s(res, 0) >= data->numb && !data->f_zero)
		ft_write_len(data, 0);
	if (!data->f_dot && !data->accur && data->f_space && data->f_minus
		&& data->numb && num >= 0 && ft_strlen_s(res, 0) < data->numb)
		ft_write_len(data, 1);
	if (data->f_dot && data->numb && data->accur && data->f_space && num >= 0
		&& !data->f_zero && data->f_minus && ft_strlen_s(res, 0) < data->numb)
		ft_write_len(data, 1);
}
