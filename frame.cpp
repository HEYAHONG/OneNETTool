#include "app.h"
#include "frame.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wxrc.h"
#include "about.h"
#include "wx/time.h"
#include "wx/clipbrd.h"
#include "onenettoken.h"
#include "onenettokencpp.h"
#include <wx/filedlg.h>
#include "xlsxio_write.h"
#include "xlsxio_read.h"


extern "C"
{
#include "icon.xpm"
}
Frame::Frame():MainFrame(NULL),app(*GetInstance())
{
    SetIcon(wxIcon(icon_xpm));

    {
        //设置日志
        wxLog::EnableLogging(true);
        {
            //设置日志窗口
            wxLogTextCtrl *logger=new wxLogTextCtrl(m_log_textCtrl);
            wxLog *oldlog=wxLog::SetActiveTarget(logger);
            if(oldlog!=NULL)
            {
                delete oldlog;
            }
        }

    }

    {
        //初始化UI刷新定时器
        UITimer=new wxTimer(this,wxID_APP_CUSTOM_FRAME_UITIMER);
        this->Connect(wxID_APP_CUSTOM_FRAME_UITIMER,wxID_APP_CUSTOM_FRAME_UITIMER,wxEVT_TIMER,wxTimerEventHandler(Frame::UITimerEvent));
        UITimer->Start(10);
    }

    //通过UI时间初始化界面
    app.AddUIEvent([=,this]()
    {
        {
            //显示ReadMe.txt文件
            const char * readme_txt=(const char *)wxRCGetHandle("ReadMe.txt");
            if(readme_txt!=NULL)
            {
                wxLogMessage(_("%s"),wxString::FromUTF8(readme_txt));
            }
        }
        {
            //显示LwM2MReadMe.txt文件
            const char * lwm2m_readme_txt=(const char *)wxRCGetHandle("LwM2MReadMe.txt");
            if(lwm2m_readme_txt!=NULL)
            {
                m_textCtrl_LwM2MDeviceList->SetValue(wxString::FromUTF8(lwm2m_readme_txt));
            }

        }
        {
            //设置token界面
            m_choice_tokenet->SetSelection(0);
            m_choice_tokenmethod->SetSelection(0);
            m_choice_tokenres->SetSelection(0);
            m_choice_tokenversion->SetSelection(0);
            m_textCtrl_tokenres_res->GetParent()->Hide();
            m_token->Layout();
        }

    });
}

void Frame::OnTokenSize( wxSizeEvent& event )
{
    m_choice_tokenversion->SetMinSize(wxSize(m_token->GetClientSize().GetWidth()/2-50,-1));
    m_token->Layout();
}

void Frame::OnTokenetChoiceUpdate( wxCommandEvent& event )
{
    switch(event.GetSelection())
    {
    case 0://当前时间戳+自定义时间
    {
        //需要对话框
        m_textCtrl_tokenet->Show();
        m_textCtrl_tokenet->SetValue(wxString::FromAscii(std::to_string(3600).c_str()));
    }
    break;
    case 1://最大Unix时间戳(会有2038问题)
    {
        //不需要对话框
        m_textCtrl_tokenet->SetValue(wxString::FromAscii(std::to_string(0x7FFFFFFF).c_str()));
        m_textCtrl_tokenet->Hide();
    }
    break;
    case 2://自定义Unix时间戳
    {
        //需要对话框
        m_textCtrl_tokenet->Show();
        m_textCtrl_tokenet->SetValue(wxString::FromAscii(std::to_string(3600ULL+wxDateTime::GetTimeNow()).c_str()));
    }
    break;
    default:
        break;
    }

    m_token->Layout();
}
void Frame::OnTokenetTextUpdate( wxCommandEvent& event )
{
    wxString data=event.GetString();
    long val=-1;
    if(data.ToLong(&val))
    {
        if(val < 0)
        {
            if(m_textCtrl_tokenet->CanUndo())
            {
                m_textCtrl_tokenet->Undo();
            }
        }
    }
    else
    {
        if(m_textCtrl_tokenet->CanUndo())
        {
            m_textCtrl_tokenet->Undo();
        }
    }
}

