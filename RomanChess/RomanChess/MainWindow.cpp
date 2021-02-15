#include "MainWindow.h"


wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_NEW, MainWindow::OnNew)
    EVT_MENU(wxID_SAVE, MainWindow::OnSave)
    EVT_MENU(wxID_OPEN, MainWindow::OnLoad)
    EVT_MENU(wxID_EXIT, MainWindow::OnQuitApp)
    EVT_MENU(MenuItems::ID::TWO_PLAYERS_GAME_MODE, MainWindow::OnTwoPlayersGameMode)
    EVT_MENU(MenuItems::ID::PLAYER_VS_AI_MODE, MainWindow::OnPlayerVsAiGameMode)
    EVT_MENU(MenuItems::ID::DISPLAY_INFORMATION, MainWindow::OnDisplayInformation)
    EVT_MENU(MenuItems::ID::SHOW_GAME_RULES, MainWindow::OnShowGameRules)
    EVT_CLOSE(MainWindow::OnClose)
wxEND_EVENT_TABLE()


MainWindow::MainWindow(wxWindow* parent,
    wxWindowID id,
    const wxString& title,
    const wxPoint& pos,
    const wxSize& size,
    long style,
    const wxString& name): wxFrame(parent, id, title, pos, size, style, name) {


    InitializeMainWindow();
    SetMainWindowMenuBar();
    SetMainWindowMenus();
}

MainWindow::~MainWindow() {

}

void MainWindow::InitializeMainWindow() {
    InitializeMainWindowMenuBar();
    InitializeMainWindowMenuItems();
}

void MainWindow::InitializeMainWindowMenuBar() {
    menu_bar_ = new wxMenuBar();

    file_menu_ = new wxMenu();
    options_menu_ = new wxMenu();
    view_menu_ = new wxMenu();
    rules_menu_ = new wxMenu();
}
void MainWindow::InitializeMainWindowMenuItems() {
    InitializeFileMenuItems();
    InitializeOptionsMenuItems();
    InitializeViewMenuItems();
    InitializeRulesMenuItems();}

void MainWindow::InitializeFileMenuItems() {
    new_game_ = new wxMenuItem(file_menu_, wxID_NEW);
    save_game_ = new wxMenuItem(file_menu_, wxID_SAVE);
    load_game_ = new wxMenuItem(file_menu_, wxID_OPEN);
    quit_app_ = new wxMenuItem(file_menu_, wxID_EXIT);
}

void MainWindow::InitializeOptionsMenuItems() {
    game_mode_sub_menu_ = new wxMenu();
}

void MainWindow::InitializeViewMenuItems() {
    display_info_ = new wxMenuItem(view_menu_, MenuItems::ID::DISPLAY_INFORMATION, wxConstantStrings::DisplayInformation);
}

void MainWindow::InitializeRulesMenuItems() {
    show_game_rules_ = new wxMenuItem(rules_menu_, MenuItems::ID::SHOW_GAME_RULES, wxConstantStrings::DisplayRules);
}


void MainWindow::SetMainWindowMenuBar() {

    menu_bar_->Append(file_menu_, wxConstantStrings::File);
    menu_bar_->Append(options_menu_, wxConstantStrings::Options);
    menu_bar_->Append(view_menu_, wxConstantStrings::View);
    menu_bar_->Append(rules_menu_, wxConstantStrings::Rules);

    SetMenuBar(menu_bar_);
}


void MainWindow::DeleteMainWindowMenuBar() {
 
}

void MainWindow::SetMainWindowMenus() {
    SetFileMenu();
    SetOptionsMenu();
    SetViewMenu();
    SetRulesMenu();
}

void MainWindow::SetFileMenu() {
    SetNewGameMenuItem();
    SetSaveGameMenuItem();
    SetLoadGameMenuItem();
    SetQuitAppMenuItem();
}

void MainWindow::SetOptionsMenu() {
    SetGameModeSubMenu();
}

