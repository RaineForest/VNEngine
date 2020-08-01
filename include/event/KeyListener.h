#pragma once

#include "event/IListener.h"

#include <GLFW/glfw3.h>

#include <mutex>
#include <queue>

namespace vngine {
namespace event {

/// see GLFW key events
struct KeyEvent
{
        int key;
        int scancode;
        int action;
        int mods;
};

class KeyListener : public IListener<KeyEvent> {
public:
        KeyListener(GLFWwindow* window);
        virtual ~KeyListener() = default;

        virtual const KeyEvent& wait() override;

        virtual void poll() override;

private:
        static KeyEvent event; 
        static std::mutex eventMutex;
        static std::condition_variable cv;

        static void callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};

} // namespace event
} // namespace vngine
