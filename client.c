/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:50:08 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 11:18:54 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//static int	stream_byte(int pid, char c)
//{
//	int	i;
//	int	err;
//
//	i = 0;
//	while (i < 8)
//	{
//		if (128 & c)
//			err = kill(pid, SIGUSR1);
//		else
//			err = kill(pid, SIGUSR2);
//		if (err == -1)
//			return (-1);
//		c = c << 1;
//		i++;
//		pause();
//	}
//	return (0);
//}
static int	stream_int(int pid, int d)
{
	int	i;
	int	err;

	i = 0;
	while (i < 32)
	{
		if (2147483648 & d)
			err = kill(pid, SIGUSR1);
		else
			err = kill(pid, SIGUSR2);
		if (err == -1)
			return (-1);
		d = d << 1;
		i++;
		usleep(100);
	}
	return (0);
}

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
		pause();
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	srv_pid;
	int	i;
	struct sigaction	sigact;

	if (argc != 3)
		return (-1);
	srv_pid = ft_atoi(argv[1]);
	i = 0;
	sigact.sa_handler = &signal_handler;
	if (srv_pid > 0)
	{
		stream_int(srv_pid, getpid());
		while (argv[2][i])
		{
			sigaction(SIGUSR1, &sigact, NULL);
			stream_byte(srv_pid, argv[2][i++]);
		}
		stream_byte(srv_pid, '\0');
		//if (sigemptyset(sigset) == -1)
		//	return (-1);
		//if (sigaddset(sigset, SIGUSR1));
		//	return(-1);
	}
	else
		ft_printf("wrong signal (SIGUSR1 == 10; SIGUSR2 == 12)\n");
	return (0);
}
