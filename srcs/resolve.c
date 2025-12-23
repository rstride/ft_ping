/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int	resolve_hostname(t_ping *ping)
{
	struct addrinfo	hints;
	struct addrinfo	*res;
	int				ret;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	ret = getaddrinfo(ping->hostname, NULL, &hints, &res);
	if (ret != 0)
	{
		fprintf(stderr, "ft_ping: %s: %s\n",
			ping->hostname, gai_strerror(ret));
		return (-1);
	}
	ping->dest_addr = *(struct sockaddr_in *)res->ai_addr;
	ping->ip_str = strdup(inet_ntoa(ping->dest_addr.sin_addr));
	if (ping->ip_str == NULL)
	{
		freeaddrinfo(res);
		error_msg("strdup failed");
		return (-1);
	}
	freeaddrinfo(res);
	return (0);
}
