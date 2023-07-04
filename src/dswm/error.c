#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "dswm.h"

static void
error_type(Error err)
{
	if (opt_colorize)
	{
		fprintf(stderr, "\033[1;31m");
	}

	switch (err)
	{
		case ERROR_FATAL:
			fprintf(stderr, "fatal error: ");
			break;
		
		case ERROR_ERROR:
			fprintf(stderr, "error: ");
			break;

		default:
			fprintf(stderr, "???: ");
			break;
	}

	if (opt_colorize)
	{
		fprintf(stderr, "\033[0m");
	}
}

void
error(Error err, char const *fmt, ...)
{
	va_list args;

	va_start(args, fmt);
	fprintf(stderr, "%s: ", prg_name);
	error_type(err);
	vfprintf(stderr, fmt, args);
	fprintf(stderr, "\n");
	va_end(args);

	if (err == ERROR_FATAL)
	{
		exit(EXIT_FAILURE);
	}
}
