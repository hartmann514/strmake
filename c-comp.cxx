#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <tuple>

/* Securitee? Readabilitee? Who da duck needs that? */

constexpr unsigned short kb_4 = 4096;
bool s_known = false;

char* args(int argc, char** argv);
std::tuple<char*, char*, char*> fetch();

int main(int argc, char** argv)
{
    system("@echo off");
    /* 64 kilobytes ought to be enough for anybody */
    char compyil[65536];
    const char* deleet = "del *.obj";
    char* lnk = args(argc, argv);
    auto [incl, lib, src] = fetch();
    sprintf(compyil, "cl /nologo /std:c++latest /EHsc /O2 /Gd /J %s%s/TP /link %s%s\n\n\0", incl, src, lib, lnk);
    system(compyil);
    system(deleet);
    return 0;
}

char* args(int argc, char** argv)
{
    char lnk[65536] = "/MACHINE:X64 ";
    for (int i = argc - 1; i > 0; i--)
    {
        /* summoning the YandereDev */
        std::string arg(argv[i]);
        if (strcmp(arg.c_str(), "dll") == 0)
        {
            strcat(lnk, "/DLL "); continue;
        }
        if (strcmp(arg.c_str(), "s") == 0)
        {
            strcat(lnk, "/SUBSYSTEM:");
            if (strcmp(arg.substr(2).c_str(), "con") == 0)
            {
                strcat(lnk, "CONSOLE ");
            } else
            if (strcmp(arg.substr(2).c_str(), "win32") == 0)
            {
                strcat(lnk, "WINDOWS ");
            } else
            {
                strcat(lnk, "CONSOLE ");
            } s_known = true; continue;
        }
    }
    if (!s_known) strcat(lnk, "/SUBSYSTEM:CONSOLE ");
    return lnk;
}

std::tuple<char*, char*, char*> fetch()
{
    char*(*istr)(_iobuf*, const char*) = <::> (_iobuf* stream, const char* key)
    {
        char buf[kb_4]; char* str = new char[kb_4]{};
        while (fgets(buf, sizeof buf, stream) != NULL)
        {
            buf[strcspn(buf, "\n")] = 0;
            strcat(str, key);
            strcat(str, buf);
            strcat(str, "\" ");
        }
        fclose(stream);
        return str;
    };
    return std::make_tuple(istr(fopen("incl.txt", "r"), "/I\""), istr(fopen("lib.txt", "r"), "/LIBPATH:\""), istr(fopen("src.txt", "r"), "\""));
}
