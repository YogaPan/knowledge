#include <sys/types.h>

#ifndef progress_h
#define progress_h

struct progress_bar {
	char completed;
	char head;
	char uncompleted;
};

struct progress {
	char mission[64];
	int total;
	int completed;
	clock_t start;
	struct progress_bar bar;
};

struct progress *progress_init(const char *mission, int total, struct progress_bar *custom_bar);
void progress_tick(struct progress *p, int len);
void progress_destroy(struct progress *p);
void progress_print(struct progress *p);

void waste_time(void);
void format_time(char *time_string, int second);

#endif
