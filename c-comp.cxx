#include <stdio.h>
#include <stdlib.h>
#include <string>

//securitee? readabilitee? who da fuck needs that?

std::string ext_rm(char* val)
{
    std::string input(val);
    size_t dot = input.find_last_of('.');
    if (dot!=std::string::npos)
    {
        input.erase(dot,sizeof(long long));
    }
    return input;
}

int main(int argc, char** argv)
{
	if (argc < 2) { puts("How do i compile the nothing?"); goto ERROR; }
	char compyil[0x100];
	char deleet[sizeof(compyil)>>2];
	sprintf(compyil, "cl /EHsc /W0 /std:c++17 /O2 /I\"D:\\Windows Kits\\10\\Include\\10.0.17763.0\\ucrt\" /I\"D:\\DIMA\\ALL\\SDK\\Visual Studio\\IDE\\VC\\Tools\\MSVC\\14.16.27023\\include\" /Fo:\"%s\".~temp \"%s\"", ext_rm(argv[1]).c_str(), argv[1]);
	sprintf(deleet, "del \"%s.~temp\"", ext_rm(argv[1]).c_str());
    std::system("@echo off");
    std::system("set PATH=\%PATH\%;D:\\DIMA\\ALL\\SDK\\Visual Studio\\IDE\\VC\\Tools\\MSVC\\14.16.27023\\bin\\Hostx64\\x64");
    std::system("set LIB=\%LIB\%;D:\\DIMA\\ALL\\SDK\\Visual Studio\\IDE\VC\\Tools\\MSVC\\14.16.27023\\lib\x64;D:\\Windows Kits\\10\\Lib\\10.0.17763.0\\um\\x64;D:\\Windows Kits\\10\\Lib\\10.0.17763.0\\ucrt\\x64");
    std::system(compyil);
    std::system(deleet);

SUCCESS:
    return 0;
ERROR:
	return -1;
}