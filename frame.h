#ifndef FRAME_H
#define FRAME_H
#include "GUIFrame.h"
#include "wxrc.h"
#include <vector>

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
    virtual void OnMenuLwM2MDeviceAdd( wxCommandEvent& event );
    virtual void OnMenuLwM2MDeviceListClearAll( wxCommandEvent& event );
    virtual void OnMenuLwM2MDeviceListRemove( wxCommandEvent& event );
    virtual void OnLwM2MDeviceListContextMenu( wxDataViewEvent& event );
    virtual void OnLwM2MDeviceListSaveButtonClick( wxCommandEvent& event );
    virtual void OnButtonLwM2MDeviceListClearAllClick( wxCommandEvent& event );
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

    //LwM2MDevice列表
    typedef struct
    {
        wxString DeviceName;
        wxString IMEI;
        wxString IMSI;
        wxString AuthCode;
        wxString PSK;
    } LwM2MDevice;
    std::vector<LwM2MDevice> LwM2MDeviceList;
    void ClearAllLwM2MDevice();
    void AddLwM2MDevice(LwM2MDevice device);
    void RemoveLwM2MDevice(size_t index);

};

#endif // FRAME_H
