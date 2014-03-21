/*
 * =====================================================================================
 *
 *       Filename:  Map.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  14/03/2014 22:40:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef MAP_HPP_
#define MAP_HPP_

class Map {
	public:
		Map(const char *filename, u16 x, u16 y, u16 area, u8 layers, u16 tilesetID);
		~Map();
		
		void loadTile(u16 tileX, u16 tileY, u8 layer);
		void load();
		
		void render();
		void renderOverlay();
		
		s16 getTile(u16 tileX, u16 tileY, u16 layer);
		
		Tileset *tileset() const { return m_tileset; }
		
		u8 layers() const { return m_layers; }
		
	private:
		Tileset *m_tileset;
		
		u16 m_x;
		u16 m_y;
		
		u16 m_width;
		u16 m_height;
		
		u16 m_area;
		
		u8 m_layers;
		s16 **m_data;
		
		SDL_Texture **m_layersTex;
		Uint32 m_pixelFormat;
};

#endif // MAP_HPP_
