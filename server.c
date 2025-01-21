/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:07:21 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 14:03:56 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	confirm_message(pid)
{
	if (kill(pid, SIGUSR1))
		return (0);
	return (1);
}

static int	store_byte(int sig, char *c)
{
	static int	i = 1;

	encode_byte(sig, c);
	if (i == 8)
	{
		i = 1;
		return (1);
	}
	i++;
	return (0);
}

static int	reset_data(t_string_data *data)
{
	if (data == NULL)
		return (-1);
	data->c = 0;
	if (data->str)
		free(data->str);
	data->str = NULL;
	return (0);
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static t_string_data	data;
	char	*tmp;

	(void)context;
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
			data.str = tmp;
		}
	}
	if (!confirm_message(info->si_pid))
		ft_putendl_fd("server message confirmation failed (wrong pid)", 2);
}


int	main(int argc, char **argv)
{
	struct sigaction	sigact;

	if (argc != 1)
		return (-1);
	(void)argv;
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = &signal_handler;
	if (init_mask(&sigact) == -1)
		return (-1);
	ft_printf("%d\n", getpid());
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
	return (0);
}
