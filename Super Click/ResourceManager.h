#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_memfile.h>

#include <unordered_map>
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

class ResourceManager
{
	unordered_map<string, ALLEGRO_BITMAP *> images;
	unordered_map<string, ALLEGRO_SAMPLE *> audio;

public:
	ResourceManager();
	~ResourceManager();

	ALLEGRO_BITMAP *GetImage(const char *name);
	void PlaySample(const char *name, float speed);
	
	bool LoadBitmap(const char *name, const char *file);
	bool LoadBitmapMemfile(const char *name, vector<unsigned char> file);
	bool LoadBitmapFromResource(const char *name, int id);

	bool LoadSample(const char *name, const char *file);
	bool LoadSampleMemfile(const char *name, unsigned char file[]);
	bool LoadSampleFromResource(const char *name, int id);

	void AddBitmap(const char *name, ALLEGRO_BITMAP *bmp);
};

