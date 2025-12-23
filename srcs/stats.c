/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:14 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	init_stats(t_ping *ping)
{
	ping->rtt_min = 0.0;
	ping->rtt_max = 0.0;
	ping->rtt_sum = 0.0;
	ping->rtt_sum_sq = 0.0;
}

void	update_stats(t_ping *ping, double rtt)
{
	if (ping->packets_recv == 1 || rtt < ping->rtt_min)
		ping->rtt_min = rtt;
	if (rtt > ping->rtt_max)
		ping->rtt_max = rtt;
	ping->rtt_sum += rtt;
	ping->rtt_sum_sq += rtt * rtt;
}

void	print_stats(t_ping *ping)
{
	double	loss_pct;
	double	avg;
	double	stddev;
	double	variance;

	printf("--- %s ping statistics ---\n", ping->hostname);
	if (ping->packets_sent > 0)
		loss_pct = 100.0 * (ping->packets_sent - ping->packets_recv)
			/ ping->packets_sent;
	else
		loss_pct = 0.0;
	printf("%d packets transmitted, %d packets received, %.0f%% packet loss\n",
		ping->packets_sent, ping->packets_recv, loss_pct);
	if (ping->packets_recv > 0)
	{
		avg = ping->rtt_sum / ping->packets_recv;
		variance = (ping->rtt_sum_sq / ping->packets_recv) - (avg * avg);
		if (variance < 0)
			variance = 0;
		stddev = sqrt(variance);
		printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
			ping->rtt_min, avg, ping->rtt_max, stddev);
	}
}
