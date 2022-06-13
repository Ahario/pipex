/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeo <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 12:58:05 by hyeo              #+#    #+#             */
/*   Updated: 2022/06/13 12:58:07 by hyeo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void infile_error(void)
{
	perror("infile error in main function ");
}

void outfile_error(void)
{
	perror("outfile error in main function : ");
}

void command_error(void)
{
	perror("command not found COI");
}

void fork_error(void)
{
	perror("fork error in command_to_outfile : ");
}

void pipe_error(void)
{
	perror("pipe error in command_to_outfile : ");
}

void execve_error(void)
{
	perror("execve error in command_to_outfile ");
}

void command_to_outfile_error(void)
{
	perror("command not found in COO");
	exit(127);
}

void file_number_error(void)
{
	perror("you must have 4 inputs");
}
