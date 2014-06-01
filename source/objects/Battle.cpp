/*
 * =====================================================================================
 *
 *       Filename:  Battle.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  23/04/2014 18:05:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

Battle::Battle(const Battle &battle) {
	for(auto &it : battle.m_actors) {
		m_actors.push_back(std::make_pair(it.first, new Actor(*it.second)));
	}
	
	for(auto &it : battle.m_enemies) {
		m_enemies.push_back(std::make_pair(it.first, new Enemy(*it.second)));
	}
	
	m_actorsCount = battle.m_actorsCount;
	m_enemiesCount = battle.m_enemiesCount;
	
	m_battleback = new Image(*battle.m_battleback);
}

Battle::Battle(std::string battleback) {
	m_actorsCount = 0;
	m_enemiesCount = 0;
	
	m_battleback = new Image(battleback.c_str());
}

Battle::~Battle() {
	delete m_battleback;
	
	while(m_actors.size() != 0) {
		delete m_actors.back().second;
		m_actors.pop_back();
	}
	
	while(m_enemies.size() != 0) {
		delete m_enemies.back().second;
		m_enemies.pop_back();
	}
}

void Battle::drawArrow(Battler *battler) {
	s16 x, y;
	u16 width, height;
	
	width = battler->image()->posRect().w;
	height = battler->image()->posRect().h;
	
	x = battler->image()->posRect().x + width / 2 - 16;
	y = battler->image()->posRect().y + height / 2;
	
	Interface::interface->render(x, y, 32, 32, 128 + 32 * (SDL_GetTicks() / 4 % 2), 96, 32, 32);
}

void Battle::enemyTurn() {
	for(auto &it : m_enemies) {
		pushAction(it.second, m_actors[rand() % m_actors.size()].second, ItemManager::skills[0]);
	}
}

void Battle::pushAction(Battler *actor, Battler *receiver, Item *item) {
	m_actionStack.push(new BattleAction(actor, receiver, item));
}

void Battle::processAction() {
	if(m_actionStack.top()->receiver()->hp() == 0) {
		if(m_actionStack.top()->receiver()->type() == Battler::Type::TypeEnemy) {
			m_actionStack.top()->setReceiver(getNextEnemyPair(1, -1).second);
		} else {
			m_actionStack.top()->setReceiver(getNextActorPair(1, -1).second);
		}
	}
	
	m_actionStack.top()->process();
}

void Battle::checkDead() {
	if(m_actionStack.top()->receiver()->hp() == 0) {
		if(m_actionStack.top()->animationAtEnd()) m_actionStack.top()->receiver()->kill();
	}
}

std::pair<u8, Actor*> Battle::getNextActorPair(s8 v, s8 current) {
	do {
		current += v;
		if(current >= (s8)m_actors.size() || current < 0) {
			return std::make_pair(current, (Actor*)NULL);
		}
	} while(getActor(current)->hp() == 0);
	
	return m_actors[current];
}

std::pair<u8, Enemy*> Battle::getNextEnemyPair(s8 v, s8 current) {
	do {
		current += v;
		if(current >= (s8)m_enemies.size() || current < 0) {
			return std::make_pair(current, (Enemy*)NULL);
		} else {
		}
	} while(getEnemy(current)->hp() == 0);
	
	return m_enemies[current];
}

void Battle::renderBattleback() {
	m_battleback->render();
}
