#include "newlwm2mdevice.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wxrc.h"
#include "serialport.h"
#include "wx/dir.h"
#include "wx/regex.h"
#include <thread>

#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif // __WXMSW__

static wxArrayString wxSerialPortGetPortNames()
{
    wxArrayString vStrPortNames;
#ifdef __WXMSW__
    wxRegKey regKey(wxRegKey::HKLM, wxS("HARDWARE\\DEVICEMAP\\SERIALCOMM"));

    if (!regKey.Exists())
        return vStrPortNames;

    wxASSERT(regKey.Exists());

    wxString strValueName;
    long lIndex;

    // Enumerate all values
    bool bCont = regKey.GetFirstValue(strValueName, lIndex);

    while (bCont)
    {
        wxRegKey::ValueType valueType = regKey.GetValueType(strValueName);

        if ((valueType == wxRegKey::Type_String || valueType == wxRegKey::Type_Expand_String ||
                valueType == wxRegKey::Type_Multi_String) && !strValueName.empty())
        {
            wxString strValueData;
            regKey.QueryValue(strValueName, strValueData);
            vStrPortNames.push_back(strValueData);
        }

        bCont = regKey.GetNextValue(strValueName, lIndex);
    }
#else // !__WXMSW__
    wxArrayString arrStrFiles;
    wxDir::GetAllFiles(wxS("/dev/"), &arrStrFiles, wxS("ttyUSB*"), wxDIR_FILES);

    for (wxArrayString::const_iterator it = arrStrFiles.begin(); it != arrStrFiles.end(); ++it)
        vStrPortNames.push_back(*it);

    arrStrFiles.Clear();
    wxDir::GetAllFiles(wxS("/dev/"), &arrStrFiles, wxS("ttyS*"), wxDIR_FILES);

    for (wxArrayString::const_iterator it = arrStrFiles.begin(); it != arrStrFiles.end(); ++it)
        vStrPortNames.push_back(*it);

#endif // __WXMSW__

    return vStrPortNames;
}


