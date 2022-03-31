/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:42:17 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 10:42:18 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_modint(t_flag *data, int n, int size, char *res)
{
	char	c;
	int		i;

	c = '0';
	if (!n && !data->accur && data->f_dot)
		c = ' ';
	i = 0;
	while (i < size)
	{
		res[i] = c;
		i++;
	}
	res[size] = 0;
	if (data->f_space && data->accur >= data->numb && n >= 0)
	{
		write(1, " ", 1);
		data->len = data->len + 1;
	}
}

int	ft_size_di(int c, int sys, t_flag *data)
{
	int	result;

	result = 0;
	if (c < 0 || data->plus)
		result++;
	while (c / sys)
	{
		c = c / sys;
		result++;
	}
	if (!data->f_dot && data->numb > result && data->f_zero)
		result = data->numb - 1;
	return (result + 1);
}

void	ft_nbr_rec(int nb, int size, char *sys, t_flag *data)
{
	int	i;

	i = data->sys_len;
	if (nb == -2147483648)
	{
		ft_nbr_rec(nb / i, size - 1, sys, data);
		data->res[size - 1] = sys[-(nb % i)];
	}
	else if (nb < 0)
	{
		data->res[0] = '-';
		ft_nbr_rec(-nb, size, sys, data);
	}
	else
	{
		if (nb / i)
			ft_nbr_rec(nb / i, size - 1, sys, data);
		data->res[size - 1] = sys[nb % i];
		if (data->plus && data->nb >= 0)
		{
			data->res[0] = '+';
			if (!data->nb && !data->accur && !data->numb && data->f_dot)
				data->res[1] = 0;
		}
	}
}

char	*ft_itoa_pf(int n, char *sys, t_flag *data)
{
	int		size;

	size = ft_size_di(n, ft_strlen_s(sys, 0), data);
	if (size < data->accur)
	{
		size = data->accur;
		if (n < 0)
			size++;
	}
	if (n < 0 && size == data->accur)
		size++;
	if (data->plus && size <= data->accur)
		size++;
	data->res = malloc(sizeof(char) * (size + 1));
	if (!data->res)
		return (ft_mal_def(data->res, data));
	ft_modint(data, n, size, data->res);
	data->sys_len = ft_strlen_s(sys, 0);
	data->nb = n;
	ft_nbr_rec(n, size, sys, data);
	return (data->res);
}

char	*ft_add_int(int num, t_flag *data)
{
	char	*res;
	int		i;

	res = ft_itoa_pf(num, "0123456789", data);
	if (res && !data->accur && !num && !data->numb
		&& data->f_dot && !data->plus)
		res[0] = 0;
	if (res && !data->accur && !num && data->numb && data->f_dot)
	{
		i = -1;
		while (res[++i])
		{
			if (res[i] == '0')
			{
				res[i] = ' ';
				if (data->f_dot && data->numb && !data->accur && !num)
					res[i] = 0;
			}
		}
	}
	ft_space_for_int(data, num, res);
	return (res);
}
