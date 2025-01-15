/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:50:08 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 10:50:48 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	stream_byte(int pid, char c)
{
	int	i;
	int	err;

	i = 0;
	while (i < 8)
	{
		if (128 & c)
			err = kill(pid, SIGUSR1);
		else
			err = kill(pid, SIGUSR2);
		if (err == -1)
			return (-1);
		c = c << 1;
		i++;
		usleep(2);
	}
	return (0);
}

static	int	send_pid(int pid)
{
	int	i;
	char err;

	i = 4;
	while (i--)
	{
		err = stream_byte(pid, pid >> (i * 8));
		if (err)
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	pid = ft_atoi(argv[1]);
	i = 0;
	if (argc != 3)
		return (-1);
	if (pid > 0)
	{
		send_pid(pid);
		//while (argv[2][i])
		//	stream_byte(pid, argv[2][i++]);
		//stream_byte(pid, '\0');
		//if (sigemptyset(sigset) == -1)
		//	return (-1);
		//if (sigaddset(sigset, SIGUSR1));
		//	return(-1);
	}
	else
		ft_printf("wrong signal (SIGUSR1 == 10; SIGUSR2 == 12)\n");
	return (0);
}
