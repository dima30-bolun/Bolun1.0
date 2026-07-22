#include "BenFormat.hpp"
#include <iostream>
int main(int argc,char** argv){ if(argc<4){ std::cerr<<"usage: luna-builder output.ben name entry\n"; return 2; } luna::BenExecutable exe{argv[2], {'L','u','n','a'}, argv[3]}; if(!luna::BenFormat::write(argv[1],exe)){ std::cerr<<"cannot write BEN file\n"; return 1; } return 0; }
