# ⚛️ Quantum Particle-in-a-Box Simulator

> A C implementation of the **infinite 1-D square well** from quantum mechanics — computes energy levels, wavefunctions, and probability densities for an electron confined in a nanoscale box.

---

## 📋 Table of Contents

- [Project Overview](#project-overview)
- [Physics Background](#physics-background)
- [Features](#features)
- [Project Structure](#project-structure)
- [How to Compile & Run](#how-to-compile--run)
- [Sample Output](#sample-output)
- [Learning Outcomes](#learning-outcomes)
- [Future Improvements](#future-improvements)
- [Authors](#authors)
- [References](#references)

---

## Project Overview

This project simulates a quantum particle (electron) trapped inside a **one-dimensional infinite potential well** — one of the foundational models in quantum mechanics. By numerically solving the time-independent Schrödinger equation in C, the program makes abstract quantum concepts concrete and computable.

The simulator accepts user-defined box sizes (in metres, nanometres, or micrometres) and quantum levels, then outputs:

- Discrete **energy eigenvalues** in both Joules and electron-volts
- **Wavefunction** values `ψₙ(x)` sampled across the box
- **Probability densities** `|ψₙ(x)|²` showing where the particle is most likely to be found

Developed as an academic project at **Jaypee University of Information Technology, Waknaghat**, under the supervision of **Prof. Dr. P. B. Barman**.

---

## Physics Background

### The Model

An infinite square well confines a particle between `x = 0` and `x = L`. The potential is zero inside and infinite at the walls, so the particle can never escape — and its allowed states are quantised.

### Energy Eigenvalues

```
Eₙ = (n² · π² · ℏ²) / (2 · m · L²)
```

| Symbol | Meaning | Value |
|--------|---------|-------|
| `n`    | Principal quantum number | 1, 2, 3, … |
| `ℏ`    | Reduced Planck constant | 1.05457 × 10⁻³⁴ J·s |
| `m`    | Electron mass | 9.10938 × 10⁻³¹ kg |
| `L`    | Box length | User-defined (e.g. 1 nm) |

Energy scales as `n²` — so the second level is 4× the ground state, the third is 9×, and so on. This is the signature of **quantisation**.

### Normalised Wavefunction

```
ψₙ(x) = √(2/L) · sin(n·π·x / L)
```

The wavefunction is a standing wave with `n` half-wavelengths fitting inside the box. The normalisation factor `√(2/L)` ensures the total probability integrates to 1 over `[0, L]`.

### Probability Density

```
ρₙ(x) = |ψₙ(x)|² = (2/L) · sin²(n·π·x / L)
```

This tells you the *likelihood* of finding the particle near position `x`. The ground state (`n = 1`) peaks at the centre; higher states develop multiple lobes separated by nodes where `ρ = 0`.

---

## Features

- **Interactive input** — enter box length with unit (`u` / `n` / `m`), max quantum number, and position-step count
- **Demo mode** — run with `--demo` flag for instant output with default parameters (L = 1 nm, n_max = 5)
- **Dual energy units** — results shown in both Joules and eV for easy comparison with textbook values
- **Full wavefunction table** — ψₙ(x) and |ψₙ(x)|² at evenly-spaced positions across the well
- **Input validation** — graceful error messages for invalid units or out-of-range parameters
- **Clean formatted output** — aligned columns and section separators for readable terminal output
- **Portable C89/C99** — compiles on GCC, Clang, MSVC with a single flag (`-lm`)

---

## Project Structure

```
particle-in-a-box/
├── src/
│   └── particle_in_a_box.c    # Core source — physics functions + main
├── samples/
│   └── sample-output.txt      # Pre-generated demo run (L=1nm, n=1..5)
├── docs/
│   └── project-report.pdf     # Full project report (JUIT submission)
├── README.md                  # This file
└── .gitignore
```

---

## How to Compile & Run

### Prerequisites

- A C compiler: `gcc` (Linux/macOS) or MinGW/MSVC (Windows)
- The math library (`-lm` flag on Linux/macOS)

### Compile

```bash
gcc src/particle_in_a_box.c -o particle_in_a_box -lm
```

### Run — Interactive Mode

```bash
./particle_in_a_box
```

You will be prompted for:

```
Enter length and unit: 1 n          # 1 nanometre
Maximum quantum number n_max: 3
Number of position steps: 11
```

Accepted units: `n` (nanometres), `u` (micrometres), `m` (metres).

### Run — Demo Mode

```bash
./particle_in_a_box --demo
```

Runs silently with `L = 1 nm`, `n_max = 5`, `steps = 11` and prints the full output. Useful for CI/testing or quick inspection.

### Windows (MinGW)

```cmd
gcc src\particle_in_a_box.c -o particle_in_a_box.exe -lm
particle_in_a_box.exe --demo
```

---

## Sample Output

```
************************************************************
  Quantum Particle-in-a-Box Simulator  |  C Edition
  JUIT Waknaghat  —  Dept. of CSE & IT
************************************************************

  [Demo mode]  L = 1 nm,  n_max = 5,  steps = 11

============================================================
  ENERGY LEVELS  (box length L = 1.0000e-09 m)
============================================================
  n       Energy (J)            Energy (eV)
------------------------------------------------------------
  1       6.024668e-20          3.760302e-01
  2       2.409867e-19          1.504121e+00
  3       5.422201e-19          3.384272e+00
  4       9.639468e-19          6.016483e+00
  5       1.506167e-18          9.400754e+00
============================================================

  Quantum number n = 1
  x (m)           psi_n(x)                |psi_n(x)|^2
  0.000000e+00    0.00000000e+00          0.00000000e+00
  1.000000e-10    1.38196601e+04          1.90983006e+08
  5.000000e-10    4.47213595e+04          2.00000000e+09   ← peak at centre
  1.000000e-09    5.47678698e-12          2.99951957e-23
```

Full output in [`samples/sample-output.txt`](samples/sample-output.txt).

---

## Learning Outcomes

Working on this project reinforced several important skills:

**Physics & Mathematics**
- Applying the time-independent Schrödinger equation to a real model system
- Understanding energy quantisation and why only discrete levels are allowed
- Interpreting wavefunction nodes and the physical meaning of `|ψ|²`

**C Programming**
- Structuring a multi-function C program with clear separation of concerns
- Using `<math.h>` functions (`sin`, `sqrt`, `pow`) with double precision
- Command-line argument handling (`argc`, `argv`)
- Formatted I/O with `printf` for scientific notation output

**Software Engineering**
- Writing readable, well-commented scientific code
- Designing for reuse (the physics functions are independent of `main`)
- Input validation and graceful error handling

---

## Future Improvements

- [ ] **GNUplot integration** — pipe output directly to GNUplot for live wavefunction plots
- [ ] **Python post-processing script** — parse output and render `matplotlib` plots
- [ ] **Finite square well** — numerical shooting method for states in a well of finite depth
- [ ] **Time-dependent evolution** — animate wave packet motion using superposition of eigenstates
- [ ] **Multi-particle extension** — two non-interacting particles; illustrate the Pauli exclusion principle
- [ ] **CSV export** — add a `--csv` flag to dump data for spreadsheet analysis
- [ ] **3-D box extension** — generalise to a cubic infinite well (`n_x`, `n_y`, `n_z`)

---

## Authors

| Name | Roll Number |
|------|-------------|
| Akshat Tyagi | 241031016 |
| Anshit Guleria | 241032004 |
| Aansh Jain | 241030210 |
| Toshit Kaul | 241030436 |
| Saubhagya Sharma | — |

**Supervisor:** Prof. Dr. P. B. Barman  
**Institution:** Jaypee University of Information Technology, Waknaghat, Himachal Pradesh — 173234  
**Department:** Computer Science & Engineering and Information Technology

---

## References

1. Griffiths, D. J. (2018). *Introduction to Quantum Mechanics* (3rd ed.). Cambridge University Press.
2. Eisberg, R., & Resnick, R. (2002). *Quantum Physics of Atoms, Molecules, Solids, Nuclei, and Particles*. Wiley.
3. Beiser, A. (2003). *Concepts of Modern Physics*. McGraw-Hill.
4. NIST. (2023). [CODATA Fundamental Physical Constants](https://physics.nist.gov/cuu/Constants/).
5. ISO/IEC 9899:1999 — *Programming Languages — C* (C99 standard).

---

*Built with C · Quantum Mechanics · JUIT Waknaghat*
