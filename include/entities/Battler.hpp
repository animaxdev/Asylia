/*
 * =====================================================================================
 *
 *       Filename:  Battler.hpp
 *
 *    Description:
 *
 *        Created:  22/04/2014 19:29:30
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#ifndef BATTLER_HPP_
#define BATTLER_HPP_

#include <string>

#include "Image.hpp"
#include "Skill.hpp"
#include "Sprite.hpp"
#include <gk/core/IntTypes.hpp>

class Battler {
	public:
		Battler(const Battler &battler);
		Battler(const std::string &name, const std::string &appearance, u8 level);
		~Battler();

		void calculateAllStats(u16 agi, u16 vit, u16 dex, u16 str, u16 wis, u16 intell);

		void blink();

		void kill();

		const std::string &name() const { return m_name; }

		Image *image() const { return m_image; }

		Sprite *sprite() const { return m_sprite; }

		u8 level() const { return m_level; }

		s16 hp() const { return m_hp; }
		s16 sp() const { return m_sp; }

		u16 basehp() const { return m_basehp; }
		u16 basesp() const { return m_basesp; }

		u16 atk() const { return m_atk; }
		u16 def() const { return m_def; }

		u16 totalAtk() const { return m_atk; }
		u16 totalDef() const { return m_def; }

		u8 state() const { return (u8)m_state; }

		u16 exp() const { return m_exp; }

		void setPosition(s16 x, s16 y) { m_image->setPosRect(x, y, m_image->width(), m_image->height()); }

		void hurt(u16 damages) { m_hp -= damages; if(m_hp < 0) m_hp = 0; }
		void heal(u16 p = 100) { m_hp += s16(p / 100 * m_basehp); }

		std::string getStateString();

		void attack(Battler *battler, Skill *skill);

		enum State {
			Normal
		};

		u8 type() const { return m_type; }

		enum Type {
			TypeNone,
			TypeActor,
			TypeEnemy
		};

		u16 growAgi(u16 agi, u16 level) { return agi + level * 0.30 * agi; }
		u16 growVit(u16 vit, u16 level) { return vit + level * 0.40 * vit; }
		u16 growDex(u16 dex, u16 level) { return dex + level * 0.36 * dex; }
		u16 growStr(u16 str, u16 level) { return str + level * 0.40 * str; }
		u16 growWis(u16 wis, u16 level) { return wis + level * 0.38 * wis; }
		u16 growInt(u16 intell, u16 level) { return intell + level * 0.38 * intell; }

		u16 speed() { return 2 * m_agi + m_vit; }

		u16 expGivenIfKilled() { return 40 * m_level + 1 + rand() % int(0.20 * (40 * std::exp(m_level) + 1)); }
		u16 goldGivenIfKilled() { return 40 * m_level + 1 + rand() % int(0.15 * (40 * m_level + 1)); }

		s16 expRemainingToLevelUp() { return m_level * 656 - m_exp; }

		void levelUp();

		void checkLevelUp() { if(expRemainingToLevelUp() < 0) levelUp(); }

		void gainExp(u16 value) { m_exp += value; }

	protected:
		std::string m_name;

		Image *m_image;

		Sprite *m_sprite;

		u8 m_level;
		u16 m_exp;

		s16 m_hp;
		s16 m_sp;

		u16 m_basehp;
		u16 m_basesp;

		u16 m_atk;
		u16 m_def;

		u16 m_agi;
		u16 m_vit;
		u16 m_dex;
		u16 m_str;
		u16 m_wis;
		u16 m_int;

		u8 m_state;

		u8 m_type;
};

#endif // BATTLER_HPP_
