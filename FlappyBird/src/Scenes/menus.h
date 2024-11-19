#pragma once

#include "raylib.h"

namespace Menu 
{


enum class Menus
{
	MainMenu,
	Playing,
	PlayingTwo,
	Rules,
	HowToPlay,
	Credits,
	WantToExit,
	None,

	Replay,

	Resume,

	ConfirmExit,
	CancelExit,
	Exit

};


extern const float titlesFontSize;
extern const float textFontSize;
extern const float scoreFontSize;

} // namespace Menu