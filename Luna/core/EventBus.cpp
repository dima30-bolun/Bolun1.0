#include "EventBus.hpp"
namespace luna {
int EventBus::subscribe(const std::string& topic, Handler handler) {
  if (topic.empty() || !handler) return 0;
  std::lock_guard<std::mutex> lock(mutex_);
  const int id = nextId_++;
  handlers_[topic][id] = std::move(handler);
  return id;
}
bool EventBus::unsubscribe(const std::string& topic, int id) {
  std::lock_guard<std::mutex> lock(mutex_);
  auto it = handlers_.find(topic);
  if (it == handlers_.end()) return false;
  return it->second.erase(id) == 1;
}
int EventBus::publish(const Event& event) const {
  std::vector<Handler> copy;
  {
    std::lock_guard<std::mutex> lock(mutex_);
    auto exact = handlers_.find(event.topic);
    if (exact != handlers_.end()) for (const auto& pair : exact->second) copy.push_back(pair.second);
    auto all = handlers_.find("*");
    if (all != handlers_.end()) for (const auto& pair : all->second) copy.push_back(pair.second);
  }
  for (const auto& handler : copy) handler(event);
  return static_cast<int>(copy.size());
}
}
