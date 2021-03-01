#include "ChessApp.h"
#include "MainWindow.h"
#include "BadInputException.h"
#include <system_error>
#include <future>
#include <new>


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
	try {
		throw;
	}

	catch (const BadInputException& exception) {
		wxString bad_input_message = exception.what();
		wxLogError("Bad input exception has occurred: %s. \nProgram will now terminate", bad_input_message);
	}

	catch (const std::system_error& exception) {
		wxString system_error_message = exception.what();
		wxLogError("System error exception has occurred: %s. \nProgram will now terminate", system_error_message);
	}

	catch (const std::future_error& exception) {
		wxString future_error_message = exception.what();
		wxLogError("Future error exception has occurred: %s. \nProgram will now terminate", future_error_message);
	}

	catch (const std::bad_alloc& exception) {
		wxString bad_alloc_message = exception.what();
		wxLogError("Bad alloc exception has occurred: %s. \nProgram will now terminate", bad_alloc_message);
	}

	return false;
}
