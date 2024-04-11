#include "blueprint_builder.h"

int	main(int argc, char **argv)
{
	char	error;

	if (argc != 3)
	{
		puterr(ERRORSTRING_AMOUNT_ARGS, NULL);
		exit(ERRORCODE_AMOUNT_ARGS);
	}
	error = file_to_blueprint(argv[1], argv[2]);
	if (error != 0)
		exit(error);
	exit(0);
}
