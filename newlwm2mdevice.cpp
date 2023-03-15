#include "newlwm2mdevice.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wxrc.h"
#include "serialport.h"

NewLwM2MDevice::NewLwM2MDevice(wxWindow *parent):NewLwM2MDeviceDialog(parent)
{
    {
        //显示LwM2MReadMe.txt文件
        const char * readme_txt=(const char *)wxRCGetHandle("NewLwM2MDeviceDialogManualReadMe.txt");
        if(readme_txt!=NULL)
        {
            m_textCtrl_NewLwM2MDevice_Manual_ReadMe->SetValue(wxString::FromUTF8(readme_txt));
        }
    }
    {
        //从环境变量中获取上次数据
        if(wxGetEnv(_T("LwM2MNewDeviceAuthCode"),&AuthCode))
        {
            m_textCtrl__NewLwM2MDevice_Manual_AuthCode->SetValue(AuthCode);
        }
        if(wxGetEnv(_T("LwM2MNewDevicePSK"),&PSK))
        {
            m_textCtrl__NewLwM2MDevice_Manual_PSK->SetValue(PSK);
        }
    }
}

void NewLwM2MDevice::OnNewLwM2MDeviceManualOK( wxCommandEvent& event )
{
    DeviceName=m_textCtrl_NewLwM2MDevice_Manual_DeviceName->GetValue();
    IMEI=m_textCtrl__NewLwM2MDevice_Manual_IMEI->GetValue();
    IMSI=m_textCtrl__NewLwM2MDevice_Manual_IMSI->GetValue();
    AuthCode=m_textCtrl__NewLwM2MDevice_Manual_AuthCode->GetValue();
    PSK=m_textCtrl__NewLwM2MDevice_Manual_PSK->GetValue();
    if(DeviceName.IsEmpty() || IMEI.IsEmpty() || IMSI.IsEmpty())
    {
        wxMessageBox(_T("带*号为必填项"),_T("错误"));
        return;
    }

    wxLogMessage(_T("添加新LwM2M设备:DeviceName=%s,IMEI=%s,IMSI=%s,AuthCode=%s,PSK=%s"),DeviceName,IMEI,IMSI,AuthCode,PSK);

    EndModal(wxID_OK);
}

NewLwM2MDevice::~NewLwM2MDevice()
{
    {
        //设置环境变量
        wxSetEnv(_T("LwM2MNewDeviceAuthCode"),AuthCode);
        wxSetEnv(_T("LwM2MNewDevicePSK"),PSK);
    }
}
