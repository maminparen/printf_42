/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:42:35 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 11:25:14 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_init_data(t_flag *data)
{
	data->f_minus = 0;
	data->f_zero = 0;
	data->f_num = 0;
	data->numb = 0;
	data->f_dot = 0;
	data->accur = 0;
	data->f_space = 0;
	data->resh = 0;
	data->plus = 0;
	data->parc_flags = NULL;
	data->type = 0;
	data->fl = 0;
	data->len = 0;
}

void	ft_clear_data(t_flag *data)
{
	data->f_minus = 0;
	data->f_zero = 0;
	data->f_num = 0;
	data->numb = 0;
	data->f_dot = 0;
	data->accur = 0;
	data->f_space = 0;
	data->resh = 0;
	data->plus = 0;
	data->type = 0;
}

int	find_param(char c)
{
	if (c == 'c')
		return (99);
	if (c == 's')
		return (115);
	if (c == 'p')
		return (112);
	if (c == 'd')
		return (100);
	if (c == 'i')
		return (105);
	if (c == 'u')
		return (117);
	if (c == 'x')
		return (120);
	if (c == 'X')
		return (88);
	if (c == '%')
		return (37);
	return (0);
}

int	ft_strlen_s(const char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	ft_helper(t_flag *data, const char ***form, char **res)
{
	int	i;

	if (!*form || !data)
		return (-1);
	i = ft_strlen_s(**form, '%');
	*res = malloc(sizeof(char) * (i + 1));
	if (!(*res))
		return (-3);
	return (i);
}
