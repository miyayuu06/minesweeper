#include "display.h"
#include <iostream>

using namespace MS;

int main()
{
    Display d;
    SDL_Event event;
    bool clicked = false;

    while (true) {
        float x, y;
        SDL_GetMouseState(&x, &y);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                return 0;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
                if (!clicked) {
                    d.update(clicked, x, y);
                    clicked = true;
                }
                std::cout << d.print() << std::endl;
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                clicked = false;
            }
        }
        d.update(clicked, x, y);
    }

    std::cout << "Hello World!\n";
}