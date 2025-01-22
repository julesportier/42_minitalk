/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:07:21 by juportie          #+#    #+#             */
/*   Updated: 2025/01/21 14:59:10 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static volatile sig_atomic_t	g_wait_len = 0;

static void	confirm_message(int pid)
{
	if (kill(pid, SIGUSR1) == -1)
		exit(EXIT_FAILURE);
}

// Start by executing store_byte() until it returns 1
// to reinit it's internal static variable.
static void	reset_data(t_string_data *data)
{
	while (store_byte(SIGUSR2, &(data->c)) != 1)
		;
	if (data == NULL)
		exit(EXIT_FAILURE);
	data->c = 0;
	if (data->str)
		free(data->str);
	data->str = NULL;
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static t_string_data	data;
	char					*tmp;

	(void)context;
	if (g_wait_len == -1)
		reset_data(&data);
	g_wait_len = 0;
	if (store_byte(sig, &(data.c)))
	{
		if (data.c == '\0')
		{
			ft_putendl_fd(data.str, 1);
			reset_data(&data);
		}
		else
		{
			tmp = ft_strjoin(data.str, &(data.c));
			free(data.str);
			if (tmp == NULL)
				exit(EXIT_FAILURE);
			data.str = tmp;
		}
	}
	confirm_message(info->si_pid);
}

static int	init_sigaction(void)
{
	struct sigaction	sigact;

	ft_bzero(&sigact, sizeof(struct sigaction));
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &signal_handler;
	//if (init_mask(&sigact) == -1)
	//	return (-1);
	if (sigaction(SIGUSR1, &sigact, NULL) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &sigact, NULL) == -1)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 1)
		return (-1);
	(void)argv;
	if (init_sigaction() == -1)
		return (-1);
	ft_printf("%d\n", getpid());
	while (1)
	{
		usleep(1);
		if (g_wait_len >= 0)
		{
			if (++g_wait_len == TIMEOUT)
				g_wait_len = -1;
		}
	}
	return (0);
}
