#ifndef NEWLWM2MDEVICE_H
#define NEWLWM2MDEVICE_H

#include "GUIFrame.h"

class NewLwM2MDevice:public NewLwM2MDeviceDialog
{
public:
    NewLwM2MDevice(wxWindow *parent);
    virtual ~NewLwM2MDevice();
    wxString DeviceName;
    wxString IMEI;
    wxString IMSI;
    wxString AuthCode;
    wxString PSK;

protected:
    virtual void OnNewLwM2MDeviceManualOK( wxCommandEvent& event );

private:
};

#endif // NEWLWM2MDEVICE_H
