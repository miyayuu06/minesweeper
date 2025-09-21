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
                    bool right = SDL_GetMouseState(&x, &y) == SDL_BUTTON_X1;
                    std::cout << std::endl << SDL_GetMouseState(&x, &y) << std::endl << std::endl;
                    d.update(x, y, right);
                    clicked = true;
                }
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                clicked = false;
            }
        }
        d.render(x, y);
    }

    std::cout << "Hello World!\n";
}