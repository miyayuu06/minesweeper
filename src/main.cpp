#include "display.h"
#include <iostream>

using namespace MS;

int main()
{
    Display d;
    SDL_Event event;

    while (true) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                return 0;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                std::cout << d.print() << std::endl;
            }
        }
        d.update(x, y);
    }

    std::cout << "Hello World!\n";
}