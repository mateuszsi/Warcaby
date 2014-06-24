#pragma once

#include "Headers.h"
#include "Window.h"
#include "Plansza.h"
#include "ClassButton.h"

void Update(Plansza &plansza, SDL_Event e, int &zabezpieczenie, bool &start, ClassButton &przycisk, char &tura, bool &gramy);
void Render(Window window, Plansza &plansza, ClassButton &button);