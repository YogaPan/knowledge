#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "progress.h"
#include "str.h"

struct progress *progress_init(const char *mission, int total, struct progress_bar *custom_bar)
{
	struct progress *p;

	p = malloc(sizeof(p));
	if (!p)
		return NULL;
	p->total = total;
	p->completed = 0;
	snprintf(p->mission, 64, "%s", mission);
	p->start = clock();
	if (custom_bar) {
		p->bar = *custom_bar;
	} else {
		p->bar = (struct progress_bar) {
			.completed = '#',
			.uncompleted = ' ',
			.head = '>'
		};
	}

	return p;
}

void progress_destroy(struct progress *p)
{
	if (p != NULL)
		free(p);
}

void progress_tick(struct progress *p, int len)
{
	p->completed += len;
	if (p->completed >= p->total) {
		p->completed = p->total;
		p->bar.head = p->bar.completed;
		progress_print(p);
		printf(", done\n");
		return;
	}
	progress_print(p);
	printf("\r");
}

void progress_print(struct progress *p)
{
	char bar[60];
	char *tmp;
	char time_string[64];
	int percent;
	int completed_length;
	int uncompleted_length;
	int total_length = 50;
	clock_t run_time;

	percent = p->completed * 100 / p->total;
	if (percent > 100)
		percent = 100;

	completed_length = percent / 2;
	uncompleted_length = total_length - completed_length;

	tmp = bar;
	*tmp++ = '[';
	tmp = memset(tmp, p->bar.completed, completed_length) + completed_length;
	*tmp++ = p->bar.head;
	tmp = memset(tmp, p->bar.uncompleted, uncompleted_length) + uncompleted_length;
	*tmp++ = ']';
	*tmp = '\0';

	run_time = (clock() - p->start) / CLOCKS_PER_SEC;
	format_time(time_string, run_time);

	printf("%-10s %60s %d%% (%d/%d), %s", p->mission, bar, percent, p->completed, p->total, time_string);
	fflush(stdout);
}

void format_time(char *time_string, int second)
{
	int minute, hour;

	minute = second / 60; second = second % 60;
	hour = minute / 60; minute = minute % 60;

	snprintf(time_string, 64, "%d:%02d:%02d", hour, minute, second);
}

void waste_time(void)
{
	int i; for(i = 0; i < 1000000000; i++);
}
