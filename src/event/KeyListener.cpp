#include "event/KeyListener.h"

#include <functional>

namespace vngine {
namespace event {

KeyEvent KeyListener::event{};
std::mutex KeyListener::eventMutex{};
std::condition_variable KeyListener::cv{};

KeyListener::KeyListener(GLFWwindow* window) {
        using namespace std::placeholders;
        glfwSetKeyCallback(window, &KeyListener::callback);
}

const KeyEvent& KeyListener::wait() {
        std::unique_lock<std::mutex> lock(eventMutex);
        cv.wait(lock);
        return event;
}

void KeyListener::poll() { glfwPollEvents(); }

void KeyListener::callback(GLFWwindow*, int key, int scancode, int action, int mods) {
        std::unique_lock<std::mutex> lock(eventMutex);
        event = {key, scancode, action, mods};
        lock.unlock();
        cv.notify_all();
}

} // namespace event
} // namespace vngine
