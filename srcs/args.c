/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rstride <rstride@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 08:00:00 by rstride           #+#    #+#             */
/*   Updated: 2025/12/23 09:20:37 by rstride          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	print_help(void)
{
	printf("Usage: ft_ping [OPTION...] HOST\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");
	printf("Options:\n");
	printf("  -v\t\tverbose output\n");
	printf("  -?\t\tgive this help list\n");
}

static int	is_option(const char *arg)
{
	return (arg && arg[0] == '-' && arg[1] != '\0');
}

static int	parse_option(const char *arg, t_ping *ping)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'v')
			ping->verbose = 1;
		else if (arg[i] == '?')
		{
			print_help();
			exit(0);
		}
		else
		{
			fprintf(stderr, "ft_ping: invalid option -- '%c'\n", arg[i]);
			fprintf(stderr, "Try 'ft_ping -?' for more information.\n");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	parse_args(int argc, char **argv, t_ping *ping)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (is_option(argv[i]))
		{
			if (parse_option(argv[i], ping) < 0)
				return (-1);
		}
		else
		{
			if (ping->hostname != NULL)
			{
				fprintf(stderr, "ft_ping: too many hosts\n");
				return (-1);
			}
			ping->hostname = argv[i];
		}
		i++;
	}
	if (ping->hostname == NULL)
	{
		fprintf(stderr, "ft_ping: missing host operand\n");
		fprintf(stderr, "Try 'ft_ping -?' for more information.\n");
		return (-1);
	}
	return (0);
}
