#include "scene.h"

#include <list>
#include <string>

#include "Engine/utilities.h"
#include "Engine/button.h"
#include "Engine/engine.h"
#include "Scenes/menus.h"
#include "GamePlay/Entities/player.h"
#include "GamePlay/Entities/pipe.h"

void Drawers::DrawGamePlay(Menu::Menus gameState, Player::Player playerOne, Player::Player playerTwo, std::list<Pipe::PipeSet>& pipeSets, Sprites::Sprites& sprites, Sprites::SpriteMovement spriteMovement, bool pause)
{

	Vector2 origin = { 0.0f, 0.0f };

	// Dibujar el fondo
	Rectangle sourceRec = { 0.0f, 0.0f, (float)sprites.sky.width, (float)sprites.sky.height };

	Rectangle destRec = { spriteMovement.sky, 0, screenWidth, screenHeight };
	DrawTexturePro(sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);

	destRec = { screenWidth + spriteMovement.sky, 0, screenWidth, screenHeight };
	DrawTexturePro(sprites.sky, sourceRec, destRec, origin, 0.0f, WHITE);



	sourceRec = { 0.0f, 0.0f, (float)sprites.backBuildings.width, (float)sprites.backBuildings.height };

	destRec = { spriteMovement.backBuildings, 0, screenWidth, screenHeight };
	DrawTexturePro(sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

	destRec = { screenWidth + spriteMovement.backBuildings, 0, screenWidth, screenHeight };
	DrawTexturePro(sprites.backBuildings, sourceRec, destRec, origin, 0.0f, WHITE);


	sourceRec = { 0.0f, 0.0f, (float)sprites.frontBuildings.width, (float)sprites.frontBuildings.height };

	destRec = { spriteMovement.frontBuildings, 0.0f, screenWidth, screenHeight };
	DrawTexturePro(sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

	destRec = { screenWidth + spriteMovement.frontBuildings, 0.0f, screenWidth, screenHeight };
	DrawTexturePro(sprites.frontBuildings, sourceRec, destRec, origin, 0.0f, WHITE);

	playerOne.pos.x += sprites.playerOneSheet.width / 2;
	playerOne.pos.y += sprites.playerOneSheet.height / 2;

	DrawTexturePro(
		sprites.playerOneSheet,
		playerOne.frameRec,
		Rectangle{ playerOne.pos.x - playerOne.size / 2, playerOne.pos.y - playerOne.size / 2, playerOne.size, playerOne.size },
		Vector2{ static_cast<float>(sprites.playerOneSheet.width) / 2, static_cast<float>(sprites.playerOneSheet.height) / 2 },
		0,
		WHITE);
	
	if (gameState == Menu::Menus::PlayingTwo)
	{
		playerTwo.pos.x += sprites.playerTwoSheet.width / 2;
		playerTwo.pos.y += sprites.playerTwoSheet.height / 2;

		DrawTexturePro(
			sprites.playerTwoSheet,
			playerTwo.frameRec,
			Rectangle{ playerTwo.pos.x - playerTwo.size / 2, playerTwo.pos.y - playerTwo.size / 2, playerTwo.size, playerTwo.size },
			Vector2{ static_cast<float>(sprites.playerTwoSheet.width) / 2, static_cast<float>(sprites.playerTwoSheet.height) / 2 },
			0,
			WHITE);
	}

	

	for (Pipe::PipeSet pipeSetIt : pipeSets)
	{
		DrawRectangleRec(pipeSetIt.top.rect, GREEN);
		DrawRectangleRec(pipeSetIt.bottom.rect, RED);

		pipeSetIt.top.rect.x += pipeSetIt.top.rect.width / 2;
		pipeSetIt.top.rect.y += pipeSetIt.top.rect.height / 2;

		float pipeSpriteWidth = static_cast<float>(sprites.pipeImage.width);
		float pipeSpriteHeight = static_cast<float>(sprites.pipeImage.height);

		DrawTexturePro(
			sprites.pipeImage,
			Rectangle{ 0,0, pipeSpriteWidth, pipeSpriteHeight },
			pipeSetIt.top.rect,
			Vector2{ pipeSetIt.top.rect.width / 2, pipeSetIt.top.rect.height / 2 },
			180.0f,
			WHITE);

		DrawTexturePro(
			sprites.pipeImage,
			Rectangle{ 0,0,pipeSpriteWidth, pipeSpriteHeight },
			pipeSetIt.bottom.rect,
			Vector2{ 0,0 },
			pipeSetIt.bottom.angle,
			WHITE);
	}

	sourceRec = { 0.0f, 0.0f, (float)sprites.fence.width, (float)sprites.fence.height };

	destRec = { spriteMovement.fence, screenHeight - sprites.fence.height * 2, screenWidth * 2, (float)sprites.fence.height * 2 };
	DrawTexturePro(sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);

	destRec = { screenWidth + spriteMovement.fence, screenHeight - sprites.fence.height * 2, screenWidth * 2, (float)sprites.fence.height * 2 };
	DrawTexturePro(sprites.fence, sourceRec, destRec, origin, 0.0f, WHITE);

	if (!pause)
	{
		std::string text = "Points: " + std::to_string(playerOne.points);

		DrawText(text.c_str(), 0, 0, 20, RAYWHITE);

		text = "Press ESC to pause " + std::to_string(pipeSets.size());

		DrawText(text.c_str(), static_cast<int>(screenWidth) - MeasureText(text.c_str(), 20), 0, 20, RAYWHITE);
	}
}

void Drawers::DrawMainMenu(Menu::Menus& gameState, Font font, Texture2D titleTexture)
{
	ClearBackground(DARKGRAY);
	const int maxButtons = 6;
	Vector2 mouse;
	Buttons::Button button[maxButtons] = {};


	// Posiciones iniciales pa los botones
	float yBottomSpacing = 60.0f;
	float startX = (0 + Buttons::buttonWidth /2);
	float startY = screenHeight - (Buttons::buttonHeight * maxButtons + Buttons::buttonSpacing * (maxButtons - 1) + yBottomSpacing);

	struct ButtonData 
	{
		Menu::Menus option;
		const char* text;
	};

	ButtonData buttonData[maxButtons] = 
	{
		{ Menu::Menus::Playing, "1 Player" },
		{ Menu::Menus::PlayingTwo, "2 Players" },
		{ Menu::Menus::Rules, "Rules" },
		{ Menu::Menus::HowToPlay, "How To Play" },
		{ Menu::Menus::Credits, "Credits" },
		{ Menu::Menus::WantToExit, "Exit" }
	};

	// Configuración de los botones
	for (int i = 0; i < maxButtons; i++) 
	{
		button[i].rect = { startX, startY + i * (Buttons::buttonHeight + Buttons::buttonSpacing), Buttons::buttonWidth, Buttons::buttonHeight };
		button[i].option = buttonData[i].option;
	}

	Color outline = BLACK;
	mouse = GetMousePosition();

	// Detección de interacciones del mouse
	for (int i = 0; i < maxButtons; i++) 
	{
		if (Tools::CheckMouseButtonCollision(mouse, button[i].rect)) 
		{
			button[i].color = WHITE;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
				button[i].color = YELLOW;
			}

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
				gameState = button[i].option;
			}
		}
	}

	// Dibujar texto de version
	DrawText("v1.0", 0, 0, 20, WHITE);



	// Dibujar Titulo
	float scale = std::min(
		static_cast<float>(GetScreenWidth()) / titleTexture.width,
		static_cast<float>(GetScreenHeight()) / titleTexture.height
	);

	// Calcular las dimensiones escaladas
	float scaledWidth = (titleTexture.width * scale)-70;
	float scaledHeight = titleTexture.height * scale;

	// Posicionar en el centro de la mitad derecha de la pantalla
	float destX = GetScreenWidth() / 2 + (GetScreenWidth() / 4) - (scaledWidth / 2); // Mitad derecha, centrado
	float destY = (GetScreenHeight() / 2) - (scaledHeight / 2);                 // Centrado verticalmente

	// Dibujar la textura escalada en la posición calculada
	DrawTexturePro(
		titleTexture,
		Rectangle{ 0, 0, static_cast<float>(titleTexture.width), static_cast<float>(titleTexture.height) }, // Fuente completa
		Rectangle{ destX, destY, scaledWidth, scaledHeight },                                              // Destino ajustado
		Vector2{ 0, 0 },  // Sin desplazamiento
		0.0f,             // Sin rotación
		WHITE              // Sin tintes
	);

	// Dibujar los botones
	for (int i = 0; i < maxButtons; i++) 
	{
		Buttons::DrawButton(button[i].rect, buttonData[i].text, button[i].color, outline, font);
	}
}

