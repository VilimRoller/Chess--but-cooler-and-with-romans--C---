#pragma once
//Separated from Constants.h to avoid including wxWidgets in tests

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

namespace wxConstants {
	const wxPoint MainWindowPoint{ 550, 150 };
	const wxSize MainWindowSize{ 818, 865 };

	const wxPoint BoardCanvasPoint{ 0,0 };
	const wxSize BoardCanvasSize{ 800,800 };
}

namespace wxConstantStrings {
	const wxString ApplicationName = wxT("Roman Chess");

	const wxString DisplayInformation = wxT("Display information");
	const wxString DisplayGameRules = wxT("Display Game Rules");
	const wxString DisplayRules = wxT("Display rules");
	const wxString File = wxT("File");
	const wxString Options = wxT("Options");
	const wxString View = wxT("View");
	const wxString Rules = wxT("Rules");

	const wxString NewGame = wxT("New Game");
	const wxString SaveGame = wxT("Save Game as");
	const wxString LoadGame = wxT("Load Game");
	const wxString TwoPlayers = wxT("Two Players");
	const wxString PlayerVsAI = wxT("Player vs AI");
	const wxString GameMode = wxT("Game Mode");

	const wxString FileNotSavedHeadline = wxT("File not saved notification");
	const wxString FileNotSavedMessage = wxT("This game has not been saved. Do you wish to quit anyway?");
}
