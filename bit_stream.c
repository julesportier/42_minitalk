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

void	encode_int(int sig, int	*i)
{
	*i = *i << 1;
	if (sig == SIGUSR1)
		*i = 1 | *i;
}
