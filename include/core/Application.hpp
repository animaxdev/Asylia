/*
 * =====================================================================================
 *
 *       Filename:  Application.hpp
 *
 *    Description:
 *
 *        Created:  14/03/2014 21:27:51
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <gk/core/CoreApplication.hpp>

#include "GameWindow.hpp"
#include "KeyboardHandler.hpp"
#include "LanguageManager.hpp"
#include "LuaHandler.hpp"

class Application : public gk::CoreApplication {
	public:
		Application(int argc, char **argv);

		void init() override;

	private:
		void onEvent(const SDL_Event &event) override;
		void mainLoop() override;

		GameWindow m_window;

		KeyboardHandler m_keyboardHandler;

		LanguageManager m_languageManager;

		LuaHandler m_luaHandler;
};

#endif // APPLICATION_HPP_
