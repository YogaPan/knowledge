#include <stdio.h>
#include "config.h"
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <fuck.h>

void say_fuck(void)
{
#ifdef HAVE_UNISTD_H
	sleep(3);
#endif
	printf("fuck\n");
}
