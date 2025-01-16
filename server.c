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
#include <stdio.h>
//static int	confirm_message(pid)
//{
//	if (kill(pid, SIGUSR1))
//		return (-1);
//	return (0);
//}

//static void	print_sig(int sig)
//{
//	if (sig == SIGUSR1)
//		ft_printf("1");
//	else if (sig == SIGUSR2)
//		ft_printf("0");
//	else
//		ft_printf("unknown signal\n");
//	//confirm_message(
//}

static int	store_cli_pid(int sig, int *cli_pid)
{
	static int	i = 1;

	encode_int(sig, cli_pid);
	if (i == 32)
	{
		//ft_printf("\ncli_pid %d\n", *cli_pid);
		i = 1;
		return (1);
	}
	i++;
	return (0);
}

static int	store_byte(int sig, char *c)
{
	static int	i = 1;

	//print_sig(sig);
	//printf("*c -> %c\n", *c);
	encode_byte(sig, c);
	ft_printf("store_byte call %d\n", i);
	if (i == 8)
	{
		ft_printf("store_byte byteend result %c\n\n", *c);
		//// DEBUG don't print 
		//int	ptr = 0;
		//ftpf_putuibase_fd((unsigned int)c, "01", 1, &ptr);
		//ft_printf("\n\n");
		//// ENDDEBUG
		i = 1;
		return (1);
	}
	i++;
	return (0);
}

static int	reset_data(t_connection_data *data)
{
	if (data == NULL)
		return (-1);
	data->status = WAITING;
	data->cli_pid = 0;
	data->c = 0;
	if (data->str)
		free(data->str);
	data->str = NULL;
	return (0);
}

static void	signal_handler(int sig)
{
	static t_connection_data	data = {
		.status = WAITING,
		.cli_pid = 0,
		.c = 0,
		.str = NULL,
	};
	char	*tmp;

	if (data.status == WAITING)
	{
		if (store_cli_pid(sig, &(data.cli_pid)))
		{
			data.status = CONNECTED;
			ft_printf("server connected to client %d\n", data.cli_pid);
		}
	}
	else
	{
		//ft_printf("data.status -> %d\n", data.status);
		if (store_byte(sig, &(data.c)))
		{
			ft_printf("data.c %c\n", data.c);
			if (data.c == '\0')
			{
				ft_printf("SRV OUT : %s\n", data.str);
				ft_printf("reset data\n");
				reset_data(&data);
				return ;
			}
			//ft_printf("data.c -> %c\n", data.c);
			tmp = ft_strjoin(data.str, &(data.c));
			free(data.str);
			data.str = tmp;
			ft_printf("data.str %s\n", data.str);
		}
	}
}


int	main(int argc, char **argv)
{
	struct sigaction	sigact;
	int	cli_pid;

	cli_pid = 0;
	(void)argv;
	//sigact.sa_handler = &print_sig;
	sigact.sa_handler = &signal_handler;
	if (argc != 1)
		return (-1);
	ft_printf("%d\n", getpid());
	while (1)
	{
		sigaction(SIGUSR1, &sigact, NULL);
		sigaction(SIGUSR2, &sigact, NULL);
		pause();
	}
	return (0);
}
