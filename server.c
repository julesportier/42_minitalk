/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 14:07:21 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 08:38:10 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//static int	confirm_message(pid)
//{
//	if (kill(pid, SIGUSR1))
//		return (-1);
//	return (0);
//}

void	print_sig(int sig)
{
	if (sig == SIGUSR1)
		ft_printf("1");
	else if (sig == SIGUSR2)
		ft_printf("0");
	else
		ft_printf("unknown signal\n");
	//confirm_message(
}

void	signal_handler(int sig)
{
	static int	i = 1;
	static unsigned char	c = 0;

	print_sig(sig);
	encode_byte(sig, &c);
	if (i % 8 == 0 && i != 0)
	{
		ft_printf("%c\n", c);
		//// DEBUG don't print 
		//int	ptr = 0;
		//ftpf_putuibase_fd((unsigned int)c, "01", 1, &ptr);
		//ft_printf("\n\n");
		//// ENDDEBUG
		c = 0;
	}
	i++;
}

int	main(int argc, char **argv)
{
	struct sigaction	sigact;

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
