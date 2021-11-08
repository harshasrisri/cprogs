#include <stdio.h>
#include <stdbool.h>

typedef struct rectangle {
	int left;
	int bottom;
	int right;
	int top;
} Rect;

typedef struct point {
	int x;
	int y;
} Point;

int areaOf (Rect r) {
	int area = (r.left - r.right) * (r.top - r.bottom);
	if (area < 0) area = -1 * area;
	return area;
}

bool theyIntersect (Rect a, Rect b) {
	if (a.left > b.right) return false;
   	if (a.right < b.left) return false;
	if (a.top < b.bottom) return false;
	if (a.bottom > b.top) return false;
	return true;
}

Rect intersectionOf (Rect a, Rect b) {
	Rect c;

	if (a.left >= b.left) c.left = a.left; else c.left = b.left;
	if (a.right <= b.right) c.right = a.right; else c.right = b.right;
	if (a.bottom >= b.bottom) c.bottom = a.bottom; else c.bottom = b.bottom;
	if (a.top <= b.top) c.top = a.top; else c.top = b.top;

	return c;
}

int computeArea (int A, int B, int C, int D, int E, int F, int G, int H) {
	Rect a, b, c;

	a = (Rect) {.left = A, .bottom = B, .right = C, .top = D};
	b = (Rect) {.left = E, .bottom = F, .right = G, .top = H};
	c = (Rect) {.left = 0, .bottom = 0, .right = 0, .top = 0};

	if (theyIntersect (a, b)) 
		c = intersectionOf (a, b);

	return areaOf(a) + areaOf(b) - areaOf(c);
}

int main () {
	int i, j, test[][8] = {
		{0,0,1,1,1,1,2,2},
		{-2,-2,2,2,-2,-2,2,2},
		{-2,-2,2,2,-3,-3,3,1},
		{-2,-2,2,2,3,3,4,4},
		{-2, -2, 2, 2, -3, -3, 3, -1},
	};

	for (i = 0; i < sizeof(test) / (8*sizeof(int)); i++) {
		printf ("Test %d : ", i);
		for (j = 0; j < 8; j++)
			printf ("%3d ", test[i][j]);
		printf (": %3d\n", computeArea ( test[i][0], test[i][1], test[i][2], test[i][3], test[i][4], test[i][5], test[i][6], test[i][7]));
	}
	return 0;
}