NewLwM2MDevice::NewLwM2MDevice(wxWindow *parent):NewLwM2MDeviceDialog(parent)
{
    {
        //显示LwM2MReadMe.txt文件
        const char * readme_txt=(const char *)wxRCGetHandle("NewLwM2MDeviceDialogManualReadMe.txt");
        if(readme_txt!=NULL)
        {
            m_textCtrl_NewLwM2MDevice_Manual_ReadMe->SetValue(wxString::FromUTF8(readme_txt));
        }

        readme_txt=(const char *)wxRCGetHandle("NewLwM2MDeviceDialogATReadMe.txt");
        if(readme_txt!=NULL)
        {
            m_textCtrl_NewLwM2MDevice_AT_ReadMe->SetValue(wxString::FromUTF8(readme_txt));
        }
    }
    {
        //设置扫描到的串口
        m_comboBox_NewLwM2MDevice_ComPort->Set(wxSerialPortGetPortNames());
    }
    {
        //从环境变量中获取上次数据

        //手工录入的AuthCode与PSK信息
        if(wxGetEnv(_T("LwM2MNewDeviceAuthCode"),&AuthCode))
        {
            m_textCtrl__NewLwM2MDevice_Manual_AuthCode->SetValue(AuthCode);
        }
        if(wxGetEnv(_T("LwM2MNewDevicePSK"),&PSK))
        {
            m_textCtrl__NewLwM2MDevice_Manual_PSK->SetValue(PSK);
        }

        //AT串口信息
        {
            wxString value;
            if(wxGetEnv(_T("LwM2MNewDeviceComPort"),&value))
            {
                m_comboBox_NewLwM2MDevice_ComPort->SetValue(value);
            }
        }
        {
            wxString value;
            if(wxGetEnv(_T("LwM2MNewDeviceDataRate"),&value))
            {
                m_comboBox_NewLwM2MDevice_DataRate->SetValue(value);
            }
        }
        {
            wxString value;
            if(wxGetEnv(_T("LwM2MNewDeviceDataBits"),&value))
            {
                long numval=0;
                if(value.ToLong(&numval))
                {
                    m_choice_NewLwM2MDevice_DataBits->SetSelection(numval);
                }
            }
        }
        {
            wxString value;
            if(wxGetEnv(_T("LwM2MNewDeviceStopBits"),&value))
            {
                long numval=0;
                if(value.ToLong(&numval))
                {
                    m_choice_NewLwM2MDevice_StopBits->SetSelection(numval);
                }
            }
        }
        {
            wxString value;
            if(wxGetEnv(_T("LwM2MNewDeviceFlowControl"),&value))
            {
                long numval=0;
                if(value.ToLong(&numval))
                {
                    m_choice_NewLwM2MDevice_FlowControl->SetSelection(numval);
                }
            }
        }
        {
            wxString value;
            if(wxGetEnv(_T("LwM2MNewDeviceParity"),&value))
            {
                long numval=0;
                if(value.ToLong(&numval))
                {
                    m_choice_NewLwM2MDevice_Parity->SetSelection(numval);
                }
            }
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

void NewLwM2MDevice::OnNewLwM2MDeviceATGet( wxCommandEvent& event )
{
    wxString ComPort=m_comboBox_NewLwM2MDevice_ComPort->GetValue();
    {
        if(ComPort.IsEmpty())
        {
            wxMessageBox(_T("串口不能为空!"),_T("错误"));
            return;
        }
    }

    long DataRate=0;
    {
        wxString DataRateStr=m_comboBox_NewLwM2MDevice_DataRate->GetValue();
        if(!DataRateStr.ToLong(&DataRate))
        {
            wxMessageBox(_T("波特率不合法!"),_T("错误"));
            return;
        }
    }

    long DataBits=0;
    {
        wxString DataBitsStr=m_choice_NewLwM2MDevice_DataBits->GetStringSelection();
        if(!DataBitsStr.ToLong(&DataBits))
        {
            wxMessageBox(_T("数据位不合法!"),_T("错误"));
            return;
        }
    }

    serialport::StopBits stopbits=serialport::SERIALPORT_STOPBITS_ONE;
    {
        wxString val=m_choice_NewLwM2MDevice_StopBits->GetStringSelection();
        if(val==_T("1"))
        {
            stopbits=serialport::SERIALPORT_STOPBITS_ONE;
        }
        if(val==_T("1.5"))
        {
            stopbits=serialport::SERIALPORT_STOPBITS_ONEHALF;
        }
        if(val==_T("2"))
        {
            stopbits=serialport::SERIALPORT_STOPBITS_TWO;
        }
    }
    serialport::FlowControl flowcontrol=serialport::SERIALPORT_FLOWCONTROL_NONE;
    {
        wxString val=m_choice_NewLwM2MDevice_FlowControl->GetStringSelection();
        if(val==_T("none"))
        {
            flowcontrol=serialport::SERIALPORT_FLOWCONTROL_NONE;
        }
        if(val==_T("software"))
        {
            flowcontrol=serialport::SERIALPORT_FLOWCONTROL_SOFT;
        }
        if(val==_T("hardware"))
        {
            flowcontrol=serialport::SERIALPORT_FLOWCONTROL_HARD;
        }
    }
    serialport::Parity parity=serialport::SERIALPORT_PARITY_NONE;
    {
        wxString val=m_choice_NewLwM2MDevice_Parity->GetStringSelection();
        if(val==_T("none"))
        {
            parity=serialport::SERIALPORT_PARITY_NONE;
        }
        if(val==_T("odd"))
        {
            parity=serialport::SERIALPORT_PARITY_ODD;
        }
        if(val==_T("even"))
        {
            parity=serialport::SERIALPORT_PARITY_EVEN;
        }
    }


    serialport sp;
    sp.open(ComPort.ToStdString());
    if(!sp.is_open())
    {
        wxMessageBox(_T("串口打开失败!"),_T("错误"));
        return;
    }

    sp.setdatarate(DataRate);
    sp.setdatabits(DataBits);
    sp.setstopbits(stopbits);
    sp.setflowcontrol(flowcontrol);
    sp.setparity(parity);

    {

        {
            wxString Send(_T("AT+CIMI\r\n"));
            wxLogMessage(_T("即将发送串口数据:\n%s\n"),Send);
            sp.write(Send.ToStdString());
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        {
            std::string data=sp.readall();
            if(!data.empty())
            {
                wxString Receive=wxString::FromUTF8(data.c_str());
                wxLogMessage(_T("接收到串口数据:\n%s\n"),Receive);
                wxRegEx IMSIReg(_T("[0-9]{14,15}"));
                if(!IMSIReg.IsValid())
                {
                    wxMessageBox(_T("正则表达式无效!"),_T("错误"));
                }
                if(IMSIReg.Matches(Receive))
                {
                    IMSI=IMSIReg.GetMatch(Receive,0);
                    m_textCtrl__NewLwM2MDevice_Manual_IMSI->SetValue(IMSI);
                }
                else
                {
                    wxMessageBox(_T("未读取到IMSI数据!"),_T("错误"));
                }
            }
            else
            {
                wxMessageBox(_T("未收到响应数据!"),_T("错误"));
                return;
            }
        }
    }

    {

        {
            wxString Send(_T("AT+CGSN=1\r\n"));
            wxLogMessage(_T("即将发送串口数据:\n%s\n"),Send);
            sp.write(Send.ToStdString());
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        {
            std::string data=sp.readall();
            if(!data.empty())
            {
                wxString Receive=wxString::FromUTF8(data.c_str());
                wxLogMessage(_T("接收到串口数据:\n%s\n"),Receive);
                wxRegEx IMEIReg(_T("[0-9]{15}(?:[0-9]{2})?"));
                if(!IMEIReg.IsValid())
                {
                   wxMessageBox(_T("正则表达式无效!"),_T("错误"));
                }
                if(IMEIReg.Matches(Receive))
                {
                    IMEI=IMEIReg.GetMatch(Receive,0);
                    m_textCtrl__NewLwM2MDevice_Manual_IMEI->SetValue(IMEI);
                    m_textCtrl_NewLwM2MDevice_Manual_DeviceName->SetValue(IMEI);
                }
                else
                {
                    wxMessageBox(_T("未读取到IMEI数据!"),_T("错误"));
                    return;
                }
            }
            else
            {
                wxMessageBox(_T("未收到响应数据!"),_T("错误"));
                return;
            }
        }
    }


    //切换到手工录入窗口
    m_auinotebook_NewLwM2MDevice->ChangeSelection(0);
}

NewLwM2MDevice::~NewLwM2MDevice()
{
    {
        //设置环境变量

        //手工录入的AuthCode与PSK信息
        AuthCode=m_textCtrl__NewLwM2MDevice_Manual_AuthCode->GetValue();
        PSK=m_textCtrl__NewLwM2MDevice_Manual_PSK->GetValue();
        wxSetEnv(_T("LwM2MNewDeviceAuthCode"),AuthCode);
        wxSetEnv(_T("LwM2MNewDevicePSK"),PSK);

        //AT串口信息
        wxSetEnv(_T("LwM2MNewDeviceComPort"),m_comboBox_NewLwM2MDevice_ComPort->GetValue());
        wxSetEnv(_T("LwM2MNewDeviceDataRate"),m_comboBox_NewLwM2MDevice_DataRate->GetValue());
        wxSetEnv(_T("LwM2MNewDeviceDataBits"),wxString::Format(_T("%d"),m_choice_NewLwM2MDevice_DataBits->GetSelection()));
        wxSetEnv(_T("LwM2MNewDeviceStopBits"),wxString::Format(_T("%d"),m_choice_NewLwM2MDevice_StopBits->GetSelection()));
        wxSetEnv(_T("LwM2MNewDeviceFlowControl"),wxString::Format(_T("%d"),m_choice_NewLwM2MDevice_FlowControl->GetSelection()));
        wxSetEnv(_T("LwM2MNewDeviceParity"),wxString::Format(_T("%d"),m_choice_NewLwM2MDevice_Parity->GetSelection()));

    }
}
