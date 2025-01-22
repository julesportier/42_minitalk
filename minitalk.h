/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:16:46 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 13:55:26 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include "libft/libft.h"
# include "libft/ftpf_printf.h"

# ifndef TIMEOUT
#  define TIMEOUT 10000
# endif

void	encode_byte(int sig, char *c);
int		store_byte(int sig, char *c);
int		stream_byte(int pid, char c);
int		init_mask(struct sigaction *sigact);

typedef struct s_string_data
{
	char	c;
	char	*str;
}	t_string_data;

#endif
