#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

static char	*join_cmd(char *infile, char *outfile)
{
	char	*cmd;
	size_t	len_infile;
	size_t	len_outfile;

	len_infile = strlen(infile);
	len_outfile = strlen(outfile);
	cmd = malloc((len_infile + len_outfile + 53) * sizeof(char));
	if (!cmd)
		return (NULL);
	cmd[len_infile + len_outfile] = '\0';
	memcpy(cmd, "echo 0$(< ", 10);
	memcpy(&cmd[10], infile, len_infile);
	memcpy(&cmd[len_infile + 10], " jq -c | zlib-flate -compress | base64) > ", 42);
	memcpy(&cmd[len_infile + 52], outfile, len_outfile);
	return (cmd);
}

static char	file_to_blueprint(char *infile, char *outfile)
{
	char	*command;
	int	res;

	if (access(infile, R_OK))
	{
		printf("access : cannot read the infile : restricted rights\n");
		return (1);
	}
	if (!access(outfile, F_OK) && access(outfile, W_OK))
	{
		printf("access : cannot write in the outfile : restricted rights\n");
		return (1);
	}
	command = join_cmd(infile, outfile);
	if (!command)
	{
		printf("malloc : memory allocation failed\n");
		return (1);
	}
	res = system(command);
	free(command);
	if (res)
	{
		printf("system : execution failed\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Exactly 2 arguments are required : the input file and the output file, respectively\n");
		exit(1);
	}
	if (file_to_blueprint(argv[1], argv[2]))
		exit(1);
	exit(0);
}
