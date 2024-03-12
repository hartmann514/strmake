#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <utility>

/* Securitee? Readabilitee? Who da duck needs that? */

bool s_known = false;

std::pair<char*, char*> parser(int argc, char** argv)
{
    /* 64 kilobytes ought to be enough for anybody */
    char lnk[65536] = "/MACHINE:X64 ";
    char src[65536]{};
    for (int i = argc - 1; i > 0; i--)
    {
        std::string arg(argv[i]);
        if (strcmp(arg.substr(0, 2).c_str(), "--") == 0)
        {
            goto PARAM;
        }
        {
            arg.insert(0, "\"");
            strcat(src, (arg += "\" ").c_str());
            continue;
        }
PARAM: /* summoning the YandereDev */
        if (strcmp(arg.substr(2).c_str(), "dll") == 0)
        {
            strcat(lnk, "/DLL "); continue;
        }
        if (strcmp(arg.substr(2, 1).c_str(), "s") == 0)
        {
            strcat(lnk, "/SUBSYSTEM:");
            if (strcmp(arg.substr(4).c_str(), "con") == 0)
            {
                strcat(lnk, "CONSOLE ");
            } else
            if (strcmp(arg.substr(4).c_str(), "win32") == 0)
            {
                strcat(lnk, "WINDOWS ");
            } else
            {
                strcat(lnk, "CONSOLE ");
            } s_known = true; continue;
        }
    }
    if (!s_known) strcat(lnk, "/SUBSYSTEM:CONSOLE ");
    return std::make_pair(lnk, src);
}
int main(int argc, char** argv)
{
	if (argc < 2) { puts("Usage: c-comp (sources <one with main() must be passed last>) [--dll] [--s:con/win32]\0"); goto ERROR; }
    system("@echo off");
    {
        char lib[]  = "/LIBPATH:\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\Build Tools\\VC\\Tools\\MSVC\\14.29.30133\\lib\\x64\" /LIBPATH:\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\Windows Kits\\10\\Lib\\10.0.19041.0\\ucrt\\x64\" /LIBPATH:\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64\" /LIBPATH:\"D:\\DIMA\\ALL\\SDK\\_Libraries\\SDL2\\lib\\x64\" /LIBPATH:\"D:\\DIMA\\ALL\\SDK\\_Libraries\\bass\\c\"";
        char incl[] = "/I\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\Build Tools\\VC\\Tools\\MSVC\\14.29.30133\\include\" /I\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\Windows Kits\\10\\Include\\10.0.19041.0\\ucrt\" /I\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\Windows Kits\\10\\Include\\10.0.19041.0\\um\" /I\"D:\\DIMA\\ALL\\SDK\\_Libraries\\SDL2\\include\" /I\"D:\\DIMA\\ALL\\SDK\\_Libraries\\bass\\c\"";
        char compyil[65536];
        const char* deleet = "del *.~temp";
        auto [lnk, src] = parser(argc, argv);
        sprintf(compyil, "cl /nologo /std:c++latest /EHsc /Oy /O2 /Gd /J %s %s/TP /Fo\".~temp\" /link %s %s/out:\"output.exe\"", incl, src, lib, lnk);
        printf("%s\n", compyil);
        system(compyil);
        system(deleet);
    }
SUCCESS:
    return 0;
ERROR:
	return -1;
}
