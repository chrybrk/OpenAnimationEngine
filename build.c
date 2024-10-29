#define IMPLEMENT_BUILD_C
#include "build.h"

void **merge_two_buffer(void **a, size_t n, void **b, size_t m)
{
	void **buffer = malloc((m + n) * sizeof(void**));

	for (size_t i = 0; i < n; ++i) buffer[i] = a[i];
	for (size_t i = 0; i < m; ++i) buffer[i + n] = b[i];

	return buffer;
}

int main(int argc, char **argv)
{
	int n;
	char **files = get_list_of_files_ext("oaelib/", ".c", &n);
	library_static("gcc -Ioaelib/", files, n, "bin/", "liboae.a");

	int m;
	char **source = get_list_of_files_ext("sandbox/", ".c", &m);
	if (needs_recompilation("bin/sandbox", (const char **)merge_two_buffer((void**)source, m, (void *[]){ "bin/liboae.a" }, 1), m + 1))
	{
		CMD(
			"gcc",
			"-Ioaelib",
			"-Isandbox",
			"-Ivendor/raylib/include",
			join(' ', (const char **)source, m),
			"-o",
			"bin/sandbox",
			"-Lvendor/raylib/lib",
			"-Lbin/",
			"-l:libraylib.a",
			"-lm",
			"-l:liboae.a"
		);
	}

	if (needs_recompilation("bin/test", (const char*[]){ "test/main.c" }, 1))
	{
		CMD(
			"gcc",
			"-Ivendor/raylib/include/",
			"test/main.c",
			"-o",
			"bin/test",
			"-Lvendor/raylib/lib",
			"-Lbin/",
			"-l:libraylib.a",
			"-lm"
		);
	}

	return 0;
}
