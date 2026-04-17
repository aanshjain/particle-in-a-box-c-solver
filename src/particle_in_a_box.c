/*
 * ============================================================
 *  Particle in a Box — Quantum Mechanics Simulator
 *  Jaypee University of Information Technology, Waknaghat
 *  Department of CSE & IT
 *
 *  Authors : Akshat Tyagi    (241031016)
 *            Anshit Guleria  (241032004)
 *            Aansh Jain      (241030210)
 *            Toshit Kaul     (241030436)
 *            Saubhagya Sharma
 *
 *  Supervisor : Prof. Dr. P. B. Barman
 * ============================================================
 *
 *  Solves the time-independent Schrodinger equation for an
 *  infinite 1-D square well and outputs:
 *    - Discrete energy levels  E_n  (Joules and eV)
 *    - Wavefunction values     psi_n(x)
 *    - Probability densities   |psi_n(x)|^2
 *
 *  Build :  gcc particle_in_a_box.c -o particle_in_a_box -lm
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/* ── Physical constants (SI) ──────────────────────────────── */
#define PLANCK   6.62607015e-34   /* Planck constant  [J·s]  */
#define HBAR     1.05457182e-34   /* ℏ = h / 2π       [J·s]  */
#define MASS     9.10938356e-31   /* Electron mass    [kg]   */
#define PI       3.14159265358979323846
#define J_TO_EV  6.24150907e18    /* 1 J in eV               */

/* ── Defaults (used when running in non-interactive mode) ─── */
#define DEFAULT_L      1.0e-9     /* 1 nm box               */
#define DEFAULT_MAX_N  5
#define DEFAULT_STEPS  11


/* ── Core physics functions ──────────────────────────────── */

/*
 * Energy of the nth level for an infinite square well:
 *   E_n = n^2 * pi^2 * hbar^2 / (2 * m * L^2)
 */
double energy_level(int n, double L)
{
    return ((double)n * n * PI * PI * HBAR * HBAR)
           / (2.0 * MASS * L * L);
}

/*
 * Normalised wavefunction:
 *   psi_n(x) = sqrt(2/L) * sin(n * pi * x / L)
 */
double wavefunction(int n, double x, double L)
{
    return sqrt(2.0 / L) * sin((double)n * PI * x / L);
}

/*
 * Probability density:
 *   rho_n(x) = |psi_n(x)|^2
 */
double probability_density(int n, double x, double L)
{
    double psi = wavefunction(n, x, L);
    return psi * psi;
}


/* ── Output helpers ──────────────────────────────────────── */

void print_separator(char c, int width)
{
    int i;
    for (i = 0; i < width; i++) putchar(c);
    putchar('\n');
}

void print_energy_table(int max_n, double L)
{
    int n;
    print_separator('=', 60);
    printf("  ENERGY LEVELS  (box length L = %.4e m)\n", L);
    print_separator('=', 60);
    printf("  %-6s  %-20s  %-20s\n", "n", "Energy (J)", "Energy (eV)");
    print_separator('-', 60);
    for (n = 1; n <= max_n; n++) {
        double E   = energy_level(n, L);
        double eV  = E * J_TO_EV;
        printf("  %-6d  %-20.6e  %-20.6e\n", n, E, eV);
    }
    print_separator('=', 60);
}

void print_wavefunction_table(int max_n, double L, int steps)
{
    int n, i;
    double dx = (steps > 1) ? L / (steps - 1) : 0.0;

    printf("\n");
    print_separator('=', 72);
    printf("  WAVEFUNCTION  &  PROBABILITY DENSITY\n");
    print_separator('=', 72);

    for (n = 1; n <= max_n; n++) {
        printf("\n  Quantum number n = %d\n", n);
        print_separator('-', 72);
        printf("  %-14s  %-22s  %-22s\n",
               "x (m)", "psi_n(x)", "|psi_n(x)|^2 (m^-1)");
        print_separator('-', 72);

        for (i = 0; i < steps; i++) {
            double x   = i * dx;
            double psi = wavefunction(n, x, L);
            double rho = psi * psi;
            printf("  %-14.6e  %-22.8e  %-22.8e\n", x, psi, rho);
        }
    }
    print_separator('=', 72);
}


/* ── Unit conversion helper ──────────────────────────────── */

double apply_unit(double value, char unit)
{
    switch (unit) {
        case 'u': case 'U': return value * 1.0e-6;   /* micrometres */
        case 'n': case 'N': return value * 1.0e-9;   /* nanometres  */
        case 'm': case 'M': return value;             /* metres      */
        default:
            fprintf(stderr, "  [!] Unknown unit '%c'. Assuming metres.\n", unit);
            return value;
    }
}


/* ── Main ─────────────────────────────────────────────────── */

int main(int argc, char *argv[])
{
    double L;
    int    max_n, steps;
    char   unit;

    /* ── Banner ── */
    printf("\n");
    print_separator('*', 60);
    printf("  Quantum Particle-in-a-Box Simulator  |  C Edition\n");
    printf("  JUIT Waknaghat  —  Dept. of CSE & IT\n");
    print_separator('*', 60);
    printf("\n");

    /* ── Non-interactive mode: run with defaults ── */
    if (argc > 1 && strcmp(argv[1], "--demo") == 0) {
        L     = DEFAULT_L;
        max_n = DEFAULT_MAX_N;
        steps = DEFAULT_STEPS;
        printf("  [Demo mode]  L = 1 nm,  n_max = %d,  steps = %d\n\n",
               max_n, steps);
    } else {
        /* ── Interactive input ── */
        printf("  Box length (value + unit: e.g.  1 n  for 1 nm,\n");
        printf("              1 u = 1 µm,  1e-9 m = 1 nm)\n");
        printf("  Enter length and unit: ");
        if (scanf("%lf %c", &L, &unit) != 2) {
            fprintf(stderr, "  [!] Invalid input. Exiting.\n");
            return EXIT_FAILURE;
        }
        L = apply_unit(L, unit);

        printf("  Maximum quantum number n_max: ");
        if (scanf("%d", &max_n) != 1 || max_n < 1) {
            fprintf(stderr, "  [!] n_max must be >= 1. Exiting.\n");
            return EXIT_FAILURE;
        }

        printf("  Number of position steps for wavefunction: ");
        if (scanf("%d", &steps) != 1 || steps < 2) {
            fprintf(stderr, "  [!] Steps must be >= 2. Exiting.\n");
            return EXIT_FAILURE;
        }
    }

    /* ── Compute and display ── */
    print_energy_table(max_n, L);
    print_wavefunction_table(max_n, L, steps);

    printf("\n  Done. Goodbye!\n\n");
    return EXIT_SUCCESS;
}
