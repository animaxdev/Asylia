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
	std::stringstream initCall;
	
	m_type = Type::Event;
	
	m_folder = folder;
	m_table = table;
	
	LuaHandler::doFile((folder + "main.lua").c_str());
	
	initCall << m_table << ".init()";
	
	LuaHandler::doString(initCall.str());
}

Event::~Event() {
}

void Event::update() {
	move(m_folder + "movement.lua");
	
	LuaHandler::doString(m_table + ".update()");
}

void Event::render() {
	Character::render();
	
	LuaHandler::doString(m_table + ".render()");
}

void Event::exec() {
	LuaHandler::doString(m_table + ".exec()");
}

