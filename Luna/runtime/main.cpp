#include "BenFormat.hpp"
#include <iostream>
int main(int argc,char** argv){ if(argc!=2){ std::cerr<<"usage: luna-runtime app.ben\n"; return 2; } auto exe=luna::BenFormat::read(argv[1]); std::string out; if(!luna::BenFormat::run(exe,out)){ std::cerr<<"invalid BEN executable\n"; return 1; } std::cout<<out<<'\n'; return 0; }
