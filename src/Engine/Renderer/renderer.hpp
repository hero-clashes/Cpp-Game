#pragma once
#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <unordered_map>
class Renderer
{
public:
    int tile_size;
    Renderer(int tiles_wide, int tiles_tall,const char *path_bitmap, int tile_size);
    ~Renderer();
    void render_char(int x, int y, Rectangle *sprite,const Color *color,const Color *bkcol);
	void render_char_pro(int x, int y, Rectangle *sprite,const Color *color,const Color *bkcol,float size);
    void render_text(int x, int y, std::string text,const Color *color,const Color *bkcolor);
	void render_text_by_grid(int x, int y, std::string text,const Color *color,const Color *bkcolor);
	void render_text_by_grid_with_offest(int x, int y,int offset_x,int offset_y, std::string text,const Color *color,const Color *bkcolor);
	void render_frame(int x,int y, int width,int hight);
	void render_text_pro(int x,int y,std::string text, float size,int offset_x,int offset_y,const Color *color,const Color *bkcolor);
    void render_bar(int x,int y,int current_value,int max_value,int length,const Color *colorfilled, const Color *color_notfilled);
	void render_box(int x,int y,int width,int hight,const Color *color);
	void render_rec(int x,int y,int width,int hight,const Color *color);
	void render_rec_with_title(int x,int y,int width,int hight,const Color *color,std::string title,const Color *text_color,const Color *text_color_bks);
	std::wstring Convert(const std::string& value) const;
    Rectangle glyh[16 * 16];
	Font font;
private:
    Texture2D texture;
    std::unordered_map<wchar_t,int> utfmap;
};
    //stuff for utf8 handling
	static const wchar_t kSurrogateHighStart	= 0xD800;
	static const wchar_t kSurrogateHighEnd		= 0xDBFF;
	static const wchar_t kUnicodeMaxBmp			= 0xFFFF;

	// Number of trailing bytes that are supposed to follow the first byte
	// of a UTF-8 sequence
	inline const uint8_t kTrailingBytesForUTF8[256] =
	{
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
		3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
	};

	// Magic values subtracted from a buffer value during UTF8 conversion.
	// This table contains as many values as there might be trailing bytes
	// in a UTF-8 sequence.
	inline const uint32_t kOffsetsFromUTF8[6] =
	{
		0x00000000UL,
		0x00003080UL,
		0x000E2080UL,
		0x03C82080UL,
		0xFA082080UL,
		0x82082080UL
	};

	inline const wchar_t kReplacementChar = 0x1A; // ASCII 'replacement' character