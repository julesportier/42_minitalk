/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 12:50:08 by juportie          #+#    #+#             */
/*   Updated: 2025/01/21 14:59:55 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_srv_confirmation = 1;

static int	init_main_vars(
	const char *argv1, const char *argv2,
	int *s_len, int *srv_pid
)
{
	*s_len = (ft_strlen(argv2) + 1) * 8;
	*srv_pid = ft_atoi(argv1);
	if (*srv_pid < 1)
		return (-1);
	return (0);
}

static void	signal_handler(int sig)
{
	(void)sig;

	g_srv_confirmation = 1;
}

static int	init_sigaction(void)
{
	struct sigaction sigact;

	ft_bzero(&sigact, sizeof(struct sigaction));
	sigact.sa_handler = &signal_handler;
	if (init_mask(&sigact) == -1)
		return (-1);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (-1);
	return (0);
}

static int	listen_confirmation(int srv_pid, char *str, int *s_len)
{
	static int	iter;
	static int	char_count;
	int	ret;

	if (++iter == TIMEOUT)
		return (-1);
	if (g_srv_confirmation == 1)
	{
		g_srv_confirmation = 0;
		iter = 0;
		if ((*s_len)--)
		{
			ret = stream_byte(srv_pid, str[char_count]);
			if (ret == 1)
				char_count++;
			else if (ret == -1)
				return (-1);
		}
		else
			return (1);
	}
	usleep(1);
	return (0);
}

int	main(int argc, char **argv)
{
	int	srv_pid;
	int	s_len;
	int	char_count;
	int	ret;

	if (argc != 3)
		return (-1);
	if (init_main_vars(argv[1], argv[2], &s_len, &srv_pid) == -1)
		return (-1);
	if (init_sigaction() == -1)
		return (-1);
	char_count = 0;
	while (1)
	{
		ret = listen_confirmation(srv_pid, argv[2], &s_len);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
			return (0);
	}
	return (0);
}
