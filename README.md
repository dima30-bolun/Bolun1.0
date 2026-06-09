# Bolun 1.0

Bolun 1.0 is configured as a native-only workspace. New source code must be written only in:

- C (`.c`, `.h`)
- C++ (`.cpp`, `.hpp`, `.cc`, `.hh`)
- C# (`.cs`, `.csproj`) for built-in applications and games only
- Assembly (`.asm`, `.s`, `.S`, `.inc`)

Python and Java are intentionally excluded from the source tree and from the build flow.

## Build

Build the native demonstration binary:

```sh
make
```

Run it:

```sh
make run
```

Clean generated objects and binaries:

```sh
make clean
```

## Optional C# built-in app/game compilation

C# is permitted only under `src/csharp/` for built-in applications and games. If a C# compiler is installed, run:

```sh
make csharp
```

The C# target uses `dotnet`, `csc`, or `mcs` when one is available. No Python or Java tooling is used.
