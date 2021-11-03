/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-haj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 22:01:50 by abel-haj          #+#    #+#             */
/*   Updated: 2020/01/01 18:40:00 by abel-haj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	size_t	result;

	result = 0;
	if (n < 0)
	{
		ft_putchar('-');
		result = -((size_t)n);
	}
	else
		result = n;
	if (result < 10)
		ft_putchar(result + 48);
	else
	{
		ft_putnbr(result / 10);
		ft_putchar((result % 10) + 48);
	}
}
