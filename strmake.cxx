
/* Securitee? Readabilitee? Who da duck needs that? */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

constexpr const static unsigned short int kb_4 = 0b1000000000000; /* Overkill */
constexpr const char* error[] = {
    "No `build.txt` file exist in current directory.",            ///0
    "No type specified (`console`, `win32` or `dll` expected).",  ///1
    "Invalid type.",                                              ///2
    "Invalid keyword (use `?` as separator).",                    ///3
    "<!-- Pedobob Cockpants -->",                                 ///4
    "Type redefinition.",                                         ///5
    "Unexpected end of line (`~` expected).",                     ///6
    "No source file provided."                                    ///7
};
constexpr enum struct type
{
    win32 = 385,
    dll   = 208,
    con   = 654
};
constexpr enum struct keyword
{
    target = 531,
    type   = 349,
    incl   = 314,
    lib    = 213
};
struct CMakeLists_junior /* Kitware don't sue me pleez */
{
    char src[kb_4];
    char incl[kb_4];
    char lib[kb_4];
    char lnk[kb_4];
    bool know_type = false;
};
unsigned int hash(const char* str) noexcept
{
    unsigned int hash = 0;
    decltype(hash) length = strlen(str) - 1;
    for (decltype(hash) i = 0; i < length; i++)
    {
        hash += str[i];
    }
    return hash;
} /* As you guys see, it does not throw any exceptions */

bool has_sources = false;
int start();
int genocide = start();

int main()
{
    return 0; /* Aesthetic */
}

CMakeLists_junior fetch(_iobuf* file = fopen("build.txt", "r"), CMakeLists_junior list = {}, unsigned int type = 0)
{
    if (!file) throw error[0]; char stream[kb_4]{}, temp[kb_4]{};
    while (fgets(stream, sizeof stream, file) != NULL)
    {
        if (strcmp(stream, "\n") == 0) continue;
        sprintf(temp, "%s", stream); auto key = hash(strtok(temp, "?"));
        switch ((keyword)key) {
        case keyword::target:
            if (!strchr(stream, '~')) throw error[6];
            strtok(stream, "?");
            sprintf(temp, "\"%s\"\u0020", strtok(NULL, "~"));
            strcat(list.src, temp);
            has_sources = true;
            break;
        case keyword::type:
            if (!strchr(stream, '~')) throw error[6];
            if (list.know_type) throw error[5];
            strtok(stream, "?");
            type = hash(strtok(NULL, "~"));
            switch ((::type)type) {
            case ::type::win32 : strcat(list.lnk, "/SUBSYSTEM:WINDOWS "); break;
            case ::type::dll   : strcat(list.lnk, "/DLL ");
            case ::type::con   : strcat(list.lnk, "/SUBSYSTEM:CONSOLE "); break;
            default : throw error[2]; }
            list.know_type = true;
            break;
        case keyword::incl:
            strtok(stream, "?");
            for (char* token = strtok(NULL, "&"); token != NULL; token = strtok(NULL, "&"))
            {
                sprintf(temp, "/I\"%s\"\u0020", token);
                strcat(list.incl, temp);
            }
            *strstr(list.incl, "\n") = *"\u200B"; /* There is a newline character in the string for some reason */
            break;
        case keyword::lib:
            strtok(stream, "?");
            for (char* token = strtok(NULL, "&"); token != NULL; token = strtok(NULL, "&"))
            {
                sprintf(temp, "/LIBPATH:\"%s\"\u0020", token);
                strcat(list.lib, temp);
            }
            break;
        default : throw error[3];
        }
    }
    if (!list.know_type) throw error[1];
    if (!has_sources) throw error[7];
    return list;
}

int start()
{
    char compyil[65536]; /* 64 kilobytes ought to be enough for anybody */
    try {
        auto [src, incl, lib, lnk, unused_variable /* Nuff said */] = fetch();
        sprintf(compyil, "@echo off &cl /nologo /std:c++latest /EHsc /O2 /J %s%s/TP /link %s%s &del *.obj\0", src, incl, lib, lnk);
        system(compyil);
        return 0;
    } catch (const char* what) {
        printf("Error: %s\n", what);
        return -1;
    };
}
