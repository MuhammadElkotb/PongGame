#include <stdio.h>
#include <raylib.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



#define WIDTH 1600
#define HEIGHT 900
#define ballheight 140





int main()
{
	InitWindow(WIDTH, HEIGHT, "PONG");
	
	SetTargetFPS(60);
	
	InitAudioDevice();

	Music jump = LoadMusicStream("C:\\Users\\Muham\\Downloads\\jump.wav");

	Texture2D pause = LoadTexture("C:\\Users\\Muham\\Desktop\\prject\\resources\\pause.png");
	

	


	while (!(WindowShouldClose())) {
		UpdateMusicStream(jump);
		static float yax1 = HEIGHT - ballheight;
		static float yax2 = HEIGHT - ballheight;
		static float velx = 10;
		static float vely = 10;
		static float poscircx = WIDTH / 2;
		static float poscircy = HEIGHT / 2;
		static float circtime = 0.0f;
		static float timeplayed;
		static float timer2 = 0.0f;
		static bool playgame=true;
		static bool red;
		static bool blue;
		static bool redcol;
		static bool bluecol;

		

		
	
		timeplayed = GetMusicTimePlayed(jump) / GetMusicTimeLength(jump);


		if (IsKeyReleased(KEY_SPACE) && playgame==true) {
			playgame = false;
			
		}
		if (playgame == false && IsKeyReleased(KEY_ENTER)) {
			playgame = true;
		}
		
		
		


		Rectangle rect1 = { 0, yax1, 10, ballheight };
		Rectangle rect2 = { WIDTH-10, yax2, 10, ballheight };
		Vector2 vectcirc = { poscircx, poscircy };
	
		timer2 += GetFrameTime();
		circtime += GetFrameTime();
		if (CheckCollisionPointRec(vectcirc, rect2)) {
			red = true;
			blue = false;
			
		}
		if (CheckCollisionPointRec(vectcirc, rect1)) {
			blue = true;
			red = false;
			
		}
		
			
			

			if (playgame) {
				if (poscircy >= HEIGHT - 8) {

					vely = -vely;
				}

				if (red) {
					velx = -velx;
					redcol = red;
					red = false;
				
					PlayMusicStream(jump);

				}
				if (poscircy <= 8) {

					vely = -vely;
				}

				if (blue) {
					velx = (-velx);
					bluecol = blue;
					blue = false;
					
					PlayMusicStream(jump);

				}
				if (timeplayed == 0) {
					StopMusicStream(jump);
				}

				if (poscircx <= 0 || poscircx >= WIDTH) {
					poscircx = WIDTH / 2;
					poscircy = HEIGHT / 2;
					timer2 = 0;
					vely = -vely;
					velx = -velx;



				}
				if (timer2 > 1) {
					if (circtime > 0.01f) {
						circtime = 0;
						poscircx += velx;
						poscircy += vely;
					}

				}
			}
		
		
		
			if (playgame == true) {

				if (IsKeyDown(KEY_W)) {

					yax1 -= 10;
				}
				if (IsKeyDown(KEY_S)) {

					yax1 += 10;
				}
				if (yax1 < 0) {
					yax1 = 0;
				}
				if (yax1 > HEIGHT - ballheight) {
					yax1 = HEIGHT - ballheight;
				}
				if (IsKeyDown(KEY_UP)) {

					yax2 -= 10;
				}
				if (IsKeyDown(KEY_DOWN)) {

					yax2 += 10;
				}
				if (yax2 < 0) {
					yax2 = 0;
				}
				if (yax2 > HEIGHT - ballheight) {
					yax2 = HEIGHT - ballheight;
				}
			}
	
		if (playgame == true) {
			ClearBackground(BLACK);
		}
		else {
			ClearBackground(DARKGRAY);
		}
		
			BeginDrawing();
		
		
		
			
			
		if (!playgame) {
				DrawTexture(pause, WIDTH-1140 , HEIGHT-600, DARKGRAY);
		}
		DrawRectangleRec(rect1, BLUE);
		DrawRectangleRec(rect2, RED);
		
		if (redcol) {
			DrawCircleV(vectcirc, 8, RED);
			
		}
		if (bluecol) {
			DrawCircleV(vectcirc, 8, BLUE);
		
		}
		if(!bluecol && !redcol)  {
			DrawCircleV(vectcirc, 8, WHITE);
		}
		
		
		


		EndDrawing();

		


	}

	UnloadMusicStream(jump);
	CloseAudioDevice();
	CloseWindow();
	
}