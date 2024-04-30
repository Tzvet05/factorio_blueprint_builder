// Factorio blueprint builder - source code

#include "blueprint_builder.h"

inline static int	*build_command(char *infile, char *outfile)
{
	char	*command;
	size_t	i;
	size_t	len_infile;
	size_t	len_outfile;

	len_infile = strlen(infile);
	len_outfile = strlen(outfile);
	command = malloc((len_infile + len_outfile + 53) * sizeof(char));
	if (!command)
		return (NULL);
	command[len_infile + len_outfile] = '\0';
	strcpy(command, "echo 0$(< ");
	strcpy(&command[10], infile);
	i = 10 + len_infile;
	strcpy(&command[i], " jq -c | zlib-flate -compress | base64) > ");
	i += 42;
	strcpy(&command[i], outfile);
	return (command);
}

inline static int	check_files(char *infile, char *outfile)
{
	struct stat	path;

	stat(infile, &path);
	if (S_ISREG(path.st_mode) == 0)
	{
		puterr(ERRORSTRING_NOT_FILE, infile);
		return (ERRORCODE_NOT_FILE);
	}
	stat(outfile, &path);
	if (S_ISREG(path.st_mode) == 0)
	{
		puterr(ERRORSTRING_NOT_FILE, outfile);
		return (ERRORCODE_NOT_FILE);
	}
	return (0);
}

inline static int	check_args(char *infile, char *outfile)
{
	size_t	len;
	int		error;

	error = check_files(infile, outfile);
	if (error != 0)
		return (error);
	if (access(infile, F_OK) == -1)
	{
		puterr(ERRORSTRING_INFILE_NONEXISTANT, infile);
		return (ERRORCODE_INFILE_NONEXISTANT);
	}
	if (access(infile, R_OK) == -1)
	{
		puterr(ERRORSTRING_FILE_READ_RIGHTS, infile);
		return (ERRORCODE_FILE_READ_RIGHTS);
	}
	if (access(outfile, F_OK) == 0 && access(outfile, W_OK) == -1)
	{
		puterr(ERRORSTRING_FILE_WRITE_RIGHTS, outfile);
		return (ERRORCODE_FILE_WRITE_RIGHTS);
	}
	len = strlen(infile);
	if (len < 5 || strcmp(&infile[len - 5], ".json") != 0)
		puterr(WARNING_FILE_FORMAT, infile);
	return (0);
}

int	file_to_blueprint(char *infile, char *outfile)
{
	char	*command;
	int		error;

	error = (int)check_args(infile, outfile);
	if (error != 0)
		return ((char)error);
	command = build_command(infile, outfile);
	if (command == NULL)
	{
		puterr(ERRORSTRING_MALLOC, NULL);
		return (ERRORCODE_MALLOC);
	}
	error = system(command);
	if (error != 0)
	{
		puterr(ERRORSTRING_SYSTEM, command);
		free(command);
		return (ERRORCODE_SYSTEM);
	}
	free(command);
	return (0);
}