void Drawers::DrawCredits(Menu::Menus& gameState, Font font)
{
	Buttons::Button button = {};

	Vector2 mouse = GetMousePosition();

	float newSmallFontSize = 20.0f;
	float newTextFontSize = 25.0f;
	float newTitleFontSize = 30.0f;

	Vector2 titlePos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Credits", newTitleFontSize, 2).x / 2, static_cast<float>(screenHeight) / 6 };
	Vector2 developerPos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Developer: Lucio Stefano Piccioni.", newTextFontSize, 2).x / 2, titlePos.y + 60 };
	Vector2 musicPos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Music:", newTextFontSize, 2).x / 2, developerPos.y + 60 };
	Vector2 music1Pos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "1. 'Game Over!' - Harris Cole", newSmallFontSize, 2).x / 2, musicPos.y + 40 };
	Vector2 music2Pos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "2. 'Falling Apart' - yawgooh (Lofi Girl Ambient)", newSmallFontSize, 2).x / 2, music1Pos.y + 30 };
	Vector2 music3Pos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "3. 'Quiet Nights' - JEN", newSmallFontSize, 2).x / 2, music2Pos.y + 30 };
	Vector2 music4Pos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "4. 'Facade' - JEN", newSmallFontSize, 2).x / 2, music3Pos.y + 30 };
	Vector2 soundEffectsPos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Sound Effects:", newTextFontSize, 2).x / 2, music4Pos.y + 50 };
	Vector2 chipTonePos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "ChipTone", newSmallFontSize, 2).x / 2, soundEffectsPos.y + 30 };
	Vector2 tomiPos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Special thanks to: Tomas F. Luchelli (MacGiv)", newSmallFontSize, 2).x / 2, chipTonePos.y + 30 };
	Vector2 menuPos = { static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Press ESC to go back to the Menu.", newSmallFontSize, 2).x / 2, static_cast<float>(screenHeight) - 40 };

	button.rect.width = Buttons::buttonWidth;
	button.rect.height = Buttons::buttonHeight;
	button.option = Menu::Menus::MainMenu;
	button.rect.x = static_cast<float>(screenWidth) / 2 - (button.rect.width / 2);

	button.rect.y = (chipTonePos.y + menuPos.y + 60) / 2 - (button.rect.height / 2);

	DrawTextEx(font, "Credits", titlePos, newTitleFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Developer: Lucio Stefano Piccioni.", developerPos, newTextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Special thanks to: Tomas F. Luchelli (MacGiv)", tomiPos, newSmallFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Music:", musicPos, newTextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "1. 'Game Over!' - Harris Cole", music1Pos, newSmallFontSize, 2, RAYWHITE);
	DrawTextEx(font, "2. 'Falling Apart' - yawgooh (Lofi Girl Ambient)", music2Pos, newSmallFontSize, 2, RAYWHITE);
	DrawTextEx(font, "3. 'Quiet Nights' - JEN", music3Pos, newSmallFontSize, 2, RAYWHITE);
	DrawTextEx(font, "4. 'Facade' - JEN", music4Pos, newSmallFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Sound Effects:", soundEffectsPos, newTextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "ChipTone", chipTonePos, newSmallFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Or press ESC to go back to the Menu.", menuPos, newSmallFontSize, 2, DARKGRAY);

	Color outline = BLACK;

	if (Tools::CheckMouseButtonCollision(mouse, button.rect))
	{
		button.color = WHITE;

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			button.color = YELLOW;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			gameState = button.option;
	}

	std::string text = "Menu";
	Buttons::DrawButton(button.rect, text, button.color, outline, font);
}

void Drawers::DrawGameRules(Menu::Menus& gameState, Font font)
{
	float newtextFontSize = 25.0f;
	float newTitleFontSize = 30.0f;  

	Buttons::Button button = {};
	Vector2 mouse = GetMousePosition();

	Vector2 titlePos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Game Rules", Menu::titlesFontSize, 2).x / 2,
		static_cast<float>(screenHeight) / 10
	};

	Vector2 controlsTitlePos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Controls:", newTitleFontSize, 2).x / 2,
		titlePos.y + Menu::titlesFontSize + Buttons::buttonSpacing
	};

	Vector2 pControl1 = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Space: Jump Player 1", newtextFontSize, 2).x / 2,
		controlsTitlePos.y + Buttons::buttonSpacing + Menu::titlesFontSize / 3
	};

	Vector2 pControls2 = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Up Arrow: Jump Player 2", newtextFontSize, 2).x / 2,
		pControl1.y + Buttons::buttonSpacing + Menu::titlesFontSize / 3
	};

	Vector2 backToMenuPos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Press ESC to return to menu", newtextFontSize, 2).x / 2,
		static_cast<float>(screenHeight) - 60
	};

	button.rect.width = Buttons::buttonWidth;
	button.rect.height = Buttons::buttonHeight;
	button.option = Menu::Menus::MainMenu;
	button.rect.x = static_cast<float>(screenWidth) / 2 - (button.rect.width / 2);

	DrawTextEx(font, "Game Rules", titlePos, Menu::titlesFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Controls:", controlsTitlePos, newTitleFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Space: Jump Player 1", pControl1, newtextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Up Arrow: Jump Player 2", pControls2, newtextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Press ESC to return to menu", backToMenuPos, newtextFontSize, 2, RAYWHITE);

	Color outline = BLACK;

	DrawRectangleLinesEx(button.rect, 5, RED);

	if (Tools::CheckMouseButtonCollision(mouse, button.rect))
	{
		button.color = WHITE;

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
		{
			button.color = YELLOW;
		}

		if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			gameState = button.option;
	}

	std::string text = "Menu";
	Buttons::DrawButton(button.rect, text, button.color, outline, font);
}


