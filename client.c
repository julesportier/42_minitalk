/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:50:08 by juportie          #+#    #+#             */
/*   Updated: 2025/01/13 13:00:26 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	stream_char(int pid, char c)
{
	int	i;
	int	err;

	i = 0;
	while (i < 8)
	{
		if (c % 2 != 0)
			err = kill(pid, SIGUSR1);
		else
			err = kill(pid, SIGUSR2);
		if (err == -1)
			return (-1);
		c = c >> 1;
		i++;
		usleep(1000);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid;

	pid = ft_atoi(argv[1]);
	if (argc != 3)
		return (-1);
	if (pid > 0)
	{
		//kill(pid, argv[2][0]);
		stream_char(pid, argv[2][0]);
		//if (sigemptyset(sigset) == -1)
		//	return (-1);
		//if (sigaddset(sigset, SIGUSR1));
		//	return(-1);
	}
	else
		ft_printf("wrong signal (SIGUSR1 == 10; SIGUSR2 == 12)\n");
	return (0);
}
