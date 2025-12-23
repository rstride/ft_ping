/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	build_icmp_packet(char *packet, uint16_t seq, uint16_t id)
{
	struct icmphdr	*icmp;
	struct timeval	*tv;

	memset(packet, 0, PACKET_SIZE);
	icmp = (struct icmphdr *)packet;
	icmp->type = ICMP_ECHO;
	icmp->code = 0;
	icmp->un.echo.id = htons(id);
	icmp->un.echo.sequence = htons(seq);
	icmp->checksum = 0;
	tv = (struct timeval *)(packet + sizeof(struct icmphdr));
	gettimeofday(tv, NULL);
	icmp->checksum = calculate_checksum(packet, PACKET_SIZE);
}
