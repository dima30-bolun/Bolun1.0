#pragma once
#include <functional>
#include <map>
#include <mutex>
#include <string>
#include <vector>
namespace luna {
struct Event { std::string topic; std::string payload; };
class EventBus {
public:
  using Handler = std::function<void(const Event&)>;
  int subscribe(const std::string& topic, Handler handler);
  bool unsubscribe(const std::string& topic, int id);
  int publish(const Event& event) const;
private:
  mutable std::mutex mutex_;
  int nextId_ = 1;
  std::map<std::string, std::map<int, Handler>> handlers_;
};
}
