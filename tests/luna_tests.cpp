#include "BenFormat.hpp"
#include "BappPackage.hpp"
#include "ConfigStore.hpp"
#include "EventBus.hpp"
#include "NotificationCenter.hpp"
#include <filesystem>
#include <iostream>
int main(){ int delivered=0; luna::EventBus bus; bus.subscribe("boot",[&](const luna::Event&){++delivered;}); if(bus.publish({"boot","ready"})!=1||delivered!=1) return 1; auto dir=std::filesystem::temp_directory_path()/"luna-tests"; std::filesystem::create_directories(dir); luna::BenExecutable exe{"calc",{1,2,3},"main"}; auto ben=dir/"calc.ben"; if(!luna::BenFormat::write(ben,exe)) return 2; std::string output; if(!luna::BenFormat::run(luna::BenFormat::read(ben),output) || output.empty()) return 3; luna::BappManifest m{"luna.calc","Calculator","calc.ben","",{{"ru","Калькулятор"},{"en","Calculator"}}}; auto mf=dir/"manifest.bapp"; if(!luna::BappPackage::saveManifest(mf,m)) return 4; if(luna::BappPackage::loadManifest(mf).id!="luna.calc") return 5; luna::NotificationCenter nc; nc.push("a","b"); if(nc.unread()!=1) return 6; std::cout<<"luna tests passed\n"; }
