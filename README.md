# PARSEC Benchmark with tweaks (hardcoded ROI computation, parallel make)

This is a fork of the [Parsec benchmark fork modified for cross-compilation](https://github.com/darchr/parsec-benchmark), with a couple of tweaks.

## Hardcoded ROI computation

I need to natively compile the binaries for RISC-V, and display the ROI on execution, but the `gcc-hooks`-configured builds failed with obscure ASM-related errors.

Since I couldn't find out a clean way to achieve this compilation, I just hardcoded the ROI routines.

Note that the `parsec-benchmark` fork not only improves cross-compilation compatibility, but also fixes some issues on native (RISC-V) compilation. Some benchmarks can't be cross-compiled because of x86 ASM code (`raytrace` and `x264`).

## Parallel make

The `parsecmgmt` script runs invokes `make` in sequential mode (without the `-j` option); I've added the jobs parameter with one recipe per processor (`-j $(nproc)`), in order to use speed up the compilation as much as possible.
