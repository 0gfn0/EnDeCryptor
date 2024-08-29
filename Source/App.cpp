#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
	MainFrame* mainframe = new MainFrame("EnDeCoder");
	mainframe->SetClientSize(500, 300);
	mainframe->Center();
	mainframe->Show();
	return true;
}

