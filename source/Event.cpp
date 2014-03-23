/*
 * =====================================================================================
 *
 *       Filename:  Event.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/03/2014 23:54:51
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

Event::Event(std::string folder, std::string table, std::string appearance, u16 x, u16 y, u8 anim, u16 area, u16 mapX, u16 mapY) : Character(appearance.c_str(), x, y, anim, area, mapX, mapY) {
	m_type = Type::Event;
	
	m_folder = folder;
	m_table = table;
}

Event::~Event() {
}

void Event::init() {
	LuaHandler::doFile((m_folder + "main.lua").c_str());
	LuaHandler::doString(m_table + ".init()");
}

void Event::update() {
	move(m_table + ".movements[" + std::to_string(m_movementID) + " % #" + m_table + ".movements + 1](" + std::to_string(m_speed) + ")");
	
	LuaHandler::doString(m_table + ".update()");
	
	action();
}

void Event::render() {
	Character::render();
	
	LuaHandler::doString(m_table + ".render()");
}

void Event::action() {
	if(CharacterManager::player->inFrontOf() == this) {
		LuaHandler::doString(m_table + ".action()");
	}
}

void Event::collisionAction() {
	LuaHandler::doString(m_table + ".collisionAction()");
}

