#pragma once
#include "wxConstants.h"
#include "wxID.h"
#include "wx/artprov.h"
#include "BoardCanvas.h"

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

    void MakeNewGame();
private:

    bool is_game_saved_ = true;
    std::shared_ptr<BoardCanvas> game_;

    //Smart pointers are not supported by wxWidgets
    //Memory will be freed by wxWidgets framework automatically after closing window
    wxMenuBar* menu_bar_ = nullptr;

    //Menus
    wxMenu* file_menu_ = nullptr;
    wxMenu* options_menu_ = nullptr;
    wxMenu* view_menu_ = nullptr;
    wxMenu* rules_menu_ = nullptr;

    //File menu items
    wxMenuItem* new_game_ = nullptr;
    wxMenuItem* save_game_ = nullptr;
    wxMenuItem* load_game_ = nullptr;
    wxMenuItem* quit_app_ = nullptr;

    
    //Options menu items
    wxMenu* game_mode_sub_menu_ = nullptr;
    
    //View menu items
    wxMenuItem* display_info_ = nullptr;

    //Rules menu items
    wxMenuItem* show_game_rules_ = nullptr;

    DECLARE_EVENT_TABLE()
}; 