#pragma once

namespace fr {
class Window {
public:
    Window();
    ~Window();

    void MainLoop();

private:
    void* window_ = nullptr;
};
} // namespace fr
