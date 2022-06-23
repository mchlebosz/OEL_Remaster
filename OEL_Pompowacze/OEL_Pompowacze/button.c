#include "button.h"

button_t button_create_from_image(SDL_Renderer* renderer, char* path, int x, int y, int w, int h) {
	button_t button;
	button.renderer = renderer;
	button.is_selected = false;
	button.txt = IMG_LoadTexture(renderer, path);
	button.rect.x = x;
	button.rect.y = y;
	button.rect.w = w;
	button.rect.h = h;

	return button;
}

button_t button_create(SDL_Renderer* renderer, string s, int font_size, int x, int y, SDL_Color text_color) {
	label_t lb = label_create(renderer, font_size, s, text_color);
	button_t button;
	button.renderer = renderer;
	button.is_selected = false;
	button.txt = lb.texture;
	button.rect = lb.rect;
	button.rect.x = x;
	button.rect.y = y;
	return button;
}

void button_update(button_t* button, mouse_t* mouse) {
	int x = mouse->rect.x;
	int y = mouse->rect.y;
	button->is_selected = button->rect.x <= x && x <= button->rect.x + button->rect.w
		&& button->rect.y <= y && y <= button->rect.y + button->rect.h;
}

void button_draw(const button_t* button) {
	SDL_RenderCopy(button->renderer, button->txt, NULL, &button->rect);
}

void button_free(const button_t* button) {
	SDL_DestroyTexture(button->txt);
}