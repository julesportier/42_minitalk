/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_stream.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 08:31:07 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 13:54:41 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	encode_byte(int sig, char *c)
{
	*c = *c << 1;
	if (sig == SIGUSR1)
		*c = 1 | *c;
}

int	store_byte(int sig, char *c)
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

int	stream_byte(int pid, char c)
{
	static int	i;

	if (128 & (c << i))
	{
		if (kill(pid, SIGUSR1) == -1)
			return (-1);
	}
	else
	{
		if (kill(pid, SIGUSR2) == -1)
			return (-1);
	}
	i++;
	if (i == 8)
	{
		i = 0;
		return (1);
	}
	return (0);
}

int	init_mask(struct sigaction *sigact)
{
	if (sigemptyset(&sigact->sa_mask) == -1)
		return (-1);
	if (sigaddset(&sigact->sa_mask, SIGUSR1) == -1)
		return (-1);
	if (sigaddset(&sigact->sa_mask, SIGUSR2) == -1)
		return (-1);
	return (0);
}
