/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:46:00 by sacgarci          #+#    #+#             */
/*   Updated: 2024/10/09 06:37:36 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_base(char *base, char c)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (ft_tolower(base[i]) == c || ft_toupper(base[i]) == c)
			return (i);
		++i;
	}
	return (-1);
}

int	ft_atoi_base(const char *nptr, char *base)
{
	int	i;
	int	total;
	int	minus;

	minus = 0;
	total = 0;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = 1;
		i++;
	}
	while (is_in_base(base, nptr[i]) != -1)
	{
		total = (total * ft_strlen(base)) + (is_in_base(base, nptr[i]));
		i++;
	}
	if (minus == 1)
		return (-total);
	return (total);
}