void Drawers::DrawPauseMenu(Menu::Menus& gameState, Font font, bool& pause)
{
	const int buttonCount = 3;  // Cantidad de botones
	Vector2 mouse;
	Buttons::Button buttons[buttonCount] = {}; // Array de botones

	// Inicializa la posición de los botones
	float startX = (screenWidth - Buttons::buttonWidth) / 2;
	float startY = screenHeight - (Buttons::buttonHeight * buttonCount + Buttons::buttonSpacing * (buttonCount - 1));

	// Establece las opciones de los botones
	buttons[0].option = Menu::Menus::Resume;
	buttons[1].option = Menu::Menus::MainMenu;
	buttons[2].option = Menu::Menus::WantToExit;

	// Inicialización de los rectángulos de los botones
	for (int i = 0; i < buttonCount; i++)
	{
		buttons[i].rect = { startX, startY + i * (Buttons::buttonHeight + Buttons::buttonSpacing), Buttons::buttonWidth, Buttons::buttonHeight };
	}

	Color outline = BLACK;
	mouse = GetMousePosition();

	// Dibuja los botones y gestiona la interacción
	for (int i = 0; i < buttonCount; i++)
	{
		if (Tools::CheckMouseButtonCollision(mouse, buttons[i].rect))
		{
			buttons[i].color = WHITE;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				buttons[i].color = YELLOW;
			}

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
			{
				gameState = buttons[i].option;

				if (buttons[i].option != Menu::Menus::WantToExit)
					pause = false;
			}
		}
	}

	Vector2 titlePos =
	{
		(screenWidth) / 2 - MeasureTextEx(font, "Pause", Menu::titlesFontSize, 2).x / 2,
		(screenHeight) / 5
	};

	Color pastelPurple = { 214, 196, 224, 255 };


	DrawTextEx(font, "Pause", titlePos, Menu::titlesFontSize, 2, pastelPurple);

	for (int i = 0; i < buttonCount; i++)
	{
		switch (buttons[i].option)
		{
		case Menu::Menus::Resume:
			Buttons::DrawButton(buttons[i].rect, "Resume", buttons[i].color, outline, font);
			break;
		case Menu::Menus::MainMenu:
			Buttons::DrawButton(buttons[i].rect, "Main Menu", buttons[i].color, outline, font);
			break;
		case Menu::Menus::WantToExit:
			Buttons::DrawButton(buttons[i].rect, "Exit Game", buttons[i].color, outline, font);
			break;
		default:
			break;
		}
	}

	if (gameState == Menu::Menus::Resume)
	{
		gameState = Menu::Menus::Playing;
	}
}