void MainWindow::SetViewMenu() {
    SetDisplayInfoMenuItem();
}

void MainWindow::SetRulesMenu() {
    SetShowRulesMenuItem();
}

void MainWindow::SetNewGameMenuItem() {
    new_game_->SetItemLabel(wxConstantStrings::NewGame);
    new_game_->SetBitmap(wxArtProvider::GetBitmap(wxART_NEW));
    file_menu_->Append(new_game_);
}

void MainWindow::SetSaveGameMenuItem() {
    save_game_->SetItemLabel(wxConstantStrings::SaveGame);
    save_game_->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_SAVE));
    file_menu_->Append(save_game_);
}

void MainWindow::SetLoadGameMenuItem() {
    load_game_->SetItemLabel(wxConstantStrings::LoadGame);
    load_game_->SetBitmap(wxArtProvider::GetBitmap(wxART_FILE_OPEN));
    file_menu_->Append(load_game_);
}

void MainWindow::SetQuitAppMenuItem() {
    quit_app_->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT));
    file_menu_->AppendSeparator();
    file_menu_->Append(quit_app_);
}

void MainWindow::SetGameModeSubMenu() {

    game_mode_sub_menu_->Append(MenuItems::ID::TWO_PLAYERS_GAME_MODE, wxConstantStrings::TwoPlayers);
    game_mode_sub_menu_->Append(MenuItems::ID::PLAYER_VS_AI_MODE, wxConstantStrings::PlayerVsAI);
    options_menu_->AppendSubMenu(game_mode_sub_menu_, wxConstantStrings::GameMode);

}

void MainWindow::SetDisplayInfoMenuItem() {
    display_info_->SetItemLabel(wxConstantStrings::DisplayInformation);
    view_menu_->Append(display_info_);
}

void MainWindow::SetShowRulesMenuItem() {
    show_game_rules_->SetItemLabel(wxConstantStrings::DisplayGameRules);
    rules_menu_->Append(show_game_rules_);
}

void MainWindow::OnNew(wxCommandEvent& event) {
    MakeNewGame();


    
}

void MainWindow::OnSave(wxCommandEvent& event) {
    wxMessageBox("Main Window onSave function");
}

void MainWindow::OnLoad(wxCommandEvent& event) {
    wxMessageBox("Main Window onLoad function");
}

void MainWindow::OnQuitApp(wxCommandEvent& event) {
    wxMessageBox("Main Window onQuitApp function");
    bool veto = Close();
}

void MainWindow::OnTwoPlayersGameMode(wxCommandEvent& event) {
    wxMessageBox("Main Window onTwoPlayersGameMode function");
}

void MainWindow::OnPlayerVsAiGameMode(wxCommandEvent& event) {
    wxMessageBox("Main Window onPlayerVsAiGameMode function");
}

void MainWindow::OnDisplayInformation(wxCommandEvent& event) {
    wxMessageBox("Main Window onDisplayInformation function");
}

void MainWindow::OnShowGameRules(wxCommandEvent& event) {
    wxMessageBox("Main Window onShowGameRules function");
}

void MainWindow::OnClose(wxCloseEvent& event) {
    wxMessageBox("Main Window onClose function");

    if (event.CanVeto() && !is_game_saved_) {
        if (wxMessageBox(wxConstantStrings::FileNotSavedMessage,
            wxConstantStrings::FileNotSavedHeadline,
            wxICON_QUESTION | wxYES_NO) != wxYES) {
            event.Veto();
            return;
            }
        }
    Destroy();
}

void MainWindow::MakeNewGame() {
	wxPoint board_canvas_point{ wxConstants::BoardCanvasPoint };
	wxSize board_canvas_size{ wxConstants::BoardCanvasSize };

    game_ = std::make_shared<BoardCanvas>(this, Canvas::ID::BOARD_CANVAS, board_canvas_point, board_canvas_size, 0);
}