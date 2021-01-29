#include "ChessApp.h"
#include "MainWindow.h"
#include "BadColourException.h"

wxIMPLEMENT_APP(ChessApp);

ChessApp::ChessApp() {
};

bool ChessApp::OnInit() {

	if (!wxApp::OnInit()) {
		return false;
	}

	MainWindow* main = new MainWindow(nullptr, Window::ID::MAIN_WINDOW, wxConstantStrings::ApplicationName, wxConstants::MainWindowPoint, wxConstants::MainWindowSize);
	main->Show(true);

	return true;
}

bool ChessApp::OnExceptionInMainLoop() {
	wxString error_message;

	try {
		throw;
	}

	catch (const BadColourException& exception) {
		error_message = exception.what();
	}

	wxLogError("Exception has occured in function: %s. \nProgram will now terminate", error_message);

	return false;
}
