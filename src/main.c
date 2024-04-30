// Factorio blueprint builder - source code

#include "blueprint_builder.h"

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		puterr(ERRORSTRING_AMOUNT_ARGS, NULL);
		exit(ERRORCODE_AMOUNT_ARGS);
	}
	exit(file_to_blueprint(argv[1], argv[2]));
}
