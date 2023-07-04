#include <X11/X.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <X11/Xlib.h>
#include "dsde_config.h"
#include "dswm.h"

#define IS_OPTARG(_a, _s, _l) \
			strcmp("-" _s, _a) == 0 \
        	|| strcmp("--" _l, _a) == 0

#define IS_OPTARG_LONG(_a, _l) \
  			strcmp("--" _l, _a) == 0

#define IS_NOT_OPTARG(_a) _a[0] != '-'

#define OPTARG_HELP(_s, _l, _h) printf("\t-" _s ", --" _l "\t" _h "\n")

#define OPTARG_LONG_HELP(_l, _h) printf("\t--" _l "\t" _h "\n")

#define OPTARG_HELP_VAL(_s, _l, _v, _h) printf("\t-" _s ", --" _l " " _v "\t" \
												_h "\n")

char const *prg_name;
int opt_colorize = 1;
static char const *opt_disp = NULL;

static void
show_usage(int retval)
{
	printf("Usage: %s [OPTION]...\n", prg_name);

	OPTARG_HELP_VAL("d", "display", "<display>", "specify the display to use");
	OPTARG_LONG_HELP("no-color", "turn off colored output.");
	OPTARG_HELP("h", "help", "display this help and exit.");
	OPTARG_LONG_HELP("version", "output version information and exit.");

	exit(retval);
}

static void
show_version(void)
{
	printf("%s v" VERSION "\n", prg_name);
	printf("Copyright (C) 2023 d0p1\n");
	printf("License BSD-3-Clause: <https://directory.fsf.org/wiki/License:BSD-3-Clause>\n");
	printf("This is free software: you are free to change and redistribute it.\n");
	printf("There is NO WARRANTY, to the extent permitted by law.\n");
	exit(EXIT_SUCCESS);
}

static void
parse_cli(int argc, char **argv)
{
	int idx;

	for (idx = 0; idx < argc; idx++)
	{
		if (IS_OPTARG_LONG(argv[idx], "version"))
		{
			show_version();
		}
		else if (IS_OPTARG(argv[idx], "h", "help"))
		{
			show_usage(EXIT_SUCCESS);
		}
		else if (IS_OPTARG(argv[idx], "d", "display"))
		{
			idx++;
			if (idx >= argc)
			{
				show_usage(EXIT_FAILURE);
			}
			else
			{
				opt_disp = argv[idx];
			}
		}
		else if (IS_OPTARG_LONG(argv[idx], "no-color"))
		{
			opt_colorize = 0;
		}
		else
		{
			show_usage(EXIT_FAILURE);
		}
	}
}

int
main(int argc, char **argv)
{
	char *no_color;

	no_color = getenv("NO_COLOR");
	if (no_color != NULL && no_color[0] != '\0')
	{
		opt_colorize = 0;
	}

	prg_name = basename(argv[0]);
	parse_cli(argc - 1, argv + 1);
	
	wm_initalize(opt_disp);

	wm_run();

	wm_destroy();

	return (EXIT_SUCCESS);
}
