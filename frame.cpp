#include "app.h"
#include "frame.h"
#include "wx/msgdlg.h"
#include "wx/log.h"
#include "wxrc.h"
#include "about.h"
#include "wx/time.h"
#include "wx/clipbrd.h"
#include "onenettoken.h"

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

wxString Frame::OneNETGetStringForSignature(wxString et,wxString method,wxString res,wxString version)
{
    return et+_T("\n")+method+_T("\n")+res+_T("\n")+version;
}

wxString Frame::OneNETGetUrlFormString(wxString et,wxString method,wxString res,wxString version,wxString sign)
{
    auto tourl=[](wxString &urlvalue)
    {
        urlvalue.Replace(_T("%"),_T("%25"));
        urlvalue.Replace(_T("+"),_T("%2B"));
        urlvalue.Replace(_T(" "),_T("%20"));
        urlvalue.Replace(_T("/"),_T("%2F"));
        urlvalue.Replace(_T("?"),_T("%3F"));
        urlvalue.Replace(_T("#"),_T("%23"));
        urlvalue.Replace(_T("&"),_T("%26"));
        urlvalue.Replace(_T("="),_T("%3D"));
    };
    tourl(et);
    tourl(method);
    tourl(res);
    tourl(version);
    tourl(sign);

    return wxString(_T("version="))+version+_T("&res=")+res+_T("&et=")+et+_T("&method=")+method+_T("&sign=")+sign;
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
        wxString StringForSignature=OneNETGetStringForSignature(et,method,res,version);
        uint8_t key_blob[key.length()]= {0};
        size_t  key_blob_length=OneNETBase64Decode(key_blob,sizeof(key_blob),(uint8_t *)key.ToAscii().data(),key.length());
        if(key_blob_length==0)
        {
            wxMessageBox(_T("密钥错误(可能不是Base64字符串)!"),_T("错误"));
            return;
        }
        OneNETTokenCryptoMethod method_enum=ONENET_CRYPTO_DEFAULT;
        if(method==_T("md5"))
        {
            method_enum=ONENET_CRYPTO_MD5;
        }
        if(method==_T("sha1"))
        {
            method_enum=ONENET_CRYPTO_SHA1;
        }
        if(method==_T("sha256"))
        {
            method_enum=ONENET_CRYPTO_SHA256;
        }

        uint8_t signout_blob[ONENET_HMAC_OUT_MAX]= {0};
        size_t signout_length=OneNETHmac(method_enum,signout_blob,sizeof(signout_blob),key_blob,key_blob_length,(uint8_t *)StringForSignature.ToStdString().c_str(),StringForSignature.ToStdString().length());
        if(signout_length==0)
        {
            wxMessageBox(_T("签署失败!"),_T("错误"));
            return;
        }
        const char sign[signout_length*4/3+4]= {0};
        size_t sign_length=OneNETBase64Encode((uint8_t *)sign,sizeof(sign),signout_blob,signout_length);
        if(sign_length==0)
        {
            wxMessageBox(_T("Base64加密错误!"),_T("错误"));
            return;
        }
        wxLogMessage(_T("签名成功:sign=%s"),wxString::FromUTF8(sign));
        token=OneNETGetUrlFormString(et,method,res,version,wxString::FromUTF8(sign));
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
