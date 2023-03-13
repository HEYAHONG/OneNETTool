///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/valgen.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/scrolwin.h>
#include <wx/menu.h>
#include <wx/dataview.h>
#include <wx/aui/auibook.h>
#include <wx/statusbr.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/statline.h>
#include <wx/hyperlink.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define ID_MenuFileSubExit 1000
#define ID_MenuLinksSubOneNET 1001
#define ID_MenuLinksSubOneNETToken 1002
#define ID_MenuHelpAbout 1003

///////////////////////////////////////////////////////////////////////////////
/// Class MainFrame
///////////////////////////////////////////////////////////////////////////////
class MainFrame : public wxFrame
{
	private:

	protected:
		wxAuiNotebook* m_main;
		wxScrolledWindow* m_token;
		wxStaticText* m_staticText_tokenversion;
		wxChoice* m_choice_tokenversion;
		wxStaticText* m_staticText_tokenmethod;
		wxChoice* m_choice_tokenmethod;
		wxStaticText* m_staticText_tokenet;
		wxChoice* m_choice_tokenet;
		wxTextCtrl* m_textCtrl_tokenet;
		wxStaticText* m_staticText_tokenres;
		wxChoice* m_choice_tokenres;
		wxTextCtrl* m_textCtrl_tokenres_productid;
		wxTextCtrl* m_textCtrl_tokenres_devicename;
		wxTextCtrl* m_textCtrl_tokenres_res;
		wxStaticText* m_staticText_tokenkey;
		wxTextCtrl* m_textCtrl_tokenkey;
		wxButton* m_button_tokengenerate;
		wxScrolledWindow* m_LwM2MDeviceList;
		wxMenu* m_menu_LwM2MDeviceList;
		wxDataViewListCtrl* m_dataViewListCtrl_LwM2MDeviceList;
		wxDataViewColumn* m_dataViewListColumn_LwM2MDeviceList_DeviceName;
		wxDataViewColumn* m_dataViewListColumn_LwM2MDeviceList_IMEI;
		wxDataViewColumn* m_dataViewListColumn_LwM2MDeviceList_IMSI;
		wxDataViewColumn* m_dataViewListColumn_LwM2MDeviceList_AuthCode;
		wxDataViewColumn* m_dataViewListColumn_LwM2MDeviceList_PSK;
		wxTextCtrl* m_textCtrl_LwM2MDeviceList;
		wxButton* m_button_LwM2MDeviceList_ClearAll;
		wxButton* m_button_LwM2MDeviceList_Save;
		wxMenuBar* m_menubar;
		wxMenu* MenuFile;
		wxMenu* MenuLinks;
		wxMenu* MenuHelp;
		wxStatusBar* m_statusBar;
		wxAuiNotebook* m_bottom;
		wxPanel* m_log;
		wxTextCtrl* m_log_textCtrl;

		// Virtual event handlers, override them in your derived class
		virtual void OnTokenSize( wxSizeEvent& event ) { event.Skip(); }
		virtual void OnTokenetChoiceUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTokenetTextUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTokenresChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTokenGenerateButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuLwM2MDeviceListClearAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuLwM2MDeviceListRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLwM2MDeviceListContextMenu( wxDataViewEvent& event ) { event.Skip(); }
		virtual void OnButtonLwM2MDeviceListClearAllClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLwM2MDeviceListSaveButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuFileSubExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuLinksSubOneNET( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuLinksSubOneNETToken( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnMenuHelpAbout( wxCommandEvent& event ) { event.Skip(); }


	public:
		int m_textCtrl_tokenet_validator;

		MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("OneNETTool"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1024,768 ), long style = wxCAPTION|wxCLOSE_BOX|wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;

		~MainFrame();

		void m_LwM2MDeviceListOnContextMenu( wxMouseEvent &event )
		{
			m_LwM2MDeviceList->PopupMenu( m_menu_LwM2MDeviceList, event.GetPosition() );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog
///////////////////////////////////////////////////////////////////////////////
class AboutDialog : public wxDialog
{
	private:

	protected:
		wxAuiNotebook* m_abouttab;
		wxScrolledWindow* m_scrolledWindow_info;
		wxStaticText* m_staticText_info_version;
		wxStaticText* m_staticText_info_version_str;
		wxStaticLine* m_staticline_1;
		wxStaticText* m_staticText_Info_author;
		wxHyperlinkCtrl* m_hyperlink_info_author_hyh_github;
		wxHyperlinkCtrl* m_hyperlink_info_author_hyh_gitee;
		wxStaticLine* m_staticline_2;
		wxStaticText* m_staticText_info_depends;
		wxHyperlinkCtrl* m_hyperlink_depends_wxwidgets;
		wxHyperlinkCtrl* m_hyperlink_depends_mbedtls;
		wxPanel* m_panel_license;
		wxRichTextCtrl* m_richText_license;

	public:

		AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("关于"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER );
		wxAuiManager m_mgr;

		~AboutDialog();

};

