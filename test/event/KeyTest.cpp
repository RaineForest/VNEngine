
#include "event/KeyListener.h"

#include <GLFW/glfw3.h>

#include <functional>
#include <iostream>
#include <thread>

int main() {
	if (!glfwInit()) {
		throw std::runtime_error("Failed to init GLFW");
	}

	auto window = std::unique_ptr<GLFWwindow, std::function<void(GLFWwindow*)>>(
		glfwCreateWindow(100, 100, "keytest", NULL, NULL),
		[](GLFWwindow* me) { glfwDestroyWindow(me); }
	);

	if (!window) {
		throw std::runtime_error("Failed to open window");
	}

	glfwMakeContextCurrent(window.get());

	glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);

        vngine::event::KeyListener listener(window.get());
	std::thread poll([&]() {
		while(true) {
			listener.poll();
		}
	});
        while (true) {
                auto event = listener.wait();
                std::cout << event.key << ", " << event.scancode << ", " << event.action << ", " << event.mods << std::endl;
        }
}
