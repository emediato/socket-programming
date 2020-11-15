#include <stdio.h>
#include <memory>

int main() {
    const int nrows = 3, ncols = 5;
    const int dx = 2, dy = 1;
    int a[nrows ][ncols] = { {1,  2,  3,  4, 5},
        {1,  2,  3,  4, 5},
        {1,  2,  3,  4, 5}
    };
    int tmp[nrows][ncols];
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            tmp[(i + dx) % nrows][(j + dy) % ncols] = a[i][j];
    memcpy(a, tmp, sizeof(tmp));
    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncols; j++)
            printf(j < ncols - 1 ? "%3d " : "%3d\n", a[i][j]);
}
