#ifndef FRAME_H
#define FRAME_H
#include "GUIFrame.h"
#include "wxrc.h"

class App;

class Frame:public MainFrame
{
public:
    Frame();
    virtual ~Frame();


protected:
    virtual void OnTokenSize( wxSizeEvent& event );
    virtual void OnTokenetChoiceUpdate( wxCommandEvent& event );
    virtual void OnTokenetTextUpdate( wxCommandEvent& event );
    virtual void OnTokenresChoice( wxCommandEvent& event );
    virtual void OnTokenGenerateButtonClick( wxCommandEvent& event );
    virtual void OnMenuFileSubExit( wxCommandEvent& event );
    virtual void OnMenuLinksSubOneNET( wxCommandEvent& event );
    virtual void OnMenuLinksSubOneNETToken( wxCommandEvent& event );
    virtual void OnMenuHelpAbout( wxCommandEvent& event );

private:
    App &app;
    wxTimer *UITimer;
    void UITimerEvent(wxTimerEvent& event)
    {
        app.ProcessUIEvent();
    }
};

#endif // FRAME_H
