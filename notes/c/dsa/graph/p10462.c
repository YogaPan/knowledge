#include <stdio.h>
#include <stdlib.h>

/* Max edges numbers. */
#define MAX_EDGES 200
/* This define infinity, means no way get to there. */
#define INF 0x3f3f3f3f

/* Compare a and b, return which one is bigger. */
#define max(a, b) ({					\
	__typeof__(a) _a = (a);				\
	__typeof__(b) _b = (b);				\
	_a > _b ? _a : _b;                  \
})

/* Compare a and b, return which one is smaller. */
#define min(a, b) ({					\
	__typeof__(a) _a = (a);				\
	__typeof__(b) _b = (b);				\
	_a < _b ? _a : _b;					\
})

/* Define edge structure. x and y is the vertices.
 * weight is the "distance" between two vertices. */
struct edge {
	int x;
	int y;
	int weight;
};

/* This compare function used by "qsort" and sort edges
 * according to edges weight. */
static inline int edge_weight_compare(const void *xp, const void *yp)
{
	struct edge *x = (struct edge *)xp;
	struct edge *y = (struct edge *)yp;

	return x->weight > y->weight ? 1 : -1;
}

/* Recursive find the root of this set. */
static inline int find_set_root(int *sets, int x)
{
	if (sets[x] != x)
		sets[x] = find_set_root(sets, sets[x]);
	return sets[x];
}

/* Initialize sets. Each vertice is set after intialize. */
static inline void init_sets(int *sets, int vertices_number)
{
	int i;

	for (i = 0; i <= vertices_number; i++)
		sets[i] = i;
}

/* Find the minimum spanning tree and return the cost of the tree. */
int kruskal(struct edge *edges, int edges_number, int vertices_number, int *path)
{
	int i, j, cost = 0;
	int ans = 0;
	int sets[MAX_EDGES];

	init_sets(sets, vertices_number);

	for (i = 0, j = 1; i < edges_number; i++) {
		int root_x = find_set_root(sets, edges[i].x);
		int root_y = find_set_root(sets, edges[i].y);

		/* Combine two sets and set path. */
		if (root_x != root_y) {
			cost += edges[i].weight;
			path[j++] = i;
			sets[root_x] = root_y;
		}
	}

	/* Check is there have two root of set? */
	for (i = 1; i <= vertices_number; i++) {
		if (sets[i] == i)
			ans++;
	}

	/* INF means no way to reach. */
	return ans == 1 ? cost : INF;
}

/* Find the second minimum spanning tree. */
int smst(struct edge *edges, int edges_number,
		 int vertices_number, int *path, int x)
{
	int i, cost = 0;
	int ans = 0;
	int sets[MAX_EDGES];

	init_sets(sets, vertices_number);

	for (i = 0; i < edges_number; i++) {
		int root_x = find_set_root(sets, edges[i].x);
		int root_y = find_set_root(sets, edges[i].y);

		/* Combine two sets. */
		if (root_x != root_y && i != x) {
			cost += edges[i].weight;
			sets[root_x] = root_y;
		}
	}

	/* Check is there have two root of set? */
	for (i = 1; i <= vertices_number; i++) {
		if (sets[i] == i)
			ans++;
	}

	/* INF means no way to reach. */
	return ans == 1 ? cost : INF;
}

int main(void)
{
	int i, count = 0;
	int case_number;
	int edges_number, vertices_number;

	int path[MAX_EDGES];
	struct edge edges[MAX_EDGES];

	/* How many case will be calculate. */
	scanf("%d", &case_number);
	while (case_number--) {
		/* How many edges and vertices. */
		scanf("%d %d", &vertices_number, &edges_number);

		/* for each edges. */
		for (i = 0; i < edges_number; i++) {
			/* Get edges start, end and weight. */
			scanf("%d %d %d",
				  &edges[i].x,
				  &edges[i].y,
				  &edges[i].weight);
		}
		/* Sort edges by weight. */
		if (edges_number > 0) {
			qsort(edges, edges_number - 1, sizeof(struct edge),
				  edge_weight_compare);
		}

		int first_way_cost, second_way_cost;

		/* Initialize first_way_cost and second_way_cost to INF. */
		first_way_cost = second_way_cost = INF;

		/* Get spanning tree cost and modify path. */
		first_way_cost = kruskal(edges, edges_number, vertices_number, path);

		/* Path number is vertices_number - 1 */
		for (i = 1; i < vertices_number; i++) {
			int temp = smst(edges, edges_number,
							vertices_number, path, path[i]);
			second_way_cost = min(second_way_cost, temp);
		}

		/* Only one way, multiple way, or no way. */
		if (first_way_cost == INF)
			printf("Case #%d : No way\n", ++count);
		else if (second_way_cost == INF)
			printf("Case #%d : No second way\n", ++count);
		else
			printf("Case #%d : %d\n", ++count, second_way_cost);
	}

	return 0;
}
