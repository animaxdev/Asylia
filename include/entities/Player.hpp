/*
 * =====================================================================================
 *
 *       Filename:  Player.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/03/2014 19:48:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef PLAYER_HPP_
#define PLAYER_HPP_

class Player : public Character {
	public:
		Player(std::string filename, s16 x, s16 y, u8 direction);
		~Player();
		
		void move();
		
		void action() {}
		void collisionAction() {}
		
		void addTeamMember(u16 id) { m_team.push_back(BattlerManager::actors[id]); }
		Actor *getTeamMember(u8 i) { return m_team[i]; }
		
		u16 teamSize() { return m_team.size(); }
		
	private:
		std::vector<Actor*> m_team;
};

#endif // PLAYER_HPP_
