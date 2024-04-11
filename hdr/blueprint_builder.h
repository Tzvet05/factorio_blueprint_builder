#ifndef BLUEPRINT_BUILDER_H
# define BLUEPRINT_BUILDER_H

/* ----- INCLUDES ----- */

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/stat.h>

/* ----- MACROS ----- */

// Generic macros
# define EXECUTABLE_NAME		"blueprint_builder"

// Warning string for puterr()
# define WARNING_FILE_FORMAT		"warning : infile is not in '.json' format"

// Error codes for exit()
# define ERRORSTRING_AMOUNT_ARGS	"error : exactly 2 arguments are required : \
the infile and the outfile respectively"
# define ERRORSTRING_MALLOC		"error : malloc() : failed memory allocation"
# define ERRORSTRING_SYSTEM		"error : system() : failed to run command"
# define ERRORSTRING_NOT_FILE		"error : is not a regular file"
# define ERRORSTRING_INFILE_NONEXISTANT	"error : access() : no such file"
# define ERRORSTRING_FILE_READ_RIGHTS	"error : access() : \
reading permission denied"
# define ERRORSTRING_FILE_WRITE_RIGHTS	"error : access() : \
writing permission denied"

// Error strings for puterr()
# define ERRORCODE_AMOUNT_ARGS		1
# define ERRORCODE_MALLOC		2
# define ERRORCODE_SYSTEM		3
# define ERRORCODE_NOT_FILE		4
# define ERRORCODE_INFILE_NONEXISTANT	5
# define ERRORCODE_FILE_READ_RIGHTS	6
# define ERRORCODE_FILE_WRITE_RIGHTS	7

/* ----- PROTOTYPES ----- */

// main.c
int		main(int argc, char **argv);

// convert.c
char	file_to_blueprint(char *infile, char *outfile);

// utils.c
void	puterr(char *str1, char *str2);

#endif
