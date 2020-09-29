
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>

#include "Mouse.h"
#include "ResourceManager.h"
#include "EffectManager.h"

using namespace std;

void ScreenShot(string BmpName)
{
	HWND DesktopHwnd = GetDesktopWindow();
	RECT DesktopParams;
	HDC DevC = GetDC(DesktopHwnd);
	GetWindowRect(DesktopHwnd, &DesktopParams);
	DWORD Width = DesktopParams.right - DesktopParams.left;
	DWORD Height = DesktopParams.bottom - DesktopParams.top;

	DWORD FileSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (sizeof(RGBTRIPLE) + 1 * (Width*Height * 4));
	char *BmpFileData = (char*)GlobalAlloc(0x0040, FileSize);

	PBITMAPFILEHEADER BFileHeader = (PBITMAPFILEHEADER)BmpFileData;
	PBITMAPINFOHEADER  BInfoHeader = (PBITMAPINFOHEADER)&BmpFileData[sizeof(BITMAPFILEHEADER)];

	BFileHeader->bfType = 0x4D42; // BM
	BFileHeader->bfSize = sizeof(BITMAPFILEHEADER);
	BFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	BInfoHeader->biSize = sizeof(BITMAPINFOHEADER);
	BInfoHeader->biPlanes = 1;
	BInfoHeader->biBitCount = 24;
	BInfoHeader->biCompression = BI_RGB;
	BInfoHeader->biHeight = Height;
	BInfoHeader->biWidth = Width;

	RGBTRIPLE *Image = (RGBTRIPLE*)&BmpFileData[sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)];

	HDC CaptureDC = CreateCompatibleDC(DevC);
	HBITMAP CaptureBitmap = CreateCompatibleBitmap(DevC, Width, Height);
	SelectObject(CaptureDC, CaptureBitmap);
	BitBlt(CaptureDC, 0, 0, Width, Height, DevC, 0, 0, SRCCOPY | CAPTUREBLT);
	GetDIBits(CaptureDC, CaptureBitmap, 0, Height, Image, (LPBITMAPINFO)BInfoHeader, DIB_RGB_COLORS);

	DWORD Junk;
	HANDLE FH = CreateFileA(BmpName.c_str(), GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, 0, 0);
	WriteFile(FH, BmpFileData, FileSize, &Junk, 0);
	CloseHandle(FH);
	GlobalFree(BmpFileData);
}

