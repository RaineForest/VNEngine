#pragma once

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>
#include <unordered_map>

namespace vngine {
namespace event {

template<typename EventType>
class IListener {
public:
        IListener() = default;
        virtual ~IListener() = default;

        IListener(const IListener&) = delete;
        IListener& operator=(const IListener&) const = delete;

        virtual const EventType& wait() = 0;

        virtual void poll() = 0;
};

} // namespace event
} // namespace vngine
