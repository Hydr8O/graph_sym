#include <application.hpp>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1020

int main() {
    Application app(WINDOW_WIDTH, WINDOW_HEIGHT, "Graph Sym");
    app.run();
    return 0;
}