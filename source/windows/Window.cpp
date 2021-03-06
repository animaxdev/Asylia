/*
 * =====================================================================================
 *
 *       Filename:  Window.cpp
 *
 *    Description:
 *
 *        Created:  22/03/2014 00:33:17
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include "Font.hpp"
#include "ResourceHelper.hpp"
#include "Window.hpp"

Window::Window(s16 x, s16 y, u16 width, u16 height) {
	m_x = x;
	m_y = y;

	m_width = width;
	m_height = height;

	m_cursor = gk::IntRect(0, 0, 0, 0);
}

void Window::drawCursor(s16 x, s16 y, u16 width, u16 height) {
	ResourceHelper::getImage("interface").setAlphaMod(abs(int(SDL_GetTicks() / 4 % 255 - 128)) + 127);

	ResourceHelper::getImage("interface").render(x, y, width, height, 132, 68, 23, 23);

	ResourceHelper::getImage("interface").render(x, y, 1, height, 128, 64, 1, 32);
	ResourceHelper::getImage("interface").render(x + width - 1, y, 1, height, 159, 64, 1, 32);

	ResourceHelper::getImage("interface").render(x, y, width, 1, 129, 64, 31, 1);
	ResourceHelper::getImage("interface").render(x, y + height - 1, width, 1, 129, 95, 31, 1);

	ResourceHelper::getImage("interface").setAlphaMod(255);
}

void Window::drawWindow(s16 x, s16 y, u16 width, u16 height) {
	ResourceHelper::getImage("interface").setAlphaMod(225);
	ResourceHelper::getImage("interface").render(x + 1, y + 1, width - 2, height - 2, 0, 0, 128, 128);
	ResourceHelper::getImage("interface").setAlphaMod(255);

	ResourceHelper::getImage("interface").render(x, y, 3, 3, 128, 0, 3, 3);
	ResourceHelper::getImage("interface").render(x + width - 3, y, 3, 3, 189, 0, 3, 3);
	ResourceHelper::getImage("interface").render(x, y + height - 3, 3, 3, 128, 61, 3, 3);
	ResourceHelper::getImage("interface").render(x + width - 3, y + height - 3, 3, 3, 189, 61, 3, 3);

	ResourceHelper::getImage("interface").render(x + 3, y, width - 6, 3, 132, 0, 58, 3);
	ResourceHelper::getImage("interface").render(x, y + 3, 3, height - 6, 128, 3, 3, 58);
	ResourceHelper::getImage("interface").render(x + 3, y + height - 3, width - 6, 3, 132, 61, 58, 3);
	ResourceHelper::getImage("interface").render(x + width - 3, y + 3, 3, height - 6, 189, 3, 3, 58);
}

void Window::draw(bool cursor) {
	drawWindow(m_x, m_y, m_width, m_height);

	if(m_cursor.width > 0 && cursor) {
		drawCursor(16 + m_x + m_cursor.x, 16 + m_y + m_cursor.y, m_cursor.width, m_cursor.height);
	}
}

void Window::printStat(s16 x, s16 y, std::string statName, s32 statValue, u16 nameWidth, u16 x2, u16 max) {
	Image statImg;

	ResourceHelper::getFont("default").printScaled(statName.c_str(), m_x + x, m_y + y, nameWidth, 28, FONT_LARGE, Color::System);

	if(max == 0) ResourceHelper::getFont("default").printToImage(std::to_string(statValue).c_str(), m_x + x2, m_y + y, &statImg, FONT_LARGE);
	else ResourceHelper::getFont("default").printToImage(std::string(std::to_string(statValue) + "/" + std::to_string(max)).c_str(), m_x + x2, m_y + y, &statImg, FONT_LARGE);

	statImg.render(statImg.posRect().x - statImg.width());
}

void Window::printName(Battler *battler, s16 x, s16 y, u16 width) {
	ResourceHelper::getFont("default").printScaled(battler->name().c_str(), m_x + x, m_y + y, width, 28, FONT_LARGE);
}

void Window::printState(Battler *battler, s16 x, s16 y, u16 width) {
	ResourceHelper::getFont("default").printScaled(battler->getStateString().c_str(), m_x + x, m_y + y, width, 28, FONT_LARGE);
}

void Window::printLevel(Battler *battler, s16 x, s16 y, s16 x2) {
	printStat(x, y, _t("Lv"), battler->level(), 25, x2);
}

void Window::printHP(Battler *battler, s16 x, s16 y, s16 x2, bool onMaximum) {
	printStat(x, y, _t("HP"), battler->hp(), 60, x2, (onMaximum)?(battler->basehp()):(0));
}

void Window::printSP(Battler *battler, s16 x, s16 y, s16 x2, bool onMaximum) {
	printStat(x, y, _t("SP"), battler->sp(), 60, x2, (onMaximum)?(battler->basesp()):(0));
}

void Window::printExp(Battler *battler, s16 x, s16 y, s16 x2, bool onMaximum) {
	printStat(x, y, _t("EXP"), battler->exp(), 60, x2, (onMaximum)?(battler->exp() + battler->expRemainingToLevelUp()):(0));
}

void Window::drawBattler(Battler *battler, s16 x, s16 y) {
	battler->image()->render(x, y);
}

void Window::printItem(Item *item, u16 count, s16 x, s16 y, u16 width) {
	Image countImg, itemImg;

	item->thumbnail().render(m_x + x, m_y + y);

	if(count != 0) {
		ResourceHelper::getFont("default").printToImage(std::to_string(count).c_str(), m_x + x - 16 + width, m_y + y, &countImg, FONT_LARGE);
		countImg.render(countImg.posRect().x - countImg.width());
	}

	ResourceHelper::getFont("default").printScaledToImage(item->name().c_str(), m_x + x + 28, m_y + y, width - countImg.width(), 32, &itemImg, FONT_LARGE);

	if(m_y + y < m_y) {
		itemImg.render(-1, m_y + 4, 0, itemImg.height() - (y + 32 - m_y), -1, m_y - y + 4, 0, itemImg.height() - (y + 32 - m_y));
	}
	else if(m_y + y + 32 > m_y + m_height) {
		itemImg.render(-1, m_y + y, 0, m_height - y - 4, -1, -1, 0, m_height - y - 4);
	} else {
		itemImg.render(-1, -1, 0, 0, -1, -1, 0, 0);
	}
}

