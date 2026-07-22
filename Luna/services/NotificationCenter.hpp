#pragma once
#include <string>
#include <vector>
namespace luna { struct Notification { std::string title; std::string body; bool read=false; }; class NotificationCenter { public: void push(std::string title, std::string body); int unread() const; std::vector<Notification> list() const; void markAllRead(); private: std::vector<Notification> items_; }; }
