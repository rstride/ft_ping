/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	send_ping(t_ping *ping)
{
	char	packet[PACKET_SIZE];
	int		sent;

	build_icmp_packet(packet, ping->seq, ping->id);
	sent = sendto(ping->sockfd, packet, PACKET_SIZE, 0,
			(struct sockaddr *)&ping->dest_addr, sizeof(ping->dest_addr));
	if (sent < 0)
	{
		if (errno != EINTR)
			perror("ft_ping: sendto");
		return (-1);
	}
	ping->packets_sent++;
	ping->seq++;
	return (0);
}

static double	calculate_rtt(struct timeval *sent_time)
{
	struct timeval	now;
	double			rtt;

	gettimeofday(&now, NULL);
	rtt = (now.tv_sec - sent_time->tv_sec) * 1000.0;
	rtt += (now.tv_usec - sent_time->tv_usec) / 1000.0;
	return (rtt);
}

int	receive_ping(t_ping *ping)
{
	char				buffer[1024];
	struct sockaddr_in	from;
	socklen_t			fromlen;
	int					bytes;
	struct iphdr		*ip;
	struct icmphdr		*icmp;
	struct timeval		*sent_time;
	double				rtt;

	while (1)
	{
		fromlen = sizeof(from);
		bytes = recvfrom(ping->sockfd, buffer, sizeof(buffer), 0,
				(struct sockaddr *)&from, &fromlen);
		if (bytes < 0)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				return (0);
			if (errno != EINTR)
				perror("ft_ping: recvfrom");
			return (-1);
		}
		ip = (struct iphdr *)buffer;
		icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));
		if (icmp->type == ICMP_ECHOREPLY)
		{
			if (ntohs(icmp->un.echo.id) != ping->id)
				continue ;
			sent_time = (struct timeval *)((char *)icmp
					+ sizeof(struct icmphdr));
			rtt = calculate_rtt(sent_time);
			ping->packets_recv++;
			update_stats(ping, rtt);
			print_ping_reply(ping, bytes - (ip->ihl * 4), ip, icmp, rtt);
			return (0);
		}
		else if (icmp->type != ICMP_ECHO && ping->verbose)
		{
			print_verbose_error(ping, ip, icmp);
		}
	}
	return (0);
}