void Drawers::DrawGameOver(Menu::Menus& gameState, Font font)
{
	const int maxButtons = 3;
	Vector2 mouse = GetMousePosition();
	Buttons::Button button[maxButtons] = {};

	Color outline = BLACK;

	float startX = (static_cast<float>(screenWidth) - Buttons::buttonWidth) / 2;
	float startY = ((static_cast<float>(screenHeight) - screenHeight / 5) - (Buttons::buttonHeight * maxButtons + Buttons::buttonSpacing * (maxButtons - 1)));

	for (int i = 0; i < maxButtons; i++)
	{
		button[i].rect = { startX, startY + i * (Buttons::buttonHeight + Buttons::buttonSpacing), Buttons::buttonWidth, Buttons::buttonHeight };
	}

	button[0].option = Menu::Menus::Replay;
	button[1].option = Menu::Menus::MainMenu;
	button[2].option = Menu::Menus::WantToExit;

	for (int i = 0; i < maxButtons; i++)
	{
		if (Tools::CheckMouseButtonCollision(mouse, button[i].rect))
		{
			button[i].color = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? YELLOW : WHITE;

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				gameState = button[i].option;
		}
	}

	Vector2 gameOverTextSize = MeasureTextEx(font, "GAME OVER", Menu::titlesFontSize, 0);
	Vector2 gameOverPos = { static_cast<float>(screenWidth) / 2 - gameOverTextSize.x / 2, static_cast<float>(screenHeight) / 3 };

	DrawTextEx(font, "GAME OVER", gameOverPos, Menu::titlesFontSize, 0, RED);

	for (int i = 0; i < maxButtons; i++)
	{
		switch (button[i].option)
		{
		case Menu::Menus::Replay:
			Buttons::DrawButton(button[i].rect, "Replay", button[i].color, outline, font);
			break;
		case Menu::Menus::MainMenu:
			Buttons::DrawButton(button[i].rect, "Main Menu", button[i].color, outline, font);
			break;
		case Menu::Menus::WantToExit:
			Buttons::DrawButton(button[i].rect, "Exit", button[i].color, outline, font);
			break;
		}
	}
}

