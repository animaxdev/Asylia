/*
 * =====================================================================================
 *
 *       Filename:  StateManager.cpp
 *
 *    Description:
 *
 *        Created:  20/03/2014 21:49:08
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Asylia.hpp"
#include "MapState.hpp"
#include "TitleState.hpp"

std::stack<ApplicationState*> StateManager::activities;

void StateManager::init() {
#ifdef NO_TITLESCREEN
	activities.push(new MapState);
	((MapState *)activities.top())->init();
#else
	activities.push(new TitleState);
#endif
}

void StateManager::free() {
	while(activities.size() != 0) {
		pop();
	}
}

void StateManager::push(ApplicationState *state) {
	activities.push(state);
	if(top()->parent()) top()->screenshot(top()->parent());
	if(top()->type() == ApplicationState::Type::Map) ((MapState*)state)->init();
	if(top()->type() != ApplicationState::Type::Message) top()->update();
}

