/*
 * =====================================================================================
 *
 *       Filename:  Battle.hpp
 *
 *    Description:
 *
 *        Created:  23/04/2014 18:03:16
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BATTLE_HPP_
#define BATTLE_HPP_

#include "Actor.hpp"
#include "BattleAction.hpp"
#include "Item.hpp"
#include "Troop.hpp"

class Battle {
	public:
		Battle(const Battle &battle);
		Battle();
		~Battle();

		void addActor(Actor *actor) { m_actors.push_back(std::make_pair(m_actorsCount, new Actor(*actor))); m_actorsCount++; }

		void addTroop(Troop *troop);
		void addEnemy(Enemy *enemy, s16 x, s16 y);

		void drawArrow(Battler *battler);

		void enemyTurn();

		void pushAction(Battler *actor, Battler *receiver, Item *item);
		void processAction();
		void updateAction() { m_actions.back()->updateDamages(); }
		bool drawAction() { return m_actions.back()->drawDamages(); }
		void popAction() { m_actions.pop_back(); }
		bool actionStackEmpty() { return (m_actions.size() == 0); }

		void checkDead();

		void sortBattleActions();

		Actor *getActor(u8 id) { return m_actors[id].second; }
		Enemy *getEnemy(u8 id) { return m_enemies[id].second; }

		u8 getActorPos(u8 id) { return m_actors[id].first; }
		u8 getEnemyPos(u8 id) { return m_enemies[id].first; }

		std::pair<u8, Actor*> getNextActorPair(s8 v, s8 current);
		std::pair<u8, Enemy*> getNextEnemyPair(s8 v, s8 current);

		std::vector<std::pair<u8, Actor*>> actors() { return m_actors; }
		std::vector<std::pair<u8, Enemy*>> enemies() { return m_enemies; }

		void setBattleback(Image *battleback) { m_battleback = battleback; }

		void renderBattleback();

		u16 exp() const { return m_exp; }
		u16 gold() const { return m_gold; }

	private:
		std::vector<std::pair<u8, Actor*>> m_actors;
		std::vector<std::pair<u8, Enemy*>> m_enemies;

		u8 m_actorsCount;
		u8 m_enemiesCount;

		Image *m_battleback;

		std::vector<BattleAction*> m_actions;

		u16 m_exp;
		u16 m_gold;

		bool m_allowDefeat;
};

#endif // BATTLE_HPP_
