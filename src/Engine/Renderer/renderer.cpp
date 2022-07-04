#include "renderer.hpp"
Renderer::Renderer(int tiles_wide, int tiles_tall,const char *path_bitmap, int tile_size) : tile_size(tile_size)
{

	const int w_width = tiles_wide * tile_size;
    const int w_height = tiles_tall * tile_size;

    InitWindow(w_width, w_height, "Enough Words");
	
	//Load image at specified path
	Image loadedimage = LoadImage(path_bitmap);
	ImageFormat(&loadedimage, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	auto coltodel = Color{255,0,255,255};
	ImageColorReplace(&loadedimage,coltodel,BLANK);
	texture = LoadTextureFromImage(loadedimage);
	UnloadImage(loadedimage);
	//Get Glyph's UV's
	for (int x = 0; x < 16; x++)
	{
		for (int y = 0; y < 16; y++)
		{
			glyh[x + y * 16].x = static_cast<float>(x * tile_size);
			glyh[x + y * 16].y = static_cast<float>(y * tile_size);
			glyh[x + y * 16].width = static_cast<float>(tile_size);
			glyh[x + y * 16].height = static_cast<float>(tile_size);
		};
	};
	//Fill the utfmap
		const int TCOD_CHARMAP_CP437[256] = {
		0x0000, 0x263A, 0x263B, 0x2665, 0x2666, 0x2663, 0x2660, 0x2022,
		0x25D8, 0x25CB, 0x25D9, 0x2642, 0x2640, 0x266A, 0x266B, 0x263C,
		0x25BA, 0x25C4, 0x2195, 0x203C, 0x00B6, 0x00A7, 0x25AC, 0x21A8,
		0x2191, 0x2193, 0x2192, 0x2190, 0x221F, 0x2194, 0x25B2, 0x25BC,
		0x0020, 0x0021, 0x0022, 0x0023, 0x0024, 0x0025, 0x0026, 0x0027,
		0x0028, 0x0029, 0x002A, 0x002B, 0x002C, 0x002D, 0x002E, 0x002F,
		0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037,
		0x0038, 0x0039, 0x003A, 0x003B, 0x003C, 0x003D, 0x003E, 0x003F,
		0x0040, 0x0041, 0x0042, 0x0043, 0x0044, 0x0045, 0x0046, 0x0047,
		0x0048, 0x0049, 0x004A, 0x004B, 0x004C, 0x004D, 0x004E, 0x004F,
		0x0050, 0x0051, 0x0052, 0x0053, 0x0054, 0x0055, 0x0056, 0x0057,
		0x0058, 0x0059, 0x005A, 0x005B, 0x005C, 0x005D, 0x005E, 0x005F,
		0x0060, 0x0061, 0x0062, 0x0063, 0x0064, 0x0065, 0x0066, 0x0067,
		0x0068, 0x0069, 0x006A, 0x006B, 0x006C, 0x006D, 0x006E, 0x006F,
		0x0070, 0x0071, 0x0072, 0x0073, 0x0074, 0x0075, 0x0076, 0x0077,
		0x0078, 0x0079, 0x007A, 0x007B, 0x007C, 0x007D, 0x007E, 0x007F,
		0x00C7, 0x00FC, 0x00E9, 0x00E2, 0x00E4, 0x00E0, 0x00E5, 0x00E7,
		0x00EA, 0x00EB, 0x00E8, 0x00EF, 0x00EE, 0x00EC, 0x00C4, 0x00C5,
		0x00C9, 0x00E6, 0x00C6, 0x00F4, 0x00F6, 0x00F2, 0x00FB, 0x00F9,
		0x00FF, 0x00D6, 0x00DC, 0x00A2, 0x00A3, 0x00A5, 0x20A7, 0x0192,
		0x00E1, 0x00ED, 0x00F3, 0x00FA, 0x00F1, 0x00D1, 0x00AA, 0x00BA,
		0x00BF, 0x2310, 0x00AC, 0x00BD, 0x00BC, 0x00A1, 0x00AB, 0x00BB,
		0x2591, 0x2592, 0x2593, 0x2502, 0x2524, 0x2561, 0x2562, 0x2556,
		0x2555, 0x2563, 0x2551, 0x2557, 0x255D, 0x255C, 0x255B, 0x2510,
		0x2514, 0x2534, 0x252C, 0x251C, 0x2500, 0x253C, 0x255E, 0x255F,
		0x255A, 0x2554, 0x2569, 0x2566, 0x2560, 0x2550, 0x256C, 0x2567,
		0x2568, 0x2564, 0x2565, 0x2559, 0x2558, 0x2552, 0x2553, 0x256B,
		0x256A, 0x2518, 0x250C, 0x2588, 0x2584, 0x258C, 0x2590, 0x2580,
		0x03B1, 0x00DF, 0x0393, 0x03C0, 0x03A3, 0x03C3, 0x00B5, 0x03C4,
		0x03A6, 0x0398, 0x03A9, 0x03B4, 0x221E, 0x03C6, 0x03B5, 0x2229,
		0x2261, 0x00B1, 0x2265, 0x2264, 0x2320, 0x2321, 0x00F7, 0x2248,
		0x00B0, 0x2219, 0x00B7, 0x221A, 0x207F, 0x00B2, 0x25A0, 0x00A0,
	};
	utfmap.reserve(256);
	for(int i = 0;i<256;i++){
		utfmap[TCOD_CHARMAP_CP437[i]] = i;
	};
	SetShapesTexture(texture, glyh[219]);
};
Renderer::~Renderer()
{
	UnloadTexture(texture);
};
void Renderer::render_char(int x, int y, Rectangle *sprite,const Color *color,const Color *bkcol)
{
	if(bkcol!=nullptr) DrawTextureRec(texture, glyh[219],Vector2{static_cast<float>(x), static_cast<float>(y)}, *bkcol);
	//Set rendering space and render to screen
	if(color!=nullptr) DrawTextureRec(texture, *sprite, Vector2{static_cast<float>(x), static_cast<float>(y)}, *color);
}

void Renderer::render_char_pro(int x, int y, Rectangle *sprite,const Color *color,const Color *bkcol,float size) 
{
	Rectangle dest;
	dest.height = tile_size * size;
	dest.width = tile_size * size;
	dest.x = static_cast<float>(x);
	dest.y = static_cast<float>(y);
	if (bkcol != nullptr)
		DrawTexturePro(texture, glyh[219], dest, {0, 0}, 0, *bkcol);
	// Set rendering space and render to screen
	if (color != nullptr)
		DrawTexturePro(texture, *sprite, dest, {0, 0}, 0, *color);
};
void Renderer::render_text(int x, int y, std::string text,const Color *color,const Color *bkcolor)
{
	auto conv_text = Convert(text);
	for (int i = 0; i < conv_text.size(); i++)
	{
		if(conv_text[i] == L'\n'){ 
			y+= tile_size;
			x-= (i+1) * tile_size;
			continue;
		};
		render_char(x + i * tile_size, y, &glyh[utfmap[conv_text[i]]], color, bkcolor);
	}
}
std::wstring Renderer::Convert(const std::string& value) const
{
	std::wstring result;

	size_t index = 0;
	while (index < value.length())
	{
		size_t extraBytesToRead = kTrailingBytesForUTF8[(uint8_t)value[index]];
		if (index+extraBytesToRead >= value.length())
		{
			// Stop here
			return result;
		}

		// TODO: Do UTF-8 check

		uint32_t ch = 0;
		for (int i=static_cast<int>(extraBytesToRead); i>=0; i--)
		{
			ch += (uint8_t)value[index++];
			if (i > 0) ch <<= 6;
		}
		ch -= kOffsetsFromUTF8[extraBytesToRead];

		if (ch <= kUnicodeMaxBmp)
		{
			// Target is a character <= 0xFFFF
			if (ch >= kSurrogateHighStart && ch <= kSurrogateHighEnd)
			{
				result.push_back(kReplacementChar);
			}
			else
			{
				result.push_back((wchar_t)ch); // Normal case
			}
		}
		else // Above 0xFFFF
		{
			result.push_back(kReplacementChar);
		}
	}

	return result;
}
void Renderer::render_text_by_grid(int x, int y, std::string text,const Color *color,const Color *bkcolor)
{
	render_text(x*tile_size,y*tile_size,text,color,bkcolor);
}

void Renderer::render_text_by_grid_with_offest(int x, int y,int offset_x,int offset_y, std::string text,const Color *color,const Color *bkcolor) 
{
	render_text((x*tile_size)+offset_x,(y*tile_size)+offset_y,text,color,bkcolor);
}

void Renderer::render_frame(int x,int y, int width,int hight) 
{
	
}

void Renderer::render_text_pro(int x,int y,std::string text, float size,int offset_x,int offset_y,const Color *color,const Color *bkcolor) 
{
	x = tile_size * x + offset_x;
	y = tile_size * y + offset_y;
	auto conv_text = Convert(text);
	for (int i = 0; i < conv_text.size(); i++)
	{
		render_char_pro(static_cast<int>(x + i * (tile_size * size)), y, &glyh[utfmap[conv_text[i]]], color, bkcolor,size);
	}
}

void Renderer::render_bar(int x, int y, int current_value, int max_value, int length, const Color *colorfilled, const Color *color_notfilled)
{
	//use included raylibs one they are better
	int filled_length = static_cast<int>(((float)current_value / max_value)*length);

	for (int i = 0; i < length; i++)
	{
		if (i <= filled_length)
		{
			render_char((x + i) * (tile_size), y * (tile_size), &glyh[219], nullptr, colorfilled);
		}
		else
		{
			render_char((x + i) * (tile_size), y * (tile_size), &glyh[219], nullptr, color_notfilled);
		};
	};
}

void Renderer::render_box(int x,int y,int width,int hight,const Color *color) 
{
	//use included raylibs one they are better
	DrawTexturePro(texture,glyh[219],{(float)x*tile_size,(float)y*tile_size,(float)(x+width)*tile_size,(float)(y+hight)*tile_size},{0,0},0,*color);
}

void Renderer::render_rec(int x,int y,int width,int hight,const Color *color) 
{
	DrawRectangleLines((tile_size/2)+x*tile_size, (tile_size/2)+y*tile_size, (width*tile_size)-tile_size,(hight*tile_size)-tile_size , *color);
}

void Renderer::render_rec_with_title(int x,int y,int width,int hight,const Color *color,std::string title,const Color *text_color,const Color *text_color_bk) 
{
	if(width<title.size())width = static_cast<int>(title.size());
	render_rec(x,y,width,hight,color);
	render_text_by_grid(static_cast<int>((x+width-title.size())/2),y,title,text_color,text_color_bk);
}