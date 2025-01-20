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

static const char	*g_string_to_send;

static int	stream_byte(int pid, char c)
{
	static int	i;
	int	err;

	if (128 & (c << i))
		err = kill(pid, SIGUSR1);
	else
		err = kill(pid, SIGUSR2);
	if (err == -1)
		return (-1);
	i++;
	if (i == 8)
	{
		i = 0;
		return (1);
	}
	return (0);
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int	char_count;
	int	ret;

	(void)sig;
	(void)context;
	//if (*g_string_to_send[char_count])
	ret = stream_byte(info->si_pid, g_string_to_send[char_count]);
	if (ret == 1)
	{
		char_count++;
		//ft_printf("char_count == %d\n", char_count);
	}
	else if (ret == -1)
		ft_printf("stream failed (wrong pid, sig or permissions)\n"); 
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;
	int	srv_pid;
	int	stream_len;

	if (argc != 3)
		return (-1);
	g_string_to_send = argv[2];
	stream_len = (ft_strlen(g_string_to_send) + 1) * 8;
	srv_pid = ft_atoi(argv[1]);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &signal_handler;
	sigemptyset(&sigact.sa_mask);
	if (srv_pid < 1)
		return (-1);
	//ft_printf("test\n");
	sigaction(SIGUSR1, &sigact, NULL);
	if (stream_byte(srv_pid, g_string_to_send[0]) == -1)
		return (-1);
	while (--stream_len)
	{
		//ft_printf("stream_len == %d\n", stream_len);
		//if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		//	return (-1);
		pause();
	}
	return (0);
}
