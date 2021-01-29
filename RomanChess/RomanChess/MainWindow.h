#pragma once
#include "wxConstants.h"
#include "wxID.h"
#include "wx/artprov.h"
#include "Board.h"


class MainWindow :
    public wxFrame
{
public:
    MainWindow(wxWindow* parent,
        wxWindowID id,
        const wxString& title,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxDEFAULT_FRAME_STYLE,
        const wxString& name = wxASCII_STR(wxFrameNameStr));

    ~MainWindow();
    MainWindow(const MainWindow& other) = delete;
    MainWindow(MainWindow&& other) = delete;

    bool IsGameSaved() {
        return is_game_saved_;
    }

    void InitializeMainWindow();
    void InitializeMainWindowMenuBar();

    void InitializeMainWindowMenuItems();
    void InitializeFileMenuItems();
    void InitializeOptionsMenuItems();
    void InitializeViewMenuItems();
    void InitializeRulesMenuItems();

    void SetMainWindowMenuBar();
    void DeleteMainWindowMenuBar();

    void SetMainWindowMenus();

    void SetFileMenu();
    void SetOptionsMenu();
    void SetViewMenu();
    void SetRulesMenu();

    void SetNewGameMenuItem();
    void SetSaveGameMenuItem();
    void SetLoadGameMenuItem();
    void SetQuitAppMenuItem();

    void SetGameModeSubMenu();
    void SetDisplayInfoMenuItem();
    void SetShowRulesMenuItem();

    //Event handler functions for menu items
    void OnNew(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnLoad(wxCommandEvent& event);
    void OnQuitApp(wxCommandEvent& event);

    void OnTwoPlayersGameMode(wxCommandEvent& event);
    void OnPlayerVsAiGameMode(wxCommandEvent& event);

    void OnDisplayInformation(wxCommandEvent& event);
    void OnShowGameRules(wxCommandEvent& event);

    void OnClose(wxCloseEvent& event);

    void MakeNewBoard();
private:

    bool is_game_saved_ = true;
    std::shared_ptr<Board> game_board_;

    //Smart pointers are not supported by wxWidgets
    //Memory will be freed by wxWidgets framework automatically after closing window
    wxMenuBar* menu_bar_;

    //Menus
    wxMenu* file_menu_;
    wxMenu* options_menu_;
    wxMenu* view_menu_;
    wxMenu* rules_menu_;

    //File menu items
    wxMenuItem* new_game_;
    wxMenuItem* save_game_;
    wxMenuItem* load_game_;
    wxMenuItem* quit_app_;

    
    //Options menu items
    wxMenu* game_mode_sub_menu_;
    
    //View menu items
    wxMenuItem* display_info_;

    //Rules menu items
    wxMenuItem* show_game_rules_;

    DECLARE_EVENT_TABLE()
}; 