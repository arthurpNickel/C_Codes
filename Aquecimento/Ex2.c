#include <stdio.h>

int x, y;

int main () {
	scanf("%d", &x);
	while (x != 0)
	{
		scanf("%d", &y);
		if (y != x*x)
		{
			printf("%d\n", 0);
			return 1;
		}
		scanf("%d", &x);
	}
	printf("%d\n", 1);
	return 0;
}

