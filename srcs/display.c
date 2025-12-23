/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_ping_header(t_ping *ping)
{
	printf("PING %s (%s): %d data bytes",
		ping->hostname, ping->ip_str, PAYLOAD_SIZE);
	if (ping->verbose)
		printf(", id 0x%04x = %d", ping->id, ping->id);
	printf("\n");
}

void	print_ping_reply(t_ping *ping, int bytes, struct iphdr *ip,
		struct icmphdr *icmp, double rtt)
{
	(void)icmp;
	printf("%d bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n",
		bytes, ping->ip_str, ntohs(icmp->un.echo.sequence),
		ip->ttl, rtt);
}

static const char	*get_icmp_type_name(int type)
{
	static const char	*types[] = {
		"Echo Reply",
		"ICMP 1",
		"ICMP 2",
		"Destination Unreachable",
		"Source Quench",
		"Redirect",
		"ICMP 6",
		"ICMP 7",
		"Echo Request",
		"Router Advertisement",
		"Router Solicitation",
		"Time Exceeded",
		"Parameter Problem",
		"Timestamp Request",
		"Timestamp Reply",
		"Information Request",
		"Information Reply",
		"Address Mask Request",
		"Address Mask Reply"
	};

	if (type >= 0 && type <= 18)
		return (types[type]);
	return ("Unknown ICMP type");
}

void	print_verbose_error(t_ping *ping, struct iphdr *ip,
		struct icmphdr *icmp)
{
	char	src_ip[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &ip->saddr, src_ip, INET_ADDRSTRLEN);
	printf("From %s: icmp_seq=%d %s\n",
		src_ip, ntohs(icmp->un.echo.sequence),
		get_icmp_type_name(icmp->type));
	(void)ping;
}