void Frame::OnTokenresChoice( wxCommandEvent& event )
{
    switch(event.GetSelection())
    {
    case 0://设备访问API
    {
        m_textCtrl_tokenres_productid->GetParent()->Show();
        m_textCtrl_tokenres_devicename->GetParent()->Show();
        m_textCtrl_tokenres_res->GetParent()->Hide();
    }
    break;
    case 1://产品访问API
    {
        m_textCtrl_tokenres_productid->GetParent()->Show();
        m_textCtrl_tokenres_devicename->GetParent()->Hide();
        m_textCtrl_tokenres_res->GetParent()->Hide();
    }
    break;
    case 2://自定义资源
    {
        m_textCtrl_tokenres_productid->GetParent()->Hide();
        m_textCtrl_tokenres_devicename->GetParent()->Hide();
        m_textCtrl_tokenres_res->GetParent()->Show();
    }
    break;
    default:
        break;
    }
    m_token->Layout();
}

void Frame::OnTokenGenerateButtonClick( wxCommandEvent& event )
{
    wxString version=m_choice_tokenversion->GetStringSelection();
    wxString method=m_choice_tokenmethod->GetStringSelection();
    wxString et;
    switch(m_choice_tokenet->GetSelection())
    {
    case 0://当前时间戳+自定义时间
    {
        long new_t=0;
        m_textCtrl_tokenet->GetValue().ToLong(&new_t);
        et=wxString::FromAscii(std::to_string(wxDateTime::GetTimeNow()+new_t).c_str());

    }
    break;
    case 1://最大Unix时间戳(会有2038问题)
    {
        et=wxString::FromAscii(std::to_string(0x7FFFFFFF).c_str());
    }
    break;
    case 2://自定义Unix时间戳
    {
        et=m_textCtrl_tokenet->GetValue();
    }
    break;
    default:
        break;
    }
    wxString res;
    switch(m_choice_tokenres->GetSelection())
    {
    case 0://设备访问API
    {
        wxString pid=m_textCtrl_tokenres_productid->GetValue();
        if(pid.IsEmpty())
        {
            wxMessageBox(_T("产品ID不能为空!"),_T("错误"));
            return;
        }
        wxString devicename=m_textCtrl_tokenres_devicename->GetValue();
        if(devicename.IsEmpty())
        {
            wxMessageBox(_T("设备名称不能为空!"),_T("错误"));
            return;
        }
        res=wxString(_T("products/"))+pid+_T("/devices/")+devicename;
    }
    break;
    case 1://产品访问API
    {
        wxString pid=m_textCtrl_tokenres_productid->GetValue();
        if(pid.IsEmpty())
        {
            wxMessageBox(_T("产品ID不能为空!"),_T("错误"));
            return;
        }
        res=wxString(_T("products/"))+pid;
    }
    break;
    case 2://自定义资源
    {
        res=m_textCtrl_tokenres_res->GetValue();
        if(res.IsEmpty())
        {
            wxMessageBox(_T("资源不能为空!"),_T("错误"));
            return;
        }

    }
    break;
    default:
        break;
    }
    wxString key;
    {
        key=m_textCtrl_tokenkey->GetValue();
        if(key.IsEmpty())
        {
            wxMessageBox(_T("密钥不能为空!"),_T("错误"));
            return;
        }
    }
    wxLogMessage(_T("即将生成token,参数:version=%s,et=%s,method=%s,res=%s,key=%s"),version,et,method,res,key);
    wxString token;
    {
        long long et_val=0;
        et.ToLongLong(&et_val);
        std::string sign=OneNETTokenGetSign((time_t)et_val,res.ToStdString(),key.ToStdString(),method.ToStdString(),version.ToStdString());
        if(sign.empty())
        {
            wxLogMessage(_T("签名失败"),_T("错误"));
            return;
        }
        wxLogMessage(_T("签名成功:sign=%s"),wxString::FromUTF8(sign.c_str()));
        token=wxString::FromUTF8(OneNETTokenGenerateURLToken((time_t)et_val,res.ToStdString(),sign,method.ToStdString(),version.ToStdString()).c_str());
        wxLogMessage(_T("token已生成:%s"),token);
    }
    if (wxTheClipboard->Open())
    {
        wxTheClipboard->SetData(new wxTextDataObject(token));
        wxTheClipboard->Close();
        wxMessageBox(_T("Token已复制到剪帖板!"),_T("提示"));
    }


}

void  Frame::OnMenuLwM2MDeviceListClearAll( wxCommandEvent& event )
{
    ClearAllLwM2MDevice();
}

void Frame::OnMenuLwM2MDeviceListRemove( wxCommandEvent& event )
{
    if(m_dataViewListCtrl_LwM2MDeviceList->GetSelectedRow() >=0)
    {
        RemoveLwM2MDevice(m_dataViewListCtrl_LwM2MDeviceList->GetSelectedRow());
    }
}

