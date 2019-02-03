/*
 * =====================================================================================
 *
 *       Filename:  ApplicationState.cpp
 *
 *    Description:
 *
 *        Created:  20/03/2014 21:21:01
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "ApplicationState.hpp"
#include "EndState.hpp"
#include "GameWindow.hpp"
#include "Game.hpp"
#include "Keyboard.hpp"
#include "MenuState.hpp"
#include "StateManager.hpp"

ApplicationState::ApplicationState(ApplicationState *parent) {
	m_type = Type::None;

	m_parent = parent;

	m_background = SDL_CreateTexture(GameWindow::main->renderer(), 372645892, SDL_TEXTUREACCESS_TARGET, GameWindow::main->width(), GameWindow::main->height());
	SDL_SetTextureBlendMode(m_background, SDL_BLENDMODE_BLEND);
}

ApplicationState::~ApplicationState() {
	if(m_background) SDL_DestroyTexture(m_background);
}

void ApplicationState::pollEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event) != 0) {
		switch(event.type) {
			case SDL_QUIT:
				Game::quit = true;
				break;
			case SDL_FINGERDOWN:
			case SDL_FINGERMOTION:
				Keyboard::updatePad(&event);
				break;
			case SDL_FINGERUP:
				Keyboard::resetPad(&event, true);
				break;
			case SDL_APP_WILLENTERBACKGROUND:
				Game::paused = true;
				break;
			case SDL_APP_WILLENTERFOREGROUND:
				Game::quit = true; // FIXME: See #9
				Game::paused = false;
				if(StateManager::top()->type() == Type::Map) {
					StateManager::push(new MenuState);
				}
				break;
			case SDL_APP_TERMINATING:
				if(StateManager::top()->type() != Type::GameEnd) {
					StateManager::push(new EndState);
				}
				break;
			default:
				break;
		}
	}
}

void ApplicationState::renderBackground() {
	SDL_Rect posRect = {0, 0, GameWindow::main->width(), GameWindow::main->height()};
	SDL_RenderCopy(GameWindow::main->renderer(), m_background, NULL, &posRect);
}

void ApplicationState::screenshot(ApplicationState *applicationstate) {
	SDL_SetRenderTarget(GameWindow::main->renderer(), m_background);
	applicationstate->render();
	SDL_SetRenderTarget(GameWindow::main->renderer(), NULL);
}
