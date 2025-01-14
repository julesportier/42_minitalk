/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:07:21 by juportie          #+#    #+#             */
/*   Updated: 2025/01/13 12:55:41 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	print_sig(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("1");
	else if (sig == SIGUSR2)
		ft_printf("0");
	else
		ft_printf("unknown signal\n");
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;
	//sigset_t	*sigmask;

	(void)argv;
	//sigmask = init_sig_mask();
	sigact.sa_handler = &print_sig;
	//sigact.sa_mask = *sigmask;
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
