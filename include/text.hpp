#ifndef APACALYPSE_TEXT_HPP
#define APACALYPSE_TEXT_HPP

#include <string>
#include <SDL.h>

class Text {
public:
    Text(std::string  content);
    bool init(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color);
    SDL_Texture* getTexture() {return textTexture;}
    void setPosition(float x, float y) {this->x = x; this->y = y;}
    [[nodiscard]] float getX() const {return x;}
    [[nodiscard]] float getY() const {return y;}
    void setWidth(float width) {this->width = width;}
    [[nodiscard]] float getWidth() const {return width;}
    void setHeight(float height) {this->height = height;}
    [[nodiscard]] float getHeight() const {return height;}
    ~Text() {SDL_DestroyTexture(textTexture);}
private:
    SDL_Texture* textTexture;
    std::string content;
    float x;
    float y;
    float width;
    float height = 20;
};

#endif //APACALYPSE_TEXT_HPP
