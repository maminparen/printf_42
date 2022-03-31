/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_phexa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:42:29 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 10:42:30 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_size_p(unsigned long long c, int sys)
{
	int	result;

	result = 0;
	while (c / sys)
	{
		c = c / sys;
		result++;
	}
	return (result + 1);
}

void	ft_str_nbr_p(unsigned long long nb, int size, char *res, char *sys)
{
	int	i;

	i = ft_strlen_s(sys, 0);
	if (nb / i)
		ft_str_nbr_p(nb / i, size - 1, res, sys);
	res[size - 1] = sys[nb % i];
}

char	*ft_itoa_m_p(unsigned long long n, char *sys, t_flag *data)
{
	int		size;
	int		i;
	char	*res;

	size = ft_size_p(n, ft_strlen_s(sys, 0)) + 2;
	if (size < data->accur)
		size = data->accur + 2;
	res = malloc(sizeof(char) * (size + 1));
	if (!res)
		return (ft_mal_def(res, data));
	res[size] = 0;
	i = -1;
	while (i++ < size)
		res[i] = 48;
	ft_str_nbr_p(n, size, res, sys);
	res[size] = 0;
	res[0] = '0';
	res[1] = 'x';
	if (data->f_dot && !data->accur)
		res[2] = 0;
	return (res);
}

char	*ft_phexa(unsigned long long num, t_flag *data)
{
	char	*res;

	res = ft_itoa_m_p(num, "0123456789abcdef", data);
	return (res);
}

void	ft_write_len(t_flag *data, int fl)
{
	write(1, " ", 1);
	data->len++;
	if (fl)
		data->numb--;
}
