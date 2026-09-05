#include <fstream>
#include <regex>
#include <iostream>
#include <string>
#include <cstdlib>
const std::string &rbxdecompasmloc = "/Users/artrix/offsetdumps/roblox.asm";

int spawnasmdecompcmd = std::system("otool -arch arm64 -tvV /Applications/Roblox.app/Contents/MacOS/RobloxPlayer > /Users/artrix/offsetdumps/roblox.asm");
std::string Dumpprint()
{
    std::string plcholder;
    std::ifstream disasm(rbxdecompasmloc);
    std::regex instruct(R"(bl\s+0x([0-9a-fA-F]+))");
    while(std::getline(disasm,plcholder))
    {
        if(plcholder.find("Current identity is %d")== std::string::npos)
        {
            continue;
        }
        while (std::getline(disasm, plcholder))
        {
            std::smatch got;

            if (std::regex_search(plcholder, got, instruct))
                return got[1].str();
        }
        break;
    }
    return {};
}


std::string Dumppuschcclosurek()
{
    std::string plcholder;
    std::ifstream disasm(rbxdecompasmloc);
    std::regex instruct(R"(bl\s+0x([0-9a-fA-F]+))");
    while(std::getline(disasm,plcholder))
    {
        if(plcholder.find("CyclicDependencyIndexError")== std::string::npos)
        {
            continue;
        }
        while (std::getline(disasm, plcholder))
        {
            std::smatch got;

            if (std::regex_search(plcholder, got, instruct))
                return got[1].str();
        }
        break;
    }
    return {};
}
int main(){
std::ofstream offsetsfile("/Users/artrix/offsetdumps/offsets.hpp");
std::string printsrbx = Dumpprint();
std::string pushcclosurek = Dumppuschcclosurek();
std::cout<<"Running Dumper...."<<std::endl;
offsetsfile<<"#define REBASE(x) ((uintptr_t)(x) + (uintptr_t)dyld_get_image_header(0) - 0x100000000)"<<std::endl;
offsetsfile<<"#include <cstdint.h>"<<std::endl;
offsetsfile<<"//Ron's Roblox ARM64 Internal Offsets dumper."<<std::endl;
offsetsfile<<"//@ron1447 on Discord."<<std::endl<<std::endl;
offsetsfile<<"namespace rbx{"<<std::endl<<std::endl;
offsetsfile <<"uintptr_t rbxprint = REBASE(0x"<<printsrbx<<");"<<" // Done via String search: \"Current identity is %d\", High confidence."<<std::endl;
offsetsfile <<"uintptr_t lua_pushcclosurek = REBASE(0x"<<pushcclosurek<<");"<<"// Done via String search: \"CyclicDependencyIndexError\", High confidence."<<std::endl;
offsetsfile<<std::endl<<'}'<<std::endl;
offsetsfile.close();
}