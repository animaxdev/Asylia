/*
 * =====================================================================================
 *
 *       Filename:  Game.cpp
 *
 *    Description:
 *
 *        Created:  14/03/2014 21:26:04
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

bool Game::quit = false;
bool Game::paused = false;

#ifdef __ANDROID__
std::string to_string(int n) {
	std::stringstream s; s << n; return s.str();
}
#endif

Game::Game() {
	srand(time(NULL));

	SDLManager::init();

	GameWindow::main = new GameWindow(APP_NAME);

	Sound::init();

	Interface::init();

	LanguageManager::init("en-us");

	ActivityManager::init();
}

Game::~Game() {
	ActivityManager::free();

	Interface::free();

	Sound::free();

	delete GameWindow::main;

	SDLManager::free();

	exit(EXIT_SUCCESS);
}

void Game::mainLoop() {
	while(!quit) {
		if(TimeManager::isTimeToUpdate()) {
			ActivityManager::top()->pollEvents();

			Keyboard::update();

			if(Game::paused == true) continue;

			ActivityManager::top()->update();

			if(TimeManager::hasEnoughTimeToDraw()) {
				TimeManager::beginMeasuringRenderingTime();

				GameWindow::main->clear();

				ActivityManager::top()->render();

				TimeManager::renderRTMCounter(); // Rendering time mean

				Interface::renderHUD();

				GameWindow::main->update();

				TimeManager::endMeasuringRenderingTime();
			}
		} else {
			TimeManager::waitUntilItsTime();
		}

		TimeManager::measureFrameDuration();
	}
}

