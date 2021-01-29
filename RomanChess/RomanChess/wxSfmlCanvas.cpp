#include "wxSfmlCanvas.h"

BEGIN_EVENT_TABLE(wxSfmlCanvas, wxControl)

EVT_PAINT(wxSfmlCanvas::OnPaint)
EVT_IDLE(wxSfmlCanvas::OnIdle)
EVT_ERASE_BACKGROUND(wxSfmlCanvas::OnEraseBackground)

EVT_SIZE(wxSfmlCanvas::OnSize)

END_EVENT_TABLE()

#ifdef __WXGTK__
#include <gdk/gdkx.h>
#include <gtk/gtk.h>
#include <wx/gtk/win_gtk.h>
#endif

wxSfmlCanvas::wxSfmlCanvas(wxWindow* Parent,
    wxWindowID Id,
    const wxPoint& Position,
    const wxSize& Size,
    long Style) :
    wxControl(Parent, Id, Position, Size, Style)
{
#ifdef __WXGTK__

    // Untested code: Looks like this portion doesn't work according to a stack overflow
    // answer. 
    // TODO: Fix GTK implementation.
    // // GTK implementation requires to go deeper to find the
    // // low-level X11 identifier of the widget
    // gtk_widget_realize(m_wxwindow);
    // gtk_widget_set_double_buffered(m_wxwindow, false);
    // GdkWindow* Win = GTK_PIZZA(m_wxwindow)->bin_window;
    // XFlush(GDK_WINDOW_XDISPLAY(Win));
    // sf::RenderWindow::Create(GDK_WINDOW_XWINDOW(Win));

#else
    // Tested under Windows 10, not sure about Mac OS X
    sf::RenderWindow::create(GetHandle());

#endif
}

void wxSfmlCanvas::OnIdle(wxIdleEvent&)
{
    // Send a paint message when the control is idle, to ensure maximum framerate
    Refresh();
}

wxSfmlCanvas::~wxSfmlCanvas()
{
}

void wxSfmlCanvas::OnUpdate()
{
}

void wxSfmlCanvas::OnEraseBackground(wxEraseEvent&)
{

}

void wxSfmlCanvas::OnSize(wxSizeEvent& args)
{
    // Set the size of the sfml rendering window
    setSize(sf::Vector2u(args.GetSize().x, args.GetSize().y));

    // Also adjust the viewport so that a pixel stays 1-to-1.
    setView(sf::View(sf::FloatRect(0, 0, args.GetSize().x, args.GetSize().y)));
}

void wxSfmlCanvas::OnPaint(wxPaintEvent&)
{
    // Prepare the control to be repainted
    wxPaintDC Dc(this);

    // Let the derived class do its specific stuff
    OnUpdate();

    // Display on screen
    display();
}
