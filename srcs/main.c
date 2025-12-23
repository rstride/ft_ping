/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 23:36:42 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_ping	*g_ping = NULL;

static void	signal_handler(int sig)
{
	(void)sig;
	if (g_ping)
	{
		g_ping->running = 0;
	}
}

static void	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}

static void	ping_loop(t_ping *ping)
{
	while (ping->running)
	{
		if (send_ping(ping) < 0)
		{
			if (ping->running)
				error_msg("send_ping failed");
		}
		else
		{
			receive_ping(ping);
		}
		if (ping->running)
			usleep(PING_INTERVAL);
	}
}

int	main(int argc, char **argv)
{
	t_ping	ping;

	memset(&ping, 0, sizeof(t_ping));
	ping.running = 1;
	g_ping = &ping;
	if (parse_args(argc, argv, &ping) < 0)
		return (1);
	if (resolve_hostname(&ping) < 0)
		return (1);
	if (create_socket(&ping) < 0)
		return (1);
	ping.id = getpid() & 0xFFFF;
	init_stats(&ping);
	setup_signals();
	print_ping_header(&ping);
	ping_loop(&ping);
	print_stats(&ping);
	close(ping.sockfd);
	return (0);
}
