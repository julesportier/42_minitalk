/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juportie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 11:16:46 by juportie          #+#    #+#             */
/*   Updated: 2025/01/15 08:53:46 by juportie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"
#include "libft/ftpf_printf.h"

void	encode_byte(int sig, unsigned char *c);
void	encode_int(int sig, int	*i);

#endif
