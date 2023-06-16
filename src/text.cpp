#include <iostream>
#include <utility>
#include <SDL_ttf.h>
#include "../include/text.hpp"


Text::Text(std::string  content)
: content(std::move(content)) {
}

bool Text::init(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color) {
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, content.c_str(), color);
    if (textSurface == nullptr) {
        std::cout << "TTF_RenderText_Solid ERROR: " << TTF_GetError() << std::endl;
        return false;
    } else {
        textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (textTexture == nullptr) {
            std::cout << "SDL_CreateTextureFromSurface ERROR: " << SDL_GetError() << std::endl;
            return false;
        } else {
            width = textSurface->w;
            height = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return true;
}