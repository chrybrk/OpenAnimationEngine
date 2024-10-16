#define IMPLEMENT_BUILD_C
#include "build.h"

#define CC "g++"
#define CFLAGS  "-O3", "-g0", "-Ofast"

#define LIBS "-Lvendor/lib/ -l:libraylib.a -lm"

int main(int argc, char *argv[])
{
	int engFPlen;
	char **engFP = get_files_from_directory("engine/", &engFPlen);

	if (needs_recompilation("bin/libengine.a", (const char **)engFP, engFPlen))
	{
		for (size_t i = 0; i < engFPlen; ++i)
		{
			size_t len = strlen(engFP[i]);
			char *s = substr(engFP[i], 3);

			if (!strcmp(s, "cpp"))
				CMD(
					CC,
					CFLAGS,
					"-Iengine/",
					"-Ivendor/include/",
					"-c", engFP[i],
					"-o",
					LIBS,
					writef("bin/%s.o", engFP[i])
				);
		}

		CMD("ar", "rcs", "bin/libengine.a", "bin/engine/*.o");
	}

	int SandboxFPlen;
	char **sandboxFP = get_files_from_directory("sandbox/", &SandboxFPlen);

	if (needs_recompilation("bin/sandbox", (const char**)sandboxFP, SandboxFPlen))
	{
		CMD(
			CC,
			CFLAGS,
			"-Iengine/",
			"-Ivendor/include/",
			"sandbox/*.cpp",
			"-Lbin/",
			"-l:libengine.a",
			LIBS,
			"-o",
			"bin/sandbox"
		);
	}

	return 0;
}
