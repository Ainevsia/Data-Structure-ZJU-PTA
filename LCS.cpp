#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;
char x[MAX];
char y[MAX];

int main(int argc, char const *argv[]) {
	freopen("test.txt", "r", stdin);
	cin >> x >> y;
	int m = strlen(x) - 1, n = strlen(y) - 1;
	int ** c = new int* [m+1];
	for (int i = 0; i <= m; ++i) c[i] = new int [n+1];
	for (int i = 0; i <= m; ++i) c[i][0] = 0;
	for (int j = 0; j <= n; ++j) c[0][j] = 0;
	for (int i = 1; i <= m; ++i)
	for (int j = 1; j <= n; ++j) {
		if (x[i] == y[j]) c[i][j] = c[i-1][j-1] + 1;
		else if (c[i-1][j] >= c[i][j-1]) c[i][j] = c[i-1][j];
		else c[i][j] = c[i][j-1];
	}
	cout << c[m][n];
	return 0;
}