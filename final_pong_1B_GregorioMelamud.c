/*******************************************************************************************
*
*   raylib FINAL PONG - CANNONG
*   Developed by [GREGORIO MELAMUD]
*
*   This example has been created using raylib 1.6 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
********************************************************************************************/

#include "raylib.h"

#define LEADGRAY  (Color){ 26, 20, 60, 255 }

#define ENCHANTEDRED  (Color){ 229, 108, 143, 255 }
#define ENCHANTEDBLUE  (Color){ 115, 108, 229, 255 }

#define HEAVYRED  (Color){ 234, 0, 67, 255 }
#define SUPERBLUE (Color){ 50, 0, 234, 255 }

#define BLOODYRED (Color){ 153, 0, 44, 255 }
#define DEPTBLUE  (Color){ 20, 0, 153, 255 }

#define ALMOSTRED  (Color){ 76, 0, 22, 255 }
#define LONELYBLUE (Color){ 5,0, 76, 255 }

enum  {LOGO = 0, TITLE, MENU, GAMEPLAY, ENDING};

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
	
	/*int screenWidth = 800;
    int screenHeight = 450;
    
    InitWindow(screenWidth, screenHeight, "FINAL PONG");
    
    InitAudioDevice();
    
    GameScreen currentScreen = LOGO;*/
	
	
    int screenWidth = 1280;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "raylib [core] CANNONG");
	
	InitAudioDevice();
    
	// TODO: Declare and load textures, spritefonts, sounds, music
	
	//Textures
	
    Texture2D player = LoadTexture("resources/player.png");
    Texture2D enemy = LoadTexture("resources/enemy.png");
    Texture2D eyes2 = LoadTexture("resources/eyes2.png");
    Texture2D eyes1 = LoadTexture("resources/eyes1.png");
    Texture2D moss = LoadTexture("resources/moss.png");
    Texture2D hud = LoadTexture("resources/hud.png");
    Texture2D sea = LoadTexture("resources/sea.png");
    Texture2D waves = LoadTexture("resources/waves.png");
    Texture2D logo = LoadTexture("resources/logo.png");
    Texture2D cannong = LoadTexture("resources/cannong.png");
    Texture2D title = LoadTexture("resources/title.png");
    Texture2D nubes = LoadTexture("resources/nubes.png");
    Texture2D neblina = LoadTexture("resources/neblina.png");
    Texture2D brillo = LoadTexture("resources/brillo.png");
	Texture2D menu = LoadTexture("resources/menu.png");
	Texture2D nubesmenu = LoadTexture("resources/nubesmenu.png");
	Texture2D barefect = LoadTexture("resources/barefect.png");
	Texture2D oldefect = LoadTexture("resources/oldefect.png");
	Texture2D bardownefect = LoadTexture("resources/bardownefect.png");
	Texture2D table = LoadTexture("resources/table.png");
	
	//Fonts
	
	SpriteFont savagefont = LoadSpriteFont("resources/savage.png");
	SpriteFont swampfont = LoadSpriteFont("resources/swamp.png");
    
	//Sounds
	
	Sound placFxWav = LoadSound("resources/placfx.wav");
	Sound boatFxWav = LoadSound("resources/boatfx.wav");
    Sound hitFxWav = LoadSound("resources/hitfx.wav");
	Sound swordFxWav = LoadSound("resources/swordfx.wav");
	Sound woarghFxWav = LoadSound("resources/woarghfx.wav");
	Sound winFxWav = LoadSound("resources/winfx.wav");
	Sound loseFxWav = LoadSound("resources/losefx.wav");
	Sound goFxWav = LoadSound("resources/gofx.wav");
	
	//Music
	
    Music titlemusic = LoadMusicStream("resources/titlemusic.ogg");
    
    /* NOTE: Here there are some useful variables...
    Rectangle player;
    int playerSpeedY;
    int playerLife;
    
    Rectangle enemy;
    int enemySpeedY;
    int enemyLife;
    
    Vector2 ballPosition;
    Vector2 ballSpeed;
    int ballRadius;

    int framesCounter = 0;      // General pourpose frames counter
    int gameResult = -1;        // 0 - Loose, 1 - Win, -1 - Not defined
	
	// NOTE: Use at least the following resources:
    //       - 4 textures (background, player, enemy, ball)
    //       - 2 sprite fonts (time counter, game messages)
    //       - 5 sounds (logo, start, ballhit, win, loose)
    //       - 1 music (game music)*/
    
    int currentScreen = LOGO; //0-logo, 1 tittle, 2 menu, 3 gameplay, 4 ending screen
    //gamescreen currentscreen = logo;
    int scrolling = 0;
    int framesCounter = 0;
    int elementPositionY = -125;        
    
	Color playerlifecolor = ENCHANTEDBLUE;
	Color enemylifecolor = ENCHANTEDRED;
	
    Rectangle playerlife = { 0.0f, 132.0f, 464.0f, 28.0f };
    Rectangle enemylife = { 816.0f, 132.0f, 464.0f, 28.0f };
    
    Rectangle playerframe  = {0, 0, player.width, player.height};
    float playerSpeedY = 3.5f;
    float playerPositionY = screenHeight/2;
    float playerPositionX = 60.0f;
    
    Rectangle enemyframe = {0, 0, enemy.width, enemy.height};
    float enemySpeed = 3.5f;
    float enemyPositionY = screenHeight/2;
    float enemyPositionX = screenWidth - enemy.width - 60;
    float enemyVision = screenWidth - 600;
    
	Rectangle timingframe  = {460, 240, 80, 80};
	float timingPositionX = screenWidth/2 -50;
	float timingPositionY = 50;
	int timingstate = 0;
	int timeCounter = 0;
	
	int barefectX = -1280;
	int bardownefectX = screenWidth;
	float barSpeed = 6.2f;
	float tableSpeed = 3.1f;
	
	int tablePositionY = -720;
	
	int selectionState = 0;
	int menuState = 0;
	int versusState = 0;
	
	
    int wavesposition = 0;
    
    bool pause = false;
	bool ready = false;
    
    bool fading = false;
    float alpha = 0.0f;
	
	Vector2 ball = {screenWidth/2, screenHeight/2};
    
	int enemydamage = 0;
	int playerdamage = 0;
    int ballRadius = 15;
    
    int ballSpeedX = 8;
    int ballSpeedY = 7;
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
            case LOGO:
            {
                // Update LOGO screen data here!
				
				// TODO: Logo fadeIn and fadeOut logic...............(0.5p)
                framesCounter++;
                if (framesCounter >= 300) 
                {
                    framesCounter = 0;
                    alpha = 0.0f;
                    currentScreen = TITLE;
                    PlayMusicStream(titlemusic);
					
                    
                }    
                
            } break;
            case TITLE:
            {
                // Update TITLE screen data here!
				
				// TODO: Title animation logic.......................(0.5p)
                elementPositionY++;
                framesCounter++;
                if (elementPositionY >= 85) elementPositionY = 85;
                
				scrolling -= 1;
                if (scrolling < -neblina.width) scrolling = 0;
                
				// TODO: "PRESS ENTER to START" logic................(0.5p)
				
				if (IsKeyPressed(KEY_ENTER))
				{
					framesCounter = 0;
					currentScreen = MENU;
				}
            } break;
			case MENU:
            {
                /*scrolling -= 1;
				if (scrolling < -bardownefect.width) scrolling = 0;*/
				framesCounter++;
				
				barefectX += barSpeed;
				bardownefectX -= barSpeed;
				
				tablePositionY += tableSpeed;
				
				if (barefectX >= 0) barefectX = 0;
				if (bardownefectX <= 0) bardownefectX = 0;
				
				if (tablePositionY >= 0) menuState = 1;
				
				if (framesCounter == 175) PlaySound(placFxWav);
				
				if (tablePositionY >= 0) tablePositionY = 0;
				
				if (selectionState == 0)
				{	
					if (IsKeyPressed(KEY_DOWN))
					{
						selectionState = 1;
						PlaySound(swordFxWav);
					}
					
					if (IsKeyPressed(KEY_UP))
					{
						selectionState = 2;
						PlaySound(swordFxWav);
					}
				}
				
				else if (selectionState == 1)
				{	
					if (IsKeyPressed(KEY_DOWN))
					{
						selectionState = 2;
						PlaySound(swordFxWav);
					}
					
					if (IsKeyPressed(KEY_UP))
					{
						selectionState = 0;
						PlaySound(swordFxWav);
					}
				}
				
				else if (selectionState == 2)
				{	
					if (IsKeyPressed(KEY_DOWN))
					{
						selectionState = 0;
						PlaySound(swordFxWav);
					}
					
					if (IsKeyPressed(KEY_UP))
					{
						selectionState = 1;
						PlaySound(swordFxWav);
					}
				}
				
				if ((IsKeyPressed(KEY_ENTER)) && (selectionState == 0))
				{
					currentScreen = GAMEPLAY;
					framesCounter = 0;
					selectionState = 0;
					versusState = 1;
				}
				
				if ((IsKeyPressed(KEY_ENTER)) && (selectionState == 1))
				{
					currentScreen = GAMEPLAY;
					framesCounter = 0;
					selectionState = 0;
					versusState = 0;
				}
				
            } break;
            case GAMEPLAY:
            {
                // Update GAMEPLAY screen data here!
				
				PauseMusicStream(titlemusic);
                framesCounter++;
				ready = true;
				if (framesCounter < 2) PlaySound(goFxWav);
				else if (framesCounter >= 180) ready = false;
                if ((!pause) && (!ready))
                { 
                    /*timing -= 1/60;
					if (timing <= 0) currentScreen = ENDING;*/
					
					// TODO: Ball movement logic.........................(0.5p)
					// TODO: Collision detection (ball-limits) logic.....(0.5p)
					// TODO: Life bars decrease logic....................(0.5p)
					// TODO: Game ending logic...........................(0.5p)
					timeCounter++;
					
					ball.x += ballSpeedX;
                    ball.y += ballSpeedY;
					
                    if (((ball.y + 15) > screenHeight) || (ball.y - 188 < 0)) ballSpeedY *= -1;
                    
                    if ((ball.x + 15) >= screenWidth) 
                    {
                        ballSpeedX *= -1;
                        enemylife.x += 30.0f;
						if (enemylife.x += 30.0f) enemydamage++;
						PlaySound(hitFxWav);
                    }
                    if (ball.x - 15 <= 0)
                    {
                        ballSpeedX *= -1;
                        playerlife.x -= 30.0f;
						if (playerlife.x -= 30.0f) playerdamage++;
                        PlaySound(hitFxWav);
                    }
                    if ((enemylife.x >= screenWidth) && (versusState == 0))
                    {
                        if (enemydamage > playerdamage) PlaySound(winFxWav);
						if (playerdamage > enemydamage) PlaySound(loseFxWav);
						currentScreen = ENDING;
                    }
                    if (((playerlife.x + playerlife.width) <= 0) && (versusState == 0))
                    {
						if (enemydamage > playerdamage) PlaySound(winFxWav);
						if (playerdamage > enemydamage) PlaySound(loseFxWav);
                        currentScreen = ENDING;
                    }
					if ((enemylife.x >= screenWidth) && (versusState == 1))
                    {
                        if (enemydamage > playerdamage) PlaySound(winFxWav);
						if (playerdamage > enemydamage) PlaySound(winFxWav);
						currentScreen = ENDING;
                    }
					if (((playerlife.x + playerlife.width) <= 0) && (versusState == 1))
                    {
                        if (enemydamage > playerdamage) PlaySound(winFxWav);
						if (playerdamage > enemydamage) PlaySound(winFxWav);
						currentScreen = ENDING;
                    }
					// TODO: Time counter logic..........................(0.5p)
					
					if ( timeCounter/60 == 99 ) 
					{
						if (enemydamage == playerdamage) PlaySound(woarghFxWav);
						currentScreen = ENDING;
					}
					// TODO: Player movement logic.......................(0.5p)
					
					if (versusState == 0)
					{
						if (IsKeyDown(KEY_UP)) playerPositionY += playerSpeedY*-1;
						if (IsKeyDown(KEY_DOWN)) playerPositionY += playerSpeedY;
					}

					if (IsKeyDown(KEY_W)) playerPositionY += playerSpeedY*-1;
					if (IsKeyDown(KEY_S)) playerPositionY += playerSpeedY;
					
                    if ((playerPositionY + 128) >= screenHeight) playerPositionY = screenHeight - 128;
                    else if (playerPositionY <= 172) playerPositionY = 172;
					
					// ENEMY (player2) logic
					
					if (versusState == 1)
					{
						if (IsKeyDown(KEY_UP)) enemyPositionY += enemySpeed*-1;
						if (IsKeyDown(KEY_DOWN)) enemyPositionY += enemySpeed;
					}
                    
					// TODO: Enemy movement logic (IA)...................(0.5p)
					
                    if ((enemyPositionY + 128) >= screenHeight) enemyPositionY = screenHeight - 128;
                    else if (enemyPositionY <= 172) enemyPositionY = 172;
                    
                    if ((ball.x > enemyVision)  && (versusState == 0))
                    {    
                        if (ball.y > (enemyPositionY + enemy.height/2)) enemyPositionY += enemySpeed;
                        if (ball.y < (enemyPositionY + enemy.height/2)) enemyPositionY -= enemySpeed;
        
                        if (enemyPositionY < 0) enemyPositionY = 0;
                        else if ((enemyPositionY + enemy.height) > screenHeight) enemyPositionY = screenHeight - enemy.height;
                    }
                    
					// TODO: Collision detection (ball-player) logic.....(0.5p)
					
					if (CheckCollisionCircleRec(ball, ballRadius,(Rectangle) {playerPositionX, playerPositionY, player.width, player.height}))
					{
						ballSpeedX *= -1;
						PlaySound(boatFxWav);
					}
					
					// TODO: Collision detection (ball-enemy) logic......(0.5p)
					
					if (CheckCollisionCircleRec(ball, ballRadius,(Rectangle) {enemyPositionX, enemyPositionY, enemy.width, enemy.height}))
					{
						ballSpeedX *= -1;
						PlaySound(boatFxWav);
					}
					
                    scrolling += 1;
                    if (scrolling > waves.width) scrolling = 0;
                }
				
				// TODO: Pause button logic..........................(0.5p)
				
                if (IsKeyPressed(KEY_P)) pause = !pause;
				
				
				
                
            } break;
            case ENDING:
            {
                // Update ENDING screen data here!
				
				//if (enemydamage > playerdamage) PlaySound(winFxWav);
				//if (playerdamage > enemydamage) PlaySound(loseFxWav);
				//if (enemydamage = playerdamage) PlaySound(drawFxWav);
				
				// TODO: Replay / Exit game logic....................(0.5p
				if (selectionState == 0)
				{	
					if (IsKeyPressed(KEY_DOWN))
					{
						selectionState = 1;
						PlaySound(swordFxWav);
					}
					
					if (IsKeyPressed(KEY_UP))
					{
						selectionState = 1;
						PlaySound(swordFxWav);
					}
				}
				
				else if (selectionState == 1)
				{	
					if (IsKeyPressed(KEY_DOWN))
					{
						selectionState = 0;
						PlaySound(swordFxWav);
					}
					
					if (IsKeyPressed(KEY_UP))
					{
						selectionState = 0;
						PlaySound(swordFxWav);
					}
				}
				if ((IsKeyPressed(KEY_ENTER)) && (selectionState == 0))
				{
					currentScreen = GAMEPLAY;
					framesCounter = 0;
					selectionState = 0;
					playerdamage = 0;
					enemydamage = 0;
					ball.x = screenWidth/2;
					ball.y = screenHeight/2;
					playerlife.x = 0.0f;
					enemylife.x = 816.0f;
					playerlifecolor = ENCHANTEDBLUE;
					enemylifecolor = ENCHANTEDRED;
					timeCounter = 0;
				}
				if ((IsKeyPressed(KEY_ENTER)) && (selectionState == 1))
				{
					currentScreen = MENU;
					framesCounter = 0;
					selectionState = 0;
					playerdamage = 0;
					enemydamage = 0;
					ball.x = screenWidth/2;
					ball.y = screenHeight/2;
					playerlife.x = 0.0f;
					enemylife.x = 816.0f;
					playerlifecolor = ENCHANTEDBLUE;
					enemylifecolor = ENCHANTEDRED;
					timeCounter = 0;
				}
            } break;
            default : break;
            
            //framescounter++;
            //fading alpha  += 1 /240
            
            //if fading alpha >= 1 
            /* current screen = next screen
                fading = false;
                fading alpha = 0.0f
            */
            
        }
        
        UpdateMusicStream(titlemusic);
        //----------------------------------------------------------------------------------
        
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            //DrawText("", 190, 200, 20, LIGHTGRAY);
            switch (currentScreen)
        {
            case LOGO:
            {
                // Draw LOGO screen here!
				
				// TODO: Draw Logo...............................(0.5p)
				
                DrawRectangle (0, 0, screenWidth, screenHeight, BLACK);
                if (framesCounter <= 90)  DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, Fade (WHITE, alpha +=(1.0f/90)));
                else if ((framesCounter > 90) && (framesCounter <= 210)) DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, WHITE);
                else if (framesCounter > 210) DrawTexture(logo, screenWidth/2 - logo.width/2, screenHeight/2 - logo.height/2, Fade (WHITE, alpha -=(1.0f/90)));
                
            } break;
            case TITLE:
            {
                // Draw TITLE screen here!
				
				// TODO: Draw Title texture......................(0.5p)
				
                DrawTexture(title, 0, 0, WHITE);
                DrawTexture(neblina, scrolling, 0, WHITE);
                DrawTexture(neblina, neblina.width + scrolling, 0, WHITE);
                DrawTexture(nubes, 0, 0, WHITE);
                DrawTexture(cannong, 150, elementPositionY, WHITE);
                if ((framesCounter/3)%2) DrawTexture(brillo, 0, 0, Fade (WHITE, 0.2f));
				
				// TODO: Draw "PRESS ENTER" message..............(0.5p)
				
                if ((framesCounter/30)%2) DrawText("PRESS ENTER TO CONTINUE", 700, 200, 30, Fade (BLACK, 0.6f));
                
            } break;
			case MENU:
            {
                DrawTexture(menu, 0, 0, WHITE);
				DrawTexture(nubesmenu, scrolling, 0, WHITE);
				DrawTexture(nubesmenu, nubesmenu.width + scrolling, 0, WHITE);
				
				DrawTexture(oldefect, 0, 0, Fade (WHITE, alpha +=(1.0f/240)));
				DrawTexture(barefect, barefectX, 0, WHITE);
				DrawTexture(bardownefect, bardownefectX, 0, WHITE);
				DrawTexture(table, 0, tablePositionY, WHITE);
				
				if (menuState == 1)DrawTextEx(savagefont, "2PLAYERS", (Vector2){ screenWidth/2 - 155, screenHeight/2 - 85 }, savagefont.size*1.8f, 0, WHITE);
				if (menuState == 1)DrawTextEx(savagefont, "PLAYER VS CPU", (Vector2){ screenWidth/2 - 155, screenHeight/2 - 35 }, savagefont.size*1.8f, 0, WHITE);
				if (menuState == 1)DrawTextEx(savagefont, "OPTIONS", (Vector2){ screenWidth/2 - 155, screenHeight/2 + 15 }, savagefont.size*1.8f, 0, WHITE);
				
				if ((selectionState == 0) && (menuState == 1)) DrawTextEx(savagefont, "2PLAYERS", (Vector2){ screenWidth/2 - 155, screenHeight/2 - 85 }, savagefont.size*1.8f, 0, MAROON);
				if ((selectionState == 1) && (menuState == 1)) DrawTextEx(savagefont, "PLAYER VS CPU", (Vector2){ screenWidth/2 - 155, screenHeight/2 - 35 }, savagefont.size*1.8f, 0, MAROON);
				if ((selectionState == 2) && (menuState == 1)) DrawTextEx(savagefont, "OPTIONS", (Vector2){ screenWidth/2 - 155, screenHeight/2 + 15 }, savagefont.size*1.8f, 0, MAROON);
				
            } break;
            case GAMEPLAY:
            {
                //Draw GAMEPLAY screen here!
                
                
                DrawTexture(sea, 0, 0, WHITE);
               
                
                DrawTexture(waves, 0, 0, WHITE);
                DrawTexture(hud, 0, 0, WHITE);
				
                // TODO: Draw player and enemy life bars.........(0.5p)
				
                DrawRectangleRec(playerlife, Fade (playerlifecolor, 0.8f));
                DrawRectangleRec(enemylife, Fade (enemylifecolor, 0.8f));
				
                if (playerdamage >= 1) playerlifecolor = SUPERBLUE;
				if (enemydamage >= 1) enemylifecolor = HEAVYRED;
				
				if (playerdamage >= 3) playerlifecolor = DEPTBLUE;
				if (enemydamage >= 3) enemylifecolor = BLOODYRED;
				
				if (playerdamage >= 6) playerlifecolor = LONELYBLUE;
				if (enemydamage >= 6) enemylifecolor = ALMOSTRED;
				
                if ((framesCounter/200)%2) DrawTexture(eyes1, 0, 0, WHITE);
                if ((framesCounter/300)%2) DrawTexture(eyes2, 0, 0, WHITE);
                
				DrawTexture(moss, 0, 0, WHITE);
				
				// TODO: Draw time counter (custom SpriteFont)...(0.5p)
				
				DrawTextEx(savagefont, FormatText("%i", 99 - timeCounter/60), (Vector2){ screenWidth/2 - 50, 65 }, savagefont.size*3, 0, WHITE);
				DrawCircle(ball.x, ball.y, 15, LEADGRAY);
				
				if (framesCounter <= 180) DrawTextEx(savagefont, "READY ?", (Vector2){ screenWidth/2 - 200, screenHeight/2 - 100 }, savagefont.size*4, 0, GOLD);
                
				// TODO: Draw player and enemy textures..........(0.5p)
				
                if ((ball.x + 15) >= screenWidth) DrawTextureRec(enemy, enemyframe, (Vector2) {enemyPositionX, enemyPositionY}, RED);
                if (ball.x - 15 <= 0) DrawTextureRec(player, playerframe, (Vector2) {playerPositionX, playerPositionY}, RED);
				
				
				if ((ball.x + 15) <= screenWidth)DrawTextureRec(enemy, enemyframe, (Vector2) {enemyPositionX, enemyPositionY},  WHITE);
				if (ball.x - 15 > 0)DrawTextureRec(player, playerframe, (Vector2) {playerPositionX, playerPositionY}, WHITE);
				
				// TODO: Draw pause message when required........(0.5p)
				
                if (pause) //fade
				{
					DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.4f)); //fading alpha
					if ((framesCounter/15)%2) DrawTextEx(swampfont, "GAME PAUSED", (Vector2){ screenWidth/2 - 250, screenHeight/2 - 80}, swampfont.size*3, 0, WHITE);
				}
                
            } break;
            case ENDING:
            {
                // Draw END screen here!
                
                DrawRectangle (0, 0, screenWidth, screenHeight, BLACK);
				DrawTexture(table, screenWidth/2 - table.width/2, screenHeight/2 - table.height/2, BROWN);
				
				DrawTextEx(savagefont, "PLAY AGAIN", (Vector2){ screenWidth/2 - 165, screenHeight/2 - 85 }, savagefont.size*1.8f, 0, WHITE);
				DrawTextEx(savagefont, "RETURN TO MENU", (Vector2){ screenWidth/2 - 165, screenHeight/2 - 35 }, savagefont.size*1.8f, 0, WHITE);
				if (selectionState == 0) DrawTextEx(savagefont, "PLAY AGAIN", (Vector2){ screenWidth/2 - 165, screenHeight/2 - 85 }, savagefont.size*1.8f, 0, MAROON);
				if (selectionState == 1) DrawTextEx(savagefont, "RETURN TO MENU", (Vector2){ screenWidth/2 - 165, screenHeight/2 - 35 }, savagefont.size*1.8f, 0, MAROON);
				DrawTextEx(swampfont, "PRESS ESC TO EXIT GAME", (Vector2){ screenWidth/2 - 185, screenHeight - 50 }, swampfont.size*1.2f, 0, Fade (WHITE, 0.4f));
				
				// TODO: Draw ending message (win or loose)......(0.5p)
				
				if (versusState == 0)
				{
					if (enemydamage > playerdamage) DrawTextEx(savagefont, "YOU WIN!", (Vector2){ screenWidth/2 - 180, 20 }, savagefont.size*3, 0, GREEN);
					if (playerdamage > enemydamage) DrawTextEx(savagefont, "YOU LOSE!", (Vector2){ screenWidth/2 - 180, 20}, savagefont.size*3, 0, PINK);
					if (playerdamage == enemydamage) DrawTextEx(savagefont, "DRAW GAME", (Vector2){ screenWidth/2 - 190, 20}, savagefont.size*3, 0, PINK);
				}
				if (versusState == 1)
				{
					if (enemydamage > playerdamage) DrawTextEx(savagefont, "PLAYER1 WINS!", (Vector2){ screenWidth/2 - 190, 20 }, savagefont.size*3, 0, GREEN);
					if (playerdamage > enemydamage) DrawTextEx(savagefont, "PLAYER2 WINS!", (Vector2){ screenWidth/2 - 190, 20}, savagefont.size*3, 0, PINK);
					if (playerdamage == enemydamage) DrawTextEx(savagefont, "DRAW GAME", (Vector2){ screenWidth/2 - 190, 20}, savagefont.size*3, 0, PINK);
				}
				
				
                
            } break;
            default : break;
        }
        
        DrawFPS(10, 10);
		
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
	
	// TODO: Unload textures, spritefonts, sounds and music
    
    UnloadTexture(player);
    UnloadTexture(enemy);
    UnloadTexture(eyes2);
    UnloadTexture(eyes1);
    UnloadTexture(moss);
    UnloadTexture(hud);
    UnloadTexture(waves);
    UnloadTexture(sea);
    UnloadTexture(logo);
    UnloadTexture(title);
    UnloadTexture(cannong);
    UnloadTexture(nubes);
    UnloadTexture(neblina);
    UnloadTexture(brillo);
    UnloadTexture(menu);
	UnloadTexture(nubesmenu);
	UnloadTexture(barefect);
	UnloadTexture(bardownefect);
	UnloadTexture(table);
	UnloadTexture(oldefect);
   
    UnloadSpriteFont(savagefont);
	UnloadSpriteFont(swampfont);
   
    UnloadMusicStream(titlemusic);
	
	UnloadSound(placFxWav);
    UnloadSound(hitFxWav);
    UnloadSound(swordFxWav);
    UnloadSound(winFxWav);
    UnloadSound(loseFxWav);
    UnloadSound(goFxWav);
    UnloadSound(woarghFxWav);
	UnloadSound(boatFxWav);
    
    CloseAudioDevice();
	
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}