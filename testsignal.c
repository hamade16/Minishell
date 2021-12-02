/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testsignal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: houbeid <houbeid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 17:11:14 by houbeid           #+#    #+#             */
/*   Updated: 2021/12/01 17:24:15 by houbeid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <readline>

void	handlsignal(int sig)
{
	if (sig == SIGINT)
	{
		printf(">$ \n");
	}
	else if (sig == SIGQUIT)
	{
		
	}
}

int main()
{

	signal(SIGINT, handlsignal);
	signal(SIGQUIT, handlsignal);
	while (1)
	{
		readline
	}
	return 0;
}