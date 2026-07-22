.PHONY: all build test clean check-policy
all: build
build: check-policy
	cmake -S . -B build
	cmake --build build
test: build
	ctest --test-dir build --output-on-failure
check-policy:
	@if find . -path ./.git -prune -o -type f \( -name '*.py' -o -name '*.java' -o -name 'requirements.txt' -o -name 'pyproject.toml' -o -name 'Pipfile' -o -name 'pom.xml' -o -name 'build.gradle' -o -name 'settings.gradle' \) -print | sed -n '1q' | grep -q .; then echo "Language policy violation"; exit 1; fi
clean:
	rm -rf build
