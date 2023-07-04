#include <stdlib.h>
#include <dtk.h>

int
main(int argc, char **argv)
{
	DtkApplication *app;

	app = dtk_application_new(argc, argv);
	if (app == NULL)
	{
		return (EXIT_FAILURE);
	}

	dtk_application_run(app);

	dtk_application_destroy(app);

	return (EXIT_SUCCESS);
}
