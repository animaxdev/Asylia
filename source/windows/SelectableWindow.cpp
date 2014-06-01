/*
 * =====================================================================================
 *
 *       Filename:  SelectableWindow.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  22/03/2014 00:48:20
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include "Asylia.hpp"

SelectableWindow::SelectableWindow(s16 x, s16 y, u16 width, u16 height) : Window(x, y, width, height) {
	m_itemMax = 1;
	m_columnMax = 1;
	
	m_pos = -1;
	
	m_scroll = 0;
	
	m_infoWindow = NULL;
}

SelectableWindow::~SelectableWindow() {
	if(m_infoWindow) delete m_infoWindow;
}

void SelectableWindow::updateCursor() {
	u16 x, y, cursorWidth;
	
	cursorWidth = m_width / m_columnMax - 32;
	x = m_pos % m_columnMax * (cursorWidth + 32);
	y = m_pos / m_columnMax * 32 - m_scroll * 32;
	
	m_cursor = Rectangle(x, y, cursorWidth, 32);
}

void SelectableWindow::update() {
	Window::update();
	
	u8 rowMax = m_height / 32 - 1;
	
	if(Keyboard::isKeyPressedWithDelay(Keyboard::GameUp, 150)) {
		if(m_pos - m_columnMax >= 0) {
			m_pos -= m_columnMax;
			Sound::Effect::play(Sound::Effect::move);
		}
		else if(m_columnMax == 1) {
			m_pos = m_itemMax - 1;
			Sound::Effect::play(Sound::Effect::move);
		}
		if(m_pos / m_columnMax < m_scroll) m_scroll--; 
	}
	
	if(Keyboard::isKeyPressedWithDelay(Keyboard::GameDown, 150)) {
		if(m_pos + m_columnMax < m_itemMax) {
			m_pos += m_columnMax;
			Sound::Effect::play(Sound::Effect::move);
		}
		else if(m_columnMax == 1) {
			m_pos = 0;
			Sound::Effect::play(Sound::Effect::move);
		}
		if(m_pos / m_columnMax >= rowMax + m_scroll) m_scroll++; 
	}
	
	if(Keyboard::isKeyPressedWithDelay(Keyboard::GameLeft, 150)) {
		if(m_pos > 0 && m_columnMax > 1) {
			m_pos--;
			Sound::Effect::play(Sound::Effect::move);
		}
		if(m_pos / m_columnMax < m_scroll) m_scroll--; 
	}
	
	if(Keyboard::isKeyPressedWithDelay(Keyboard::GameRight, 150)) {
		if(m_pos < m_itemMax - 1 && m_columnMax > 1) {
			m_pos++;
			Sound::Effect::play(Sound::Effect::move);
		}
		if(m_pos / m_columnMax >= rowMax + m_scroll) m_scroll++; 
	}
	
	updateCursor();
}
