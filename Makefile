CC ?= gcc
CXX ?= g++
NASM ?= nasm
CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic -O2
CXXFLAGS ?= -std=c++17 -Wall -Wextra -Wpedantic -O2
LDFLAGS ?=

BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
OBJ_DIR := $(BUILD_DIR)/obj
TARGET := $(BIN_DIR)/bolun-native

C_OBJS := $(OBJ_DIR)/core.o
CPP_OBJS := $(OBJ_DIR)/main.o
ASM_OBJS := $(OBJ_DIR)/add_i64.o
OBJS := $(C_OBJS) $(CPP_OBJS) $(ASM_OBJS)

.PHONY: all run clean csharp check-policy

all: check-policy $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

$(OBJ_DIR)/core.o: src/c/core.c src/c/core.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/main.o: src/cpp/main.cpp src/c/core.h | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -Isrc/c -c $< -o $@

$(OBJ_DIR)/add_i64.o: src/asm/add_i64.asm | $(OBJ_DIR)
	$(NASM) -f elf64 $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

run: all
	$(TARGET)

csharp: check-policy
	@if command -v dotnet >/dev/null 2>&1; then \
		dotnet build src/csharp/BolunBuiltins/BolunBuiltins.csproj; \
	elif command -v csc >/dev/null 2>&1; then \
		mkdir -p $(BIN_DIR); \
		csc -nologo -out:$(BIN_DIR)/BolunBuiltins.exe src/csharp/BolunBuiltins/Program.cs; \
	elif command -v mcs >/dev/null 2>&1; then \
		mkdir -p $(BIN_DIR); \
		mcs -out:$(BIN_DIR)/BolunBuiltins.exe src/csharp/BolunBuiltins/Program.cs; \
	else \
		echo "No C# compiler found. Install dotnet, csc, or mcs to build C# built-ins."; \
		exit 1; \
	fi

check-policy:
	@if find . -path ./.git -prune -o -type f \( \
		-name '*.py' -o -name '*.java' -o -name 'requirements.txt' -o \
		-name 'pyproject.toml' -o -name 'Pipfile' -o -name 'pom.xml' -o \
		-name 'build.gradle' -o -name 'settings.gradle' \
	\) -print | sed -n '1q' | grep -q .; then \
		echo "Language policy violation: Python/Java files are not allowed."; \
		find . -path ./.git -prune -o -type f \( \
			-name '*.py' -o -name '*.java' -o -name 'requirements.txt' -o \
			-name 'pyproject.toml' -o -name 'Pipfile' -o -name 'pom.xml' -o \
			-name 'build.gradle' -o -name 'settings.gradle' \
		\) -print; \
		exit 1; \
	fi

clean:
	rm -rf $(BUILD_DIR)
