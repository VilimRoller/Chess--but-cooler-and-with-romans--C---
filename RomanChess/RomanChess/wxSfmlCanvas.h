//Jeff DeWall's implementation of integrating SFML into wxWidgets: https://gitlab.com/sr.jilarious/wx_sfml/-/tree/master/
#pragma once

#include <SFML/Graphics.hpp>
#include <wx/wx.h>

class wxSfmlCanvas : 
    public wxControl, 
    public sf::RenderWindow
{
public:
    wxSfmlCanvas(wxWindow* Parent = nullptr,
        wxWindowID Id = -1,
        const wxPoint& Position = wxDefaultPosition,
        const wxSize& Size = wxDefaultSize,
        long Style = 0);

    virtual ~wxSfmlCanvas();

protected:

    virtual void OnUpdate();

    void OnIdle(wxIdleEvent&);

    void OnPaint(wxPaintEvent&);

    void OnEraseBackground(wxEraseEvent&);

    void OnSize(wxSizeEvent&);
    DECLARE_EVENT_TABLE()
};
