///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_main = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_mgr.AddPane( m_main, wxAuiPaneInfo() .Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );

	m_token = new wxScrolledWindow( m_main, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_token->SetScrollRate( 5, 5 );
	wxFlexGridSizer* fgSizer_token;
	fgSizer_token = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer_token->SetFlexibleDirection( wxVERTICAL );
	fgSizer_token->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxGridSizer* gSizer_tokenversion;
	gSizer_tokenversion = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText_tokenversion = new wxStaticText( m_token, wxID_ANY, wxT("版本:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_tokenversion->Wrap( -1 );
	gSizer_tokenversion->Add( m_staticText_tokenversion, 0, wxALL|wxALIGN_CENTER_VERTICAL|wxALIGN_RIGHT, 5 );

	wxString m_choice_tokenversionChoices[] = { wxT("2018-10-31") };
	int m_choice_tokenversionNChoices = sizeof( m_choice_tokenversionChoices ) / sizeof( wxString );
	m_choice_tokenversion = new wxChoice( m_token, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_tokenversionNChoices, m_choice_tokenversionChoices, 0 );
	m_choice_tokenversion->SetSelection( 0 );
	m_choice_tokenversion->SetHelpText( wxT("参数组版本号") );
	m_choice_tokenversion->SetMinSize( wxSize( 300,-1 ) );

	gSizer_tokenversion->Add( m_choice_tokenversion, 1, wxALL|wxEXPAND, 5 );


	fgSizer_token->Add( gSizer_tokenversion, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer_tokenmethod;
	gSizer_tokenmethod = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText_tokenmethod = new wxStaticText( m_token, wxID_ANY, wxT("签名方法:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_tokenmethod->Wrap( -1 );
	gSizer_tokenmethod->Add( m_staticText_tokenmethod, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choice_tokenmethodChoices[] = { wxT("md5"), wxT("sha1"), wxT("sha256") };
	int m_choice_tokenmethodNChoices = sizeof( m_choice_tokenmethodChoices ) / sizeof( wxString );
	m_choice_tokenmethod = new wxChoice( m_token, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_tokenmethodNChoices, m_choice_tokenmethodChoices, 0 );
	m_choice_tokenmethod->SetSelection( 0 );
	m_choice_tokenmethod->SetHelpText( wxT("签名方法") );

	gSizer_tokenmethod->Add( m_choice_tokenmethod, 1, wxALL|wxEXPAND, 5 );


	fgSizer_token->Add( gSizer_tokenmethod, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer_tokenet;
	gSizer_tokenet = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText_tokenet = new wxStaticText( m_token, wxID_ANY, wxT("访问过期时间:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_tokenet->Wrap( -1 );
	gSizer_tokenet->Add( m_staticText_tokenet, 0, wxALL|wxALIGN_RIGHT, 5 );

	wxBoxSizer* bSizer_tokenet;
	bSizer_tokenet = new wxBoxSizer( wxVERTICAL );

	wxString m_choice_tokenetChoices[] = { wxT("当前时间戳+自定义时间"), wxT("最大的Unix时间戳"), wxT("自定义Unix时间戳") };
	int m_choice_tokenetNChoices = sizeof( m_choice_tokenetChoices ) / sizeof( wxString );
	m_choice_tokenet = new wxChoice( m_token, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_tokenetNChoices, m_choice_tokenetChoices, 0 );
	m_choice_tokenet->SetSelection( 0 );
	bSizer_tokenet->Add( m_choice_tokenet, 1, wxALL|wxEXPAND, 5 );

	m_textCtrl_tokenet = new wxTextCtrl( m_token, wxID_ANY, wxT("3600"), wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl_tokenet->SetValidator( wxGenericValidator( &m_textCtrl_tokenet_validator ) );

	bSizer_tokenet->Add( m_textCtrl_tokenet, 0, wxALL|wxEXPAND, 5 );


	gSizer_tokenet->Add( bSizer_tokenet, 1, wxEXPAND, 5 );


	fgSizer_token->Add( gSizer_tokenet, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer_tokenres;
	gSizer_tokenres = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText_tokenres = new wxStaticText( m_token, wxID_ANY, wxT("访问资源:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_tokenres->Wrap( -1 );
	gSizer_tokenres->Add( m_staticText_tokenres, 0, wxALL|wxALIGN_RIGHT, 5 );

	wxBoxSizer* bSizer_tokenres;
	bSizer_tokenres = new wxBoxSizer( wxVERTICAL );

	wxString m_choice_tokenresChoices[] = { wxT("设备连接API"), wxT("产品访问API"), wxT("自定义资源") };
	int m_choice_tokenresNChoices = sizeof( m_choice_tokenresChoices ) / sizeof( wxString );
	m_choice_tokenres = new wxChoice( m_token, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_tokenresNChoices, m_choice_tokenresChoices, 0 );
	m_choice_tokenres->SetSelection( 0 );
	bSizer_tokenres->Add( m_choice_tokenres, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer_tokenres_productid;
	sbSizer_tokenres_productid = new wxStaticBoxSizer( new wxStaticBox( m_token, wxID_ANY, wxT("产品ID") ), wxVERTICAL );

	m_textCtrl_tokenres_productid = new wxTextCtrl( sbSizer_tokenres_productid->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer_tokenres_productid->Add( m_textCtrl_tokenres_productid, 0, wxALL|wxEXPAND, 5 );


	bSizer_tokenres->Add( sbSizer_tokenres_productid, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer_tokenres_devicename;
	sbSizer_tokenres_devicename = new wxStaticBoxSizer( new wxStaticBox( m_token, wxID_ANY, wxT("设备名称") ), wxVERTICAL );

	m_textCtrl_tokenres_devicename = new wxTextCtrl( sbSizer_tokenres_devicename->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer_tokenres_devicename->Add( m_textCtrl_tokenres_devicename, 1, wxALL|wxEXPAND, 5 );


	bSizer_tokenres->Add( sbSizer_tokenres_devicename, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer_tokenres_res;
	sbSizer_tokenres_res = new wxStaticBoxSizer( new wxStaticBox( m_token, wxID_ANY, wxT("资源路径") ), wxVERTICAL );

	m_textCtrl_tokenres_res = new wxTextCtrl( sbSizer_tokenres_res->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer_tokenres_res->Add( m_textCtrl_tokenres_res, 1, wxALL|wxEXPAND, 5 );


	bSizer_tokenres->Add( sbSizer_tokenres_res, 1, wxEXPAND, 5 );


	gSizer_tokenres->Add( bSizer_tokenres, 1, wxEXPAND, 5 );


	fgSizer_token->Add( gSizer_tokenres, 1, wxEXPAND, 5 );

	wxGridSizer* gSizer_tokenkey;
	gSizer_tokenkey = new wxGridSizer( 0, 2, 0, 0 );

	m_staticText_tokenkey = new wxStaticText( m_token, wxID_ANY, wxT("访问密钥:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_tokenkey->Wrap( -1 );
	gSizer_tokenkey->Add( m_staticText_tokenkey, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl_tokenkey = new wxTextCtrl( m_token, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_textCtrl_tokenkey->SetHelpText( wxT("访问密钥。设备连接可以使用设备密钥或产品密钥。访问产品必须使用产品密钥。") );

	gSizer_tokenkey->Add( m_textCtrl_tokenkey, 1, wxALL|wxEXPAND, 5 );


	fgSizer_token->Add( gSizer_tokenkey, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer_tokengenerate;
	bSizer_tokengenerate = new wxBoxSizer( wxVERTICAL );

	m_button_tokengenerate = new wxButton( m_token, wxID_ANY, wxT("生成"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_tokengenerate->Add( m_button_tokengenerate, 0, wxALL|wxALIGN_RIGHT, 5 );


	fgSizer_token->Add( bSizer_tokengenerate, 1, wxEXPAND, 5 );


	m_token->SetSizer( fgSizer_token );
	m_token->Layout();
	fgSizer_token->Fit( m_token );
	m_main->AddPage( m_token, wxT("Token"), false, wxNullBitmap );

	m_menubar = new wxMenuBar( 0 );
	MenuFile = new wxMenu();
	wxMenuItem* MenuFileSubExit;
	MenuFileSubExit = new wxMenuItem( MenuFile, ID_MenuFileSubExit, wxString( wxT("退出") ) + wxT('\t') + wxT("Alt+F4"), wxT("退出此应用"), wxITEM_NORMAL );
	MenuFile->Append( MenuFileSubExit );

	m_menubar->Append( MenuFile, wxT("文件") );

	MenuLinks = new wxMenu();
	wxMenuItem* MenuLinksSubOneNET;
	MenuLinksSubOneNET = new wxMenuItem( MenuLinks, ID_MenuLinksSubOneNET, wxString( wxT("OneNET") ) , wxT("打开OneNET官方地址"), wxITEM_NORMAL );
	MenuLinks->Append( MenuLinksSubOneNET );

	MenuLinks->AppendSeparator();

	wxMenuItem* MenuLinksSubOneNETToken;
	MenuLinksSubOneNETToken = new wxMenuItem( MenuLinks, ID_MenuLinksSubOneNETToken, wxString( wxT("OneNET Token") ) , wxT("打开OneNet的Token算法连接"), wxITEM_NORMAL );
	MenuLinks->Append( MenuLinksSubOneNETToken );

	m_menubar->Append( MenuLinks, wxT("链接") );

	MenuHelp = new wxMenu();
	wxMenuItem* MenuHelpAbout;
	MenuHelpAbout = new wxMenuItem( MenuHelp, ID_MenuHelpAbout, wxString( wxT("关于") ) , wxT("关于此程序"), wxITEM_NORMAL );
	MenuHelp->Append( MenuHelpAbout );

	m_menubar->Append( MenuHelp, wxT("帮助") );

	this->SetMenuBar( m_menubar );

	m_statusBar = this->CreateStatusBar( 3, wxSTB_SIZEGRIP, wxID_ANY );
	m_bottom = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_bottom->SetMinSize( wxSize( -1,75 ) );

	m_mgr.AddPane( m_bottom, wxAuiPaneInfo() .Bottom() .CaptionVisible( false ).CloseButton( false ).PinButton( true ).Dock().Resizable().FloatingSize( wxDefaultSize ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).MinSize( wxSize( -1,150 ) ) );

	m_log = new wxPanel( m_bottom, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer_log;
	bSizer_log = new wxBoxSizer( wxVERTICAL );

	m_log_textCtrl = new wxTextCtrl( m_log, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_AUTO_URL|wxTE_MULTILINE|wxTE_READONLY );
	bSizer_log->Add( m_log_textCtrl, 1, wxALL|wxEXPAND, 5 );


	m_log->SetSizer( bSizer_log );
	m_log->Layout();
	bSizer_log->Fit( m_log );
	m_bottom->AddPage( m_log, wxT("日志"), true, wxNullBitmap );


	m_mgr.Update();
	this->Centre( wxBOTH );

	// Connect Events
	m_token->Connect( wxEVT_SIZE, wxSizeEventHandler( MainFrame::OnTokenSize ), NULL, this );
	m_choice_tokenet->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::OnTokenetChoiceUpdate ), NULL, this );
	m_textCtrl_tokenet->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::OnTokenetTextUpdate ), NULL, this );
	m_choice_tokenres->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::OnTokenresChoice ), NULL, this );
	m_button_tokengenerate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTokenGenerateButtonClick ), NULL, this );
	MenuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuFileSubExit ), this, MenuFileSubExit->GetId());
	MenuLinks->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuLinksSubOneNET ), this, MenuLinksSubOneNET->GetId());
	MenuLinks->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuLinksSubOneNETToken ), this, MenuLinksSubOneNETToken->GetId());
	MenuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuHelpAbout ), this, MenuHelpAbout->GetId());
}

MainFrame::~MainFrame()
{
	// Disconnect Events
	m_token->Disconnect( wxEVT_SIZE, wxSizeEventHandler( MainFrame::OnTokenSize ), NULL, this );
	m_choice_tokenet->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::OnTokenetChoiceUpdate ), NULL, this );
	m_textCtrl_tokenet->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MainFrame::OnTokenetTextUpdate ), NULL, this );
	m_choice_tokenres->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MainFrame::OnTokenresChoice ), NULL, this );
	m_button_tokengenerate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnTokenGenerateButtonClick ), NULL, this );

	m_mgr.UnInit();

}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 800,600 ), wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);

	m_abouttab = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_mgr.AddPane( m_abouttab, wxAuiPaneInfo() .Left() .CaptionVisible( false ).CloseButton( false ).Movable( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );

	m_scrolledWindow_info = new wxScrolledWindow( m_abouttab, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow_info->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer_info;
	bSizer_info = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer_info_version;
	bSizer_info_version = new wxBoxSizer( wxHORIZONTAL );

	m_staticText_info_version = new wxStaticText( m_scrolledWindow_info, wxID_ANY, wxT("版本:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_info_version->Wrap( -1 );
	bSizer_info_version->Add( m_staticText_info_version, 0, wxALL, 5 );

	m_staticText_info_version_str = new wxStaticText( m_scrolledWindow_info, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_info_version_str->Wrap( -1 );
	bSizer_info_version->Add( m_staticText_info_version_str, 0, wxALL, 5 );


	bSizer_info->Add( bSizer_info_version, 0, wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline_1 = new wxStaticLine( m_scrolledWindow_info, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer_info->Add( m_staticline_1, 0, wxEXPAND | wxALL, 5 );

	m_staticText_Info_author = new wxStaticText( m_scrolledWindow_info, wxID_ANY, wxT("作者:何亚红"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_Info_author->Wrap( -1 );
	bSizer_info->Add( m_staticText_Info_author, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_hyperlink_info_author_hyh_github = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("github"), wxT("https://github.com/HEYAHONG"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink_info_author_hyh_github, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_hyperlink_info_author_hyh_gitee = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("gitee"), wxT("https://gitee.com/HEYAHONG"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink_info_author_hyh_gitee, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_staticline_2 = new wxStaticLine( m_scrolledWindow_info, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer_info->Add( m_staticline_2, 0, wxEXPAND | wxALL, 5 );

	m_staticText_info_depends = new wxStaticText( m_scrolledWindow_info, wxID_ANY, wxT("依赖："), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_info_depends->Wrap( -1 );
	bSizer_info->Add( m_staticText_info_depends, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_hyperlink_depends_wxwidgets = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("wxWidgets"), wxT("https://www.wxWidgets.org"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink_depends_wxwidgets, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	m_scrolledWindow_info->SetSizer( bSizer_info );
	m_scrolledWindow_info->Layout();
	bSizer_info->Fit( m_scrolledWindow_info );
	m_abouttab->AddPage( m_scrolledWindow_info, wxT("信息"), true, wxNullBitmap );
	m_panel_license = new wxPanel( m_abouttab, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer_panel_license;
	bSizer_panel_license = new wxBoxSizer( wxVERTICAL );

	m_richText_license = new wxRichTextCtrl( m_panel_license, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxVSCROLL|wxHSCROLL|wxNO_BORDER|wxWANTS_CHARS );
	bSizer_panel_license->Add( m_richText_license, 1, wxEXPAND | wxALL, 5 );


	m_panel_license->SetSizer( bSizer_panel_license );
	m_panel_license->Layout();
	bSizer_panel_license->Fit( m_panel_license );
	m_abouttab->AddPage( m_panel_license, wxT("LICENSE"), false, wxNullBitmap );


	m_mgr.Update();
	this->Centre( wxBOTH );
}

AboutDialog::~AboutDialog()
{
	m_mgr.UnInit();

}
