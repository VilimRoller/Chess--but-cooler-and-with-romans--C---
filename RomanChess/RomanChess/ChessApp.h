#pragma once
#include "wxConstants.h"


class ChessApp :
    public wxApp
{
public:
    ChessApp();
    bool OnInit() override;
    bool OnExceptionInMainLoop() override;

private:

};

wxDECLARE_APP(ChessApp);