void Drawers::DrawConfirmExit(Menu::Menus& gameState, Font font, Menu::Menus previusMenu)
{
	const int maxButtons = 2;

	Color outLine = BLACK;

	Vector2 mouse = GetMousePosition();
	Buttons::Button button[maxButtons];

	float startX, startY;

	startX = (screenWidth - Buttons::buttonWidth) / 2;
	startY = (screenHeight - (Buttons::buttonHeight * maxButtons + Buttons::buttonSpacing * (maxButtons - 1))) / 2;

	button[0].option = Menu::Menus::ConfirmExit;
	button[1].option = Menu::Menus::CancelExit;

	for (int i = 0; i < maxButtons; i++)
	{
		button[i].rect = { static_cast<float>(startX), static_cast<float>(startY + i * (Buttons::buttonHeight + Buttons::buttonSpacing)), Buttons::buttonWidth, Buttons::buttonHeight };

		switch (button[i].option)
		{
		case Menu::Menus::ConfirmExit:
			button[i].color = RED;
			break;

		case Menu::Menus::CancelExit:
			button[i].color = GREEN;
			break;

		default:
			break;
		}
	}

	for (int i = 0; i < maxButtons; i++)
	{
		if (Tools::CheckMouseButtonCollision(mouse, button[i].rect))
		{
			button[i].color = WHITE;

			if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
			{
				button[i].color = YELLOW;
			}

			if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
				gameState = button[i].option;
		}
	}

	switch (gameState)
	{
	case Menu::Menus::ConfirmExit:
		gameState = Menu::Menus::Exit;
		break;

	case Menu::Menus::CancelExit:
		gameState = previusMenu;
		timmerToCleanBuffer = 0.01f;
		break;

	default:
		break;
	}

	DrawRectangle(0, 0, static_cast<int>(screenWidth), static_cast<int>(screenHeight), Color{ 0, 0, 0, 125 });

	DrawTextEx(font, "Are you sure you want to exit?",
		Vector2{ static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Are you sure you want to exit?", Menu::textFontSize, 0).x / 2, static_cast<float>(screenHeight / 4) },
		Menu::textFontSize, 0, outLine);

	for (int i = 0; i < maxButtons; i++)
	{
		switch (button[i].option)
		{
		case Menu::Menus::ConfirmExit:
			Buttons::DrawButton(button[i].rect, "Yes", button[i].color, outLine, font);
			break;

		case Menu::Menus::CancelExit:
			Buttons::DrawButton(button[i].rect, "No", button[i].color, outLine, font);
			break;

		default:
			break;
		}
	}
}

void Drawers::DrawHowToPlay(Menu::Menus& gameState, Font font)
{
	float newTextFontSize = 25.0f;
	float newTitleFontSize = 30.0f;

	// Configuración de posiciones del texto
	Vector2 titlePos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "How To Play", newTitleFontSize, 2).x / 2,
		static_cast<float>(screenHeight) / 10
	};

	Vector2 instructionsPos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Avoid pipes and stay alive!", newTextFontSize, 2).x / 2,
		titlePos.y + newTitleFontSize + 20
	};

	Vector2 playerOneControlsPos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Player 1: Press SPACE to jump.", newTextFontSize, 2).x / 2,
		instructionsPos.y + newTextFontSize + 30
	};

	Vector2 playerTwoControlsPos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Player 2: Press UP ARROW to jump.", newTextFontSize, 2).x / 2,
		playerOneControlsPos.y + newTextFontSize + 30
	};

	Vector2 backToMenuPos = {
		static_cast<float>(screenWidth) / 2 - MeasureTextEx(font, "Press ESC to return to menu.", newTextFontSize, 2).x / 2,
		static_cast<float>(screenHeight) - 60
	};

	// Dibujar texto
	DrawTextEx(font, "How To Play", titlePos, newTitleFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Avoid pipes and stay alive!", instructionsPos, newTextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Player 1: Press SPACE to jump.", playerOneControlsPos, newTextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Player 2: Press UP ARROW to jump.", playerTwoControlsPos, newTextFontSize, 2, RAYWHITE);
	DrawTextEx(font, "Press ESC to return to menu.", backToMenuPos, newTextFontSize, 2, GRAY);

	// Detectar si se presiona ESC para volver al menú
	if (IsKeyPressed(KEY_ESCAPE))
	{
		gameState = Menu::Menus::MainMenu;
	}
}

