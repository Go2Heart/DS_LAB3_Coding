#include <bits/stdc++.h>
using namespace std;

int main()
{
	srand(time(0));
	int n = rand() % 10 + 200;
	for(int i = 1; i <= n; i++)
		putchar(rand() % 95 + 32);
}