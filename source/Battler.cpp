/*
 * =====================================================================================
 *
 *       Filename:  Battler.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/04/2014 19:32:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

Battler::Battler(std::string name, std::string appearance, u8 level, s16 hp, s16 sp, u16 atk, u16 def) {
	m_name = name;
	
	m_image = new Image(appearance.c_str());
	
	m_inventory = NULL;
	
	m_level = level;
	
	m_hp = hp;
	m_sp = sp;
	
	m_atk = atk;
	m_def = def;
}

Battler::~Battler() {
	if(m_image) delete m_image;
}

u16 Battler::totalAtk() {
	u16 atk = m_atk;
	if(m_inventory && m_inventory->weapon()) atk += m_inventory->weapon()->atk();
	return atk;
}

u16 Battler::totalDef() {
	u16 def = m_def;
	if(m_inventory) {
		for(auto it : m_inventory->armorlist()) {
			def += it->def();
		}
	}
	return def;
}

