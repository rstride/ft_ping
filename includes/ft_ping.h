/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <math.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <arpa/inet.h>
# include <netdb.h>

/* Constants */
# define PACKET_SIZE		64
# define PAYLOAD_SIZE		56
# define DEFAULT_TTL		64
# define RECV_TIMEOUT		1
# define PING_INTERVAL		1000000

/* ICMP Types */
# define ICMP_ECHO_REPLY	0
# define ICMP_ECHO_REQUEST	8

/* Ping session structure */
typedef struct s_ping
{
	int					sockfd;
	int					verbose;
	char				*hostname;
	char				*ip_str;
	struct sockaddr_in	dest_addr;
	uint16_t			seq;
	uint16_t			id;
	int					packets_sent;
	int					packets_recv;
	double				rtt_min;
	double				rtt_max;
	double				rtt_sum;
	double				rtt_sum_sq;
	int					running;
}	t_ping;

/* Global for signal handling */
extern t_ping	*g_ping;

/* args.c - Argument parsing */
int		parse_args(int argc, char **argv, t_ping *ping);
void	print_help(void);

/* resolve.c - DNS resolution */
int		resolve_hostname(t_ping *ping);

/* socket.c - Socket operations */
int		create_socket(t_ping *ping);

/* icmp.c - ICMP packet handling */
void	build_icmp_packet(char *packet, uint16_t seq, uint16_t id);

/* checksum.c - Internet checksum */
uint16_t	calculate_checksum(void *data, int len);

/* ping.c - Send/receive */
int		send_ping(t_ping *ping);
int		receive_ping(t_ping *ping);

/* display.c - Output formatting */
void	print_ping_header(t_ping *ping);
void	print_ping_reply(t_ping *ping, int bytes, struct iphdr *ip,
			struct icmphdr *icmp, double rtt);
void	print_verbose_error(t_ping *ping, struct iphdr *ip,
			struct icmphdr *icmp);

/* stats.c - Statistics */
void	init_stats(t_ping *ping);
void	update_stats(t_ping *ping, double rtt);
void	print_stats(t_ping *ping);

/* error.c - Error handling */
void	error_exit(const char *msg);
void	error_msg(const char *msg);

#endif