void Frame::OnLwM2MDeviceListContextMenu( wxDataViewEvent& event )
{

    PopupMenu(m_menu_LwM2MDeviceList);
}

void Frame::OnLwM2MDeviceListSaveButtonClick( wxCommandEvent& event )
{
    wxFileDialog savedlg(this,_T("请选择保存路径:"),wxEmptyString,wxEmptyString,_T("XLSX 文件 | *.xlsx"),wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    if(savedlg.ShowModal()==wxID_OK)
    {
        xlsxiowriter handle=xlsxiowrite_open(savedlg.GetPath().ToStdString().c_str(),"Sheet1");
        if(handle!=NULL)
        {
            xlsxiowrite_set_row_height(handle, 1);
            xlsxiowrite_add_cell_string(handle,"DeviceName");
            xlsxiowrite_add_cell_string(handle,"IMEI");
            xlsxiowrite_add_cell_string(handle,"IMSI");
            xlsxiowrite_add_cell_string(handle,"AuthCode");
            xlsxiowrite_add_cell_string(handle,"PSK");
            xlsxiowrite_next_row(handle);

            for(auto LwM2MDevice:LwM2MDeviceList)
            {
                xlsxiowrite_add_cell_string(handle,LwM2MDevice.DeviceName.ToStdString().c_str());
                xlsxiowrite_add_cell_string(handle,LwM2MDevice.IMEI.ToStdString().c_str());
                xlsxiowrite_add_cell_string(handle,LwM2MDevice.IMSI.ToStdString().c_str());
                xlsxiowrite_add_cell_string(handle,LwM2MDevice.AuthCode.ToStdString().c_str());
                xlsxiowrite_add_cell_string(handle,LwM2MDevice.PSK.ToStdString().c_str());
                xlsxiowrite_next_row(handle);
            }

            xlsxiowrite_close(handle);
        }
        else
        {
            wxMessageBox(_T("写入失败!"),_T("错误"));
        }
    }
}

void Frame::OnButtonLwM2MDeviceListClearAllClick( wxCommandEvent& event )
{
    ClearAllLwM2MDevice();
}

void Frame::OnMenuFileSubExit( wxCommandEvent& event )
{
    Destroy();
}

void Frame::OnMenuLinksSubOneNET( wxCommandEvent& event )
{
    //打开OneNET地址
    wxLaunchDefaultBrowser(_("https://open.iot.10086.cn/"));
}

void Frame::OnMenuLinksSubOneNETToken( wxCommandEvent& event )
{
    //打开OneNET Token算法地址
    wxLaunchDefaultBrowser(_T("https://open.iot.10086.cn/doc/v5/develop/detail/473"));

}

void Frame::OnMenuHelpAbout( wxCommandEvent& event )
{
    about dlg(this);
    dlg.ShowModal();
}

void Frame::ClearAllLwM2MDevice()
{
    auto cb=[=,this]()
    {
        LwM2MDeviceList.clear();
        m_dataViewListCtrl_LwM2MDeviceList->DeleteAllItems();
    };
    app.AddUIEvent(cb);
}

void Frame::AddLwM2MDevice(LwM2MDevice device)
{
    auto cb=[=,this]()
    {
        if(device.DeviceName.IsEmpty() || device.IMEI.IsEmpty() || device.IMSI.IsEmpty())
        {
            return;
        }
        LwM2MDeviceList.push_back(device);
        {
            wxVector<wxVariant> data;
            data.push_back(device.DeviceName);
            data.push_back(device.IMEI);
            data.push_back(device.IMSI);
            data.push_back(device.AuthCode);
            data.push_back(device.PSK);
            m_dataViewListCtrl_LwM2MDeviceList->AppendItem(data);
        }
    };
    app.AddUIEvent(cb);
}

void Frame::RemoveLwM2MDevice(size_t index)
{
    auto cb=[=,this]()
    {
        if(index >= LwM2MDeviceList.size())
        {
            return;
        }
        std::vector<LwM2MDevice>::iterator it=LwM2MDeviceList.begin();
        std::advance(it,index);
        LwM2MDeviceList.erase(it);
        m_dataViewListCtrl_LwM2MDeviceList->DeleteItem(index);
    };
    app.AddUIEvent(cb);
}

Frame::~Frame()
{
    {
        //关闭UI刷新定时器
        UITimer->Stop();
        delete UITimer;
        UITimer=NULL;
    }
    {
        //关闭日志
        wxLog::DontCreateOnDemand();
        wxLog *log=wxLog::SetActiveTarget(new wxLogStderr);
        if(log!=NULL)
        {
            delete log;
        }

    }
}
