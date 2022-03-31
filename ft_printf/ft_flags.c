/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hzona <hzona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 10:42:09 by hzona             #+#    #+#             */
/*   Updated: 2021/10/17 11:25:18 by hzona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_find_number(t_flag *data, char ***str)
{
	unsigned long long	res;

	data->f_num++;
	res = 0;
	while (***str && ***str >= '0' && ***str <= '9' && res <= 2147483647)
	{
		res = res * 10 + (***str - 48);
		**str = **str + 1;
	}
	if (data->numb || res > 2147483647)
		data->fl = -1;
	data->numb = (int)res;
	if (data->numb == 0 && ***str == '*')
	{
		data->f_num = -1;
		if (*(**str + 1) != 0 && *(**str + 1) != '.')
			data->fl = -1;
	}
	if (***str != 0 && ***str != '.' && ***str != '*')
		data->fl = -1;
	return (0);
}

int	ft_find_accur(t_flag *data, char ***str)
{
	unsigned long long	res;

	**str = **str + 1;
	data->f_dot++;
	res = 0;
	while (***str && res <= 2147483647 && ***str >= '0' && ***str <= '9')
	{
		res = res * 10 + (***str - 48);
		**str = **str + 1;
	}
	if ((***str != 0 && ***str != '*') || res > 2147483647 || data->accur)
	{
		data->fl = -1;
		return (0);
	}
	data->accur = (int)res;
	if (data->accur == 0 && ***str == '*')
	{
		data->f_dot = -1;
		if (*(**str + 1) != 0)
			data->fl = -1;
	}
	return (0);
}

int	ft_is_flag(char **st, t_flag *data)
{
	if ((**st < '-' || **st > '9' || **st == 47) && **st != 32 && **st != 42
		&& **st != '#' && **st != '+')
		return (1);
	if ((**st >= '1' && **st <= '9') || **st == '*')
		ft_find_number(data, &st);
	if (**st == '.')
		ft_find_accur(data, &st);
	if (**st == '-')
		data->f_minus++;
	if (**st == ' ')
		data->f_space++;
	if (**st == '0')
		data->f_zero++;
	if (**st == '#')
		data->resh++;
	if (**st == '+')
		data->plus++;
	return (0);
}

int	ft_def_fl(t_flag *data)
{
	if (data->accur >= 2147483632 || data->accur <= -2147483632
		|| data->numb >= 2147483632 || data->numb <= -2147483632)
	{
		data->fl = -1;
		return (1);
	}
	if (data->accur < 0)
	{
		data->f_dot = 0;
		data->accur = 0;
	}
	if ((data->type == 100 || data->type == 105) && data->f_zero
		&& !data-> f_dot && !data->accur && data->numb && data->f_minus)
	{
		data->accur = 0;
		data->f_dot = 0;
		data->f_zero = 0;
	}
	return (0);
}

void	ft_flags_find(t_flag *data)
{
	char	*pflag;

	if (!data->parc_flags)
		return ;
	if (data->fl)
	{
		free (data->parc_flags);
		return ;
	}
	pflag = data->parc_flags;
	while (*pflag && !data->fl)
	{
		if (ft_is_flag(&pflag, data))
			data->fl = -1;
		if (*pflag)
			pflag++;
	}
	free (data->parc_flags);
	data->parc_flags = NULL;
}
