#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int PGCD_r (int a, int b) {
    if (a==b) {
        return a;
    } if (a >= b) {
        return PGCD_r(a-b, b);
    }
    return PGCD_r(a, b-a);
}

int PGCD_i (int a, int b) {
    while (a != b) {
        if (a>=b) {
            a -= b;
        } else {
            b -= a;
        }
    }
    return a;
}

int PGCD_m (int a, int b) {
    int r = a%b;
    while (r != 0) {
        a = b;
        b = r;
        r = a%b;
    }
    return b;
}

void time_pgcd(void) {
    clock_t debut = clock();

    for (int i = 0; i < 1000000; i++) {
        PGCD_m(10000, 37);
    }

    clock_t fin = clock();

    printf("Ticks : %ld\n", (long)(fin - debut));
    printf("Temps : %f s\n",
    (double)(fin - debut) / CLOCKS_PER_SEC);
}

void moyenne(void) {
    unsigned int it = 0;
    long int sum = 0;
    float arg;
    int nb;

    do {
        nb = rand() % 101;
        sum += nb;
        it++;
        arg = sum / (float)it;
    } while (fabs(arg - 50) > 0.0000000001);
    printf("it = %u -> arg = %.3f\n", it, arg);
}

void time_moyenne() {
    clock_t debut = clock();

    moyenne();

    clock_t fin = clock();

    printf("Ticks : %ld\n", (long)(fin - debut));
    printf("Temps : %f s\n",
    (double)(fin - debut) / CLOCKS_PER_SEC);
}

void afficheTab(int t[], int n) {
    printf("t=[");
    for (int i = 0; i < n; ++i)
        printf("%3d", t[i]);
    printf("]\n");
}

void initTab(int t[], int n) {
    for (int i = 0; i < n; ++i)
        t[i] = 0;
}

int genereAlea(int A, int B) {
    return A + rand() % (B - A + 1);
}

void remplitAlea(int t[], int n, int A, int B) {
    for (int i = 0; i < n; ++i)
        t[i] = genereAlea(A, B);
}

void time_randT() {
    clock_t debut = clock();
    
    int tab[100] = {0};

    afficheTab(tab, 100);
    remplitAlea(tab, 100, 0, 100);
    afficheTab(tab, 100);

    clock_t fin = clock();

    printf("Ticks : %ld\n", (long)(fin - debut));
    printf("Temps : %f s\n",
    (double)(fin - debut) / CLOCKS_PER_SEC);
}

int main(void) {
    time_pgcd();
    time_moyenne();
    time_randT();

    return 0;
}