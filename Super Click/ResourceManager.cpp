#include "ResourceManager.h"
#include "resource.h"

ResourceManager::ResourceManager() {
	int error = 0;

	error += this->LoadBitmapFromResource("explosion", IDB_PNG1);
	error += this->LoadBitmapFromResource("fireBig", IDB_PNG2);
	error += this->LoadBitmapFromResource("fire", IDB_PNG3);
	error += this->LoadBitmapFromResource("mouse", IDB_PNG4);
	error += this->LoadBitmapFromResource("smoke", IDB_PNG5);
	error += this->LoadBitmapFromResource("smoke2", IDB_PNG6);

	error += this->LoadSampleFromResource("falling", IDR_WAVE1);
	error += this->LoadSampleFromResource("hit", IDR_WAVE2);

	for (int i = 1; i < 10; i++)
		error += this->LoadSampleFromResource(string("explosion" + to_string(i)).c_str(), IDR_WAVE2 + i);
		

	if (error > 0) {
		printf("ERRORS LOADING!\n");
		system("pause");
	}

	printf("Loaded images and audio!\n");
}


ResourceManager::~ResourceManager() {

}


ALLEGRO_BITMAP *ResourceManager::GetImage(const char *name) {
	if (images[name])
		return this->images[name];
	else {
		printf("ERROR! IMAGE NOT FOUND\n");
		ALLEGRO_BITMAP *tmp = al_create_bitmap(16, 16);
		return tmp;
	}
}

void ResourceManager::PlaySample(const char * name, float speed) {
	printf("Playing '%s'\n", name);
	if (audio[name])
		al_play_sample(audio[name], 1, 0, speed, ALLEGRO_PLAYMODE_ONCE, NULL);
	else
		printf("ERROR! AUDIO NOT FOUND\n");
}


bool ResourceManager::LoadBitmap(const char *name, const char *file) {
	printf("Loading '%s' as '%s'\n", file, name);
	this->images[name] = al_load_bitmap(file);
	return (images[name] == NULL);
}

bool ResourceManager::LoadBitmapMemfile(const char * name, vector<unsigned char> file) {
	printf("Loading '%s'\n", name);

	unsigned char* a = &file[0];
	ALLEGRO_FILE *tmp = al_open_memfile(a, sizeof(a), "r");

	this->images[name] = al_load_bitmap_f(tmp, ".png");
	return (images[name] == NULL);
}

bool ResourceManager::LoadBitmapFromResource(const char *name, int id) {
	printf("Loading image resource '%i' as '%s'\n", id, name);
	HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(id), "PNG");
	HANDLE sndLaser = LoadResource(NULL, hResInfo);
	DWORD size = SizeofResource(NULL, hResInfo);

	unsigned char *sndRes = (unsigned char *)LockResource(sndLaser);
	ALLEGRO_FILE *file = al_open_memfile(sndRes, size, "r");

	this->images[name] = al_load_bitmap_f(file, ".png");
	UnlockResource(sndLaser);
	return (images[name] == NULL);
}

bool ResourceManager::LoadSample(const char *name, const char *file) {
	printf("Loading '%s' as '%s'\n", file, name);
	this->audio[name] = al_load_sample(file);
	return (audio[name] == NULL);
}

bool ResourceManager::LoadSampleMemfile(const char * name, unsigned char file[]) {
	printf("Loading '%s'\n", name);

	ALLEGRO_FILE *tmp = al_open_memfile(file, sizeof(file), "r");

	this->audio[name] = al_load_sample_f(tmp, ".wav");
	return (audio[name] == NULL);
}

bool ResourceManager::LoadSampleFromResource(const char * name, int id) {
	printf("Loading sound resource '%i' as '%s'\n", id, name);
	HRSRC hResInfo = FindResource(NULL, MAKEINTRESOURCE(id), "WAVE");
	HANDLE sndLaser = LoadResource(NULL, hResInfo);
	DWORD size = SizeofResource(NULL, hResInfo);

	unsigned char *sndRes = (unsigned char *)LockResource(sndLaser);
	ALLEGRO_FILE *file = al_open_memfile(sndRes, size, "r");

	this->audio[name] = al_load_sample_f(file, ".wav");
	UnlockResource(sndLaser);
	return (audio[name] == NULL);
}

void ResourceManager::AddBitmap(const char *name, ALLEGRO_BITMAP *bmp) {
	this->images[name] = bmp;
}