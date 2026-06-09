# Language Policy

## Allowed implementation languages

All project code must be implemented in one of these languages:

1. C
2. C++
3. C#
4. Assembly

## Prohibited implementation languages

Do not add Python or Java source files, generators, launchers, tests, build helpers, or runtime dependencies.

Prohibited examples include:

- `*.py`, `requirements.txt`, `pyproject.toml`, `Pipfile`
- `*.java`, `pom.xml`, `build.gradle`, `settings.gradle`

## C# exception

C# is allowed only for built-in applications and games under `src/csharp/`.

## Build policy

The default build must compile native C, C++, and Assembly sources directly with compiler toolchains. It must not call Python or Java.
