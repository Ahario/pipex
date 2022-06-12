#include "pipex.h"

void infile_error()
{
	perror("infile error in main function ");
}

void outfile_error()
{
	perror("outfile error in main function : ");
}

void command_error()
{
	perror("command not found COI");
}

void fork_error()
{
	perror("fork error in command_to_outfile : ");
}

void pipe_error()
{
	perror("pipe error in command_to_outfile : ");
}

void execve_error()
{
	perror("execve error in command_to_outfile ");
}

void command_to_outfile_error()
{
	perror("command not found in COO");
	exit(127);
}