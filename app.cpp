#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "app.h"
#include "frame.h"
#include "wx/image.h"
#include "wx/fs_mem.h"

IMPLEMENT_APP(App);

bool App::OnInit()
{
    Frame *frame=NULL;
    {
        //创建主窗口
        wxInitAllImageHandlers();
        frame= new Frame;
        frame->Show(true);
    }
    return true;
}

int App::OnExit()
{
    for(const std::function<void()> &cb:OnExitEvent)
    {
        if(cb!=NULL)
        {
            cb();
        }
    }
    return wxApp::OnExit();
}


App * 	GetInstance()
{
    return dynamic_cast<App  *>(wxAppConsole::GetInstance());
}
