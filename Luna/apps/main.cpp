#include "ApplicationCatalog.hpp"
#include "NotificationCenter.hpp"
#include <iostream>
int main(){ luna::ApplicationCatalog catalog; catalog.add({"luna.settings","Luna Settings","luna-settings","settings"}); catalog.add({"luna.explorer","Luna Explorer","luna-explorer","folder"}); luna::NotificationCenter notifications; notifications.push("Luna","Services are ready"); std::cout << "Luna applications: " << catalog.all().size() << ", unread notifications: " << notifications.unread() << '\n'; return 0; }
