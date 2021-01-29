#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace Window {
	const int windowIdLowest = wxID_HIGHEST + 1;

	enum ID {
		MAIN_WINDOW = windowIdLowest
	};
}

namespace MenuItems {
	const int menuItemsLowest = Window::windowIdLowest + 10;

	enum ID {
		TWO_PLAYERS_GAME_MODE = menuItemsLowest,
		PLAYER_VS_AI_MODE = menuItemsLowest + 1,
		DISPLAY_INFORMATION = menuItemsLowest + 2,
		SHOW_GAME_RULES = menuItemsLowest + 3
	};
}

namespace Canvas {
	const int canvasIdLowest = MenuItems::menuItemsLowest + 10;

	enum ID {
		BOARD_CANVAS = canvasIdLowest
	};
}