int main() {
	srand(time(0));

	bool done = false, redraw = true, visible = false;
	bool ctrlHeld = false, mouseHeld = false;
	POINT mousePos; mousePos.x = mousePos.y = 0;

	//visible = true;

	RECT desktop;
	GetWindowRect(GetDesktopWindow(), &desktop);

	int screenWidth = desktop.right;
	int screenHeight = desktop.bottom;
	printf("Screen Width:%i  Screen Height:%i\n", screenWidth, screenHeight);


	if (!al_init()) {
		printf("Could not initialize allegro!\n");
		system("pause");
	}
	if (!al_init_image_addon()) {
		printf("Could not initialize image addon!\n");
		system("pause");
	}
	if (!al_init_primitives_addon()) {
		printf("Could not initialize audio addon!\n");
		system("pause");
	}
	if (!al_init_acodec_addon()) {
		printf("Could not initialize acodec addon!\n");
		system("pause");
	}
	if (!al_install_audio()) {
		printf("Could not install audio!\n");
		system("pause");
	}
	if (!al_reserve_samples(20)) {
		printf("Could not reserve samples!\n");
		system("pause");
	}


	al_install_keyboard();
	al_install_mouse();
	

	al_set_new_display_flags(ALLEGRO_NOFRAME);
	ALLEGRO_DISPLAY *display = al_create_display(screenWidth, screenHeight);
	al_set_window_title(display, "Super Click");
	ShowWindow(FindWindow(NULL, "Super Click"), SW_HIDE);
	al_hide_mouse_cursor(display);


	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	ALLEGRO_TIMER *timer = al_create_timer(1.0/60.0);

	ALLEGRO_BITMAP *desktopImage = al_load_bitmap("Test.jpg");


	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	//al_register_event_source(event_queue, al_get_display_event_source(display));


	ResourceManager *rm = new ResourceManager();
	Mouse *mouse = new Mouse();
	EffectManager *em = new EffectManager(rm);
	
	rm->AddBitmap("effects", al_create_bitmap(screenWidth, screenHeight));

	//rm->PlaySample("explosion1", 1);

	al_start_timer(timer);

	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER) {
			redraw = true;

			if (visible) {
				::SetWindowPos(FindWindow(NULL, "Super Click"), HWND_TOPMOST, 0, 0, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE);
				SetForegroundWindow(FindWindow(NULL, "Super Click"));
				SwitchToThisWindow(FindWindow(NULL, "Super Click"), true);

				mouse->Update(rm);
				em->Update();
				em->Cleanup();

				if (mouse->GetHit() && mouse->GetActive()) {
					mouse->SetActive(false);

					em->Explode(mouse->GetPos()->x, mouse->GetPos()->y);
				}

				
				if (visible && !mouse->GetActive() && em->GetSize() == 0) {
					em->UpdateTimer();

					if (em->GetTimer() == 0) {
						visible = false;
						cout << "Hiding display..." << endl;
						ShowWindow(FindWindow(NULL, "Super Click"), SW_HIDE);
					}
				}
			}

			if (!visible) {
				bool good = false;
				if (GetAsyncKeyState('S') != 0)
					ctrlHeld = true;
				else
					ctrlHeld = false;

				if (GetAsyncKeyState(VK_LBUTTON) == 0) {
					//cout << "Checking" << endl;
					//cout << ctrlHeld << " " << mouseHeld << endl;
					if (mouseHeld && ctrlHeld)
						good = true;
					mouseHeld = false;
				}
				else
					mouseHeld = true;

				

				if (good) {
					visible = !visible;
					if (visible) {
						GetCursorPos(mouse->GetPos());
						ScreenShot("Screenshot.jpg");

						al_set_target_bitmap(rm->GetImage("effects"));
						al_clear_to_color(al_map_rgba_f(0, 0, 0, 0));
						al_set_target_bitmap(al_get_backbuffer(display));

						ShowWindow(FindWindow(NULL, "Super Click"), SW_SHOW);
						::SetWindowPos(FindWindow(NULL, "Super Click"), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_SHOWWINDOW | SWP_NOSIZE);
						SetForegroundWindow(FindWindow(NULL, "Super Click"));
						SwitchToThisWindow(FindWindow(NULL, "Super Click"), true);

						al_destroy_bitmap(desktopImage);
						desktopImage = nullptr;
						desktopImage = al_load_bitmap("Screenshot.jpg");

						DeleteFileA("Screenshot.jpg");

						cout << "Done!" << endl;


						cout << "Showing display..." << endl;

						em->ResetTimer();
						mouse->Fall(mouse->GetPos()->x, mouse->GetPos()->y, rm);
					}
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			/**/
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			//mouse->Fall(ev.mouse.x, ev.mouse.y, rm);
			//mouse->GetPos()->x = ev.mouse.x;
			//mouse->GetPos()->y = ev.mouse.y;

			//em->Explode(mouse->GetPos()->x, mouse->GetPos()->y);
			//em->AddEffect(mouse->GetPos()->x, mouse->GetPos()->y, 2);
		}

		if (visible && redraw) {
			redraw = false;
			int shakeAmount = em->GetShakeAmount();

			//==============================
			ALLEGRO_TRANSFORM T;
			al_identity_transform(&T);
			if (shakeAmount > 0) {
				al_translate_transform(&T, float(rand() % shakeAmount - shakeAmount / 2), float(rand() % shakeAmount - shakeAmount / 2));
			}
			al_use_transform(&T);

			//=================================================
			al_clear_to_color(al_map_rgb(0, 0, 0));

			al_draw_bitmap(desktopImage, 0, 0, NULL);
			al_draw_bitmap(rm->GetImage("effects"), 0, 0, NULL);

			em->Draw();

			if (visible && !mouse->GetActive() && em->GetSize() == 0 && em->GetTimer() < 50) {
				al_set_target_bitmap(rm->GetImage("effects"));
				al_draw_filled_rectangle(0, 0, screenWidth, screenHeight, al_map_rgba_f(0, 0, 0, .075));
			}
			al_set_target_bitmap(al_get_backbuffer(display));

			mouse->Draw(rm->GetImage("mouse"));

			al_draw_filled_rectangle(0, 0, screenWidth, screenHeight, al_map_rgba_f(em->GetFlashAmount(), em->GetFlashAmount(), em->GetFlashAmount(), em->GetFlashAmount()));
			

			al_flip_display();
		}
	}

}