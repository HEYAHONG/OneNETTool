#include "about.h"
#include "wxrc.h"
#include "Version.h"
about::about(wxWindow *parent):AboutDialog(parent)
{
    {
        //加载LICENSE
        const char *license=(const char *)wxRCGetHandle("LICENSE");
        if(license!=NULL)
        {
            m_richText_license->SetValue(wxString::FromUTF8(license));
        }
    }

    {
        m_staticText_info_version_str->SetLabel(wxString::FromUTF8(PROJECT_VERSION_STR));
    }
}

about::~about()
{

}
