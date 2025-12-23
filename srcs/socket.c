/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	create_socket(t_ping *ping)
{
	int				ttl;
	struct timeval	timeout;

	ping->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ping->sockfd < 0)
	{
		if (errno == EPERM || errno == EACCES)
			fprintf(stderr, "ft_ping: socket: Operation not permitted\n");
		else
			perror("ft_ping: socket");
		return (-1);
	}
	ttl = DEFAULT_TTL;
	if (setsockopt(ping->sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
	{
		perror("ft_ping: setsockopt IP_TTL");
		close(ping->sockfd);
		return (-1);
	}
	timeout.tv_sec = RECV_TIMEOUT;
	timeout.tv_usec = 0;
	if (setsockopt(ping->sockfd, SOL_SOCKET, SO_RCVTIMEO,
			&timeout, sizeof(timeout)) < 0)
	{
		perror("ft_ping: setsockopt SO_RCVTIMEO");
		close(ping->sockfd);
		return (-1);
	}
	return (0);
}
