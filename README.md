# PARSEC Benchmark with hardcoded ROI computation

This is a fork of the [Parsec benchmark fork modified for cross-compilation](https://github.com/darchr/parsec-benchmark).

I need to natively compile the binaries for RISC-V, and display the ROI on execution, but the `gcc-hooks`-configured builds failed with obscure ASM-related errors.

Since I couldn't find out a clean way to achieve this compilation, I just hardcoded the ROI routines.

Note that the `parsec-benchmark` fork not only improves cross-compilation compatibility, but also fixes some issues on native (RISC-V) compilation. Some benchmarks can't be cross-compiled because of x86 ASM code (`raytrace` and `x264`).
