#include <stdio.h>
#include <stdint.h>
#include <time.h>

uint64_t fib_fast_doubling(uint64_t n) {
    if (n == 0) return 0;
    uint64_t a = 0, b = 1;
    for (int i = 63; i >= 0; i--) {
        uint64_t t = a * ((b << 1) - a);
        uint64_t u = a * a + b * b;
        if ((n >> i) & 1) {
            a = u;
            b = t + u;
        } else {
            a = t;
            b = u;
        }
    }
    return a;
}

int main() {
    clock_t start = clock();
    uint64_t n = 0, f = 0;
    double ttime = 60.0; // Run for ttime second

    while ((double)(clock() - start) / CLOCKS_PER_SEC < ttime) {
        f = fib_fast_doubling(n);
        n++;
    }

    double elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
    printf("Reached F(%llu) in %f second\n", (unsigned long long)(n-1), elapsed);
    printf("F(%llu) = %llu\n", (unsigned long long)(n-1), (unsigned long long)f);

    return 0;
}
