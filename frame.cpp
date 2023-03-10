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
            const char * readme_txt=(const char *)wxRCGetHandle("ReadMe.txt");
            if(readme_txt!=NULL)
            {
                wxLogMessage(_("%s"),wxString::FromUTF8(readme_txt));
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
