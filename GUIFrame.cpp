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
	m_main->AddPage( m_token, wxT("Token"), true, wxNullBitmap );
	m_LwM2MDeviceList = new wxScrolledWindow( m_main, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_LwM2MDeviceList->SetScrollRate( 5, 5 );
	m_menu_LwM2MDeviceList = new wxMenu();
	wxMenuItem* m_menuItem_LwM2MDeviceList_Add;
	m_menuItem_LwM2MDeviceList_Add = new wxMenuItem( m_menu_LwM2MDeviceList, wxID_ANY, wxString( wxT("添加设备") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_LwM2MDeviceList->Append( m_menuItem_LwM2MDeviceList_Add );

	wxMenuItem* m_menuItem__LwM2MDeviceList_ClearAll;
	m_menuItem__LwM2MDeviceList_ClearAll = new wxMenuItem( m_menu_LwM2MDeviceList, wxID_ANY, wxString( wxT("清除所有") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_LwM2MDeviceList->Append( m_menuItem__LwM2MDeviceList_ClearAll );

	wxMenuItem* m_menuItem_m_menuItem__LwM2MDeviceList_Remove;
	m_menuItem_m_menuItem__LwM2MDeviceList_Remove = new wxMenuItem( m_menu_LwM2MDeviceList, wxID_ANY, wxString( wxT("删除选中的行") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu_LwM2MDeviceList->Append( m_menuItem_m_menuItem__LwM2MDeviceList_Remove );

	m_LwM2MDeviceList->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( MainFrame::m_LwM2MDeviceListOnContextMenu ), NULL, this );

	wxFlexGridSizer* fgSizer_LwM2MDeviceList;
	fgSizer_LwM2MDeviceList = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer_LwM2MDeviceList->SetFlexibleDirection( wxVERTICAL );
	fgSizer_LwM2MDeviceList->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer_LwM2MDeviceList->Add( 800, 0, 1, wxFIXED_MINSIZE, 5 );

	m_dataViewListCtrl_LwM2MDeviceList = new wxDataViewListCtrl( m_LwM2MDeviceList, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxDV_SINGLE );
	m_dataViewListCtrl_LwM2MDeviceList->SetMinSize( wxSize( -1,300 ) );

	m_dataViewListColumn_LwM2MDeviceList_DeviceName = m_dataViewListCtrl_LwM2MDeviceList->AppendTextColumn( wxT("DeviceName"), wxDATAVIEW_CELL_INERT, 150, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewListColumn_LwM2MDeviceList_IMEI = m_dataViewListCtrl_LwM2MDeviceList->AppendTextColumn( wxT("IMEI"), wxDATAVIEW_CELL_INERT, 200, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewListColumn_LwM2MDeviceList_IMSI = m_dataViewListCtrl_LwM2MDeviceList->AppendTextColumn( wxT("IMSI"), wxDATAVIEW_CELL_INERT, 200, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewListColumn_LwM2MDeviceList_AuthCode = m_dataViewListCtrl_LwM2MDeviceList->AppendTextColumn( wxT("AuthCode"), wxDATAVIEW_CELL_INERT, 100, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	m_dataViewListColumn_LwM2MDeviceList_PSK = m_dataViewListCtrl_LwM2MDeviceList->AppendTextColumn( wxT("PSK"), wxDATAVIEW_CELL_INERT, -1, static_cast<wxAlignment>(wxALIGN_CENTER|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL), wxDATAVIEW_COL_RESIZABLE );
	fgSizer_LwM2MDeviceList->Add( m_dataViewListCtrl_LwM2MDeviceList, 1, wxALL|wxEXPAND, 5 );

	m_textCtrl_LwM2MDeviceList = new wxTextCtrl( m_LwM2MDeviceList, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_textCtrl_LwM2MDeviceList->SetMinSize( wxSize( -1,125 ) );

	fgSizer_LwM2MDeviceList->Add( m_textCtrl_LwM2MDeviceList, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer_LwM2MDeviceList;
	bSizer_LwM2MDeviceList = new wxBoxSizer( wxHORIZONTAL );

	m_button_LwM2MDeviceList_ClearAll = new wxButton( m_LwM2MDeviceList, wxID_ANY, wxT("清除所有"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_LwM2MDeviceList->Add( m_button_LwM2MDeviceList_ClearAll, 0, wxALL, 5 );

	m_button_LwM2MDeviceList_Save = new wxButton( m_LwM2MDeviceList, wxID_ANY, wxT("保存"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_LwM2MDeviceList->Add( m_button_LwM2MDeviceList_Save, 0, wxALL, 5 );


	fgSizer_LwM2MDeviceList->Add( bSizer_LwM2MDeviceList, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );


	m_LwM2MDeviceList->SetSizer( fgSizer_LwM2MDeviceList );
	m_LwM2MDeviceList->Layout();
	fgSizer_LwM2MDeviceList->Fit( m_LwM2MDeviceList );
	m_main->AddPage( m_LwM2MDeviceList, wxT("OneNET Studio LwM2M设备列表"), false, wxNullBitmap );

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
	m_menu_LwM2MDeviceList->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuLwM2MDeviceAdd ), this, m_menuItem_LwM2MDeviceList_Add->GetId());
	m_menu_LwM2MDeviceList->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuLwM2MDeviceListClearAll ), this, m_menuItem__LwM2MDeviceList_ClearAll->GetId());
	m_menu_LwM2MDeviceList->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuLwM2MDeviceListRemove ), this, m_menuItem_m_menuItem__LwM2MDeviceList_Remove->GetId());
	m_dataViewListCtrl_LwM2MDeviceList->Connect( wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, wxDataViewEventHandler( MainFrame::OnLwM2MDeviceListContextMenu ), NULL, this );
	m_button_LwM2MDeviceList_ClearAll->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonLwM2MDeviceListClearAllClick ), NULL, this );
	m_button_LwM2MDeviceList_Save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnLwM2MDeviceListSaveButtonClick ), NULL, this );
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
	m_dataViewListCtrl_LwM2MDeviceList->Disconnect( wxEVT_COMMAND_DATAVIEW_ITEM_CONTEXT_MENU, wxDataViewEventHandler( MainFrame::OnLwM2MDeviceListContextMenu ), NULL, this );
	m_button_LwM2MDeviceList_ClearAll->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnButtonLwM2MDeviceListClearAllClick ), NULL, this );
	m_button_LwM2MDeviceList_Save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainFrame::OnLwM2MDeviceListSaveButtonClick ), NULL, this );

	m_mgr.UnInit();

	delete m_menu_LwM2MDeviceList;
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

	m_hyperlink__depends_boost = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("Boost"), wxT("https://www.boost.org/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink__depends_boost, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_hyperlink_depends_mbedtls = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("MbedTLS"), wxT("https://github.com/Mbed-TLS/mbedtls.git"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink_depends_mbedtls, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_hyperlink__depends_libexpat = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("libexpat"), wxT("https://libexpat.github.io/"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink__depends_libexpat, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_hyperlink_libminizip = new wxHyperlinkCtrl( m_scrolledWindow_info, wxID_ANY, wxT("libminizip"), wxT("http://www.zlib.net"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer_info->Add( m_hyperlink_libminizip, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


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

NewLwM2MDeviceDialog::NewLwM2MDeviceDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( 450,600 ), wxDefaultSize );

	wxBoxSizer* bSizer_NewLwM2MDevice;
	bSizer_NewLwM2MDevice = new wxBoxSizer( wxVERTICAL );

	bSizer_NewLwM2MDevice->SetMinSize( wxSize( 450,600 ) );
	m_auinotebook_NewLwM2MDevice = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TOP );
	m_scrolledWindow_NewLwM2MDevice_Manual = new wxScrolledWindow( m_auinotebook_NewLwM2MDevice, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow_NewLwM2MDevice_Manual->SetScrollRate( 5, 5 );
	wxBoxSizer* bSizer__NewLwM2MDevice_Manual;
	bSizer__NewLwM2MDevice_Manual = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer__NewLwM2MDevice_Manual;
	fgSizer__NewLwM2MDevice_Manual = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer__NewLwM2MDevice_Manual->SetFlexibleDirection( wxBOTH );
	fgSizer__NewLwM2MDevice_Manual->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer__NewLwM2MDevice_Manual->Add( 150, 10, 1, wxEXPAND, 5 );


	fgSizer__NewLwM2MDevice_Manual->Add( 250, 0, 1, wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_Manual_DeviceName = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxT("DeviceName*:"), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT );
	m_staticText_NewLwM2MDevice_Manual_DeviceName->Wrap( -1 );
	fgSizer__NewLwM2MDevice_Manual->Add( m_staticText_NewLwM2MDevice_Manual_DeviceName, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl_NewLwM2MDevice_Manual_DeviceName = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	fgSizer__NewLwM2MDevice_Manual->Add( m_textCtrl_NewLwM2MDevice_Manual_DeviceName, 1, wxALL|wxEXPAND, 5 );

	m_staticText__NewLwM2MDevice_Manual_IMEI = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxT("IMEI*:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText__NewLwM2MDevice_Manual_IMEI->Wrap( -1 );
	fgSizer__NewLwM2MDevice_Manual->Add( m_staticText__NewLwM2MDevice_Manual_IMEI, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl__NewLwM2MDevice_Manual_IMEI = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	fgSizer__NewLwM2MDevice_Manual->Add( m_textCtrl__NewLwM2MDevice_Manual_IMEI, 1, wxALL|wxEXPAND, 5 );

	m_staticText__NewLwM2MDevice_Manual_IMSI = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxT("IMSI*:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText__NewLwM2MDevice_Manual_IMSI->Wrap( -1 );
	fgSizer__NewLwM2MDevice_Manual->Add( m_staticText__NewLwM2MDevice_Manual_IMSI, 0, wxALL|wxALIGN_RIGHT, 5 );

	m_textCtrl__NewLwM2MDevice_Manual_IMSI = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	fgSizer__NewLwM2MDevice_Manual->Add( m_textCtrl__NewLwM2MDevice_Manual_IMSI, 1, wxALL|wxEXPAND, 5 );

	m_staticText__NewLwM2MDevice_Manual_AuthCode = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxT("AuthCode:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText__NewLwM2MDevice_Manual_AuthCode->Wrap( -1 );
	fgSizer__NewLwM2MDevice_Manual->Add( m_staticText__NewLwM2MDevice_Manual_AuthCode, 0, wxALL|wxALIGN_RIGHT, 5 );

	m_textCtrl__NewLwM2MDevice_Manual_AuthCode = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	fgSizer__NewLwM2MDevice_Manual->Add( m_textCtrl__NewLwM2MDevice_Manual_AuthCode, 1, wxALL|wxEXPAND, 5 );

	m_staticText__NewLwM2MDevice_Manual_PSK = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxT("PSK:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText__NewLwM2MDevice_Manual_PSK->Wrap( -1 );
	fgSizer__NewLwM2MDevice_Manual->Add( m_staticText__NewLwM2MDevice_Manual_PSK, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_textCtrl__NewLwM2MDevice_Manual_PSK = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	fgSizer__NewLwM2MDevice_Manual->Add( m_textCtrl__NewLwM2MDevice_Manual_PSK, 1, wxALL|wxEXPAND, 5 );


	fgSizer__NewLwM2MDevice_Manual->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer_Button;
	bSizer_Button = new wxBoxSizer( wxVERTICAL );

	m_button_NewLwM2MDevice_Manual_OK = new wxButton( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxT("确定"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_Button->Add( m_button_NewLwM2MDevice_Manual_OK, 0, wxALL|wxALIGN_RIGHT, 5 );


	fgSizer__NewLwM2MDevice_Manual->Add( bSizer_Button, 1, wxEXPAND, 5 );


	bSizer__NewLwM2MDevice_Manual->Add( fgSizer__NewLwM2MDevice_Manual, 1, wxEXPAND, 5 );

	m_staticline4 = new wxStaticLine( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer__NewLwM2MDevice_Manual->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );

	m_textCtrl_NewLwM2MDevice_Manual_ReadMe = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_Manual, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	bSizer__NewLwM2MDevice_Manual->Add( m_textCtrl_NewLwM2MDevice_Manual_ReadMe, 1, wxALL|wxEXPAND, 5 );


	m_scrolledWindow_NewLwM2MDevice_Manual->SetSizer( bSizer__NewLwM2MDevice_Manual );
	m_scrolledWindow_NewLwM2MDevice_Manual->Layout();
	bSizer__NewLwM2MDevice_Manual->Fit( m_scrolledWindow_NewLwM2MDevice_Manual );
	m_auinotebook_NewLwM2MDevice->AddPage( m_scrolledWindow_NewLwM2MDevice_Manual, wxT("手工录入"), true, wxNullBitmap );
	m_scrolledWindow_NewLwM2MDevice_AT = new wxScrolledWindow( m_auinotebook_NewLwM2MDevice, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow_NewLwM2MDevice_AT->SetScrollRate( 5, 5 );
	wxGridBagSizer* gbSizer_NewLwM2MDevice_AT;
	gbSizer_NewLwM2MDevice_AT = new wxGridBagSizer( 0, 0 );
	gbSizer_NewLwM2MDevice_AT->SetFlexibleDirection( wxVERTICAL );
	gbSizer_NewLwM2MDevice_AT->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	wxFlexGridSizer* fgSizer_NewLwM2MDevice_AT;
	fgSizer_NewLwM2MDevice_AT = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer_NewLwM2MDevice_AT->SetFlexibleDirection( wxBOTH );
	fgSizer_NewLwM2MDevice_AT->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	fgSizer_NewLwM2MDevice_AT->Add( 200, 0, 1, wxEXPAND, 5 );


	fgSizer_NewLwM2MDevice_AT->Add( 200, 0, 1, wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_ComPort = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("串口号:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_NewLwM2MDevice_ComPort->Wrap( -1 );
	fgSizer_NewLwM2MDevice_AT->Add( m_staticText_NewLwM2MDevice_ComPort, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_comboBox_NewLwM2MDevice_ComPort = new wxComboBox( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN );
	fgSizer_NewLwM2MDevice_AT->Add( m_comboBox_NewLwM2MDevice_ComPort, 0, wxALL|wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_DataRate = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("波特率:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_NewLwM2MDevice_DataRate->Wrap( -1 );
	fgSizer_NewLwM2MDevice_AT->Add( m_staticText_NewLwM2MDevice_DataRate, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	m_comboBox_NewLwM2MDevice_DataRate = new wxComboBox( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("9600"), wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("1200") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("2400") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("4800") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("9600") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("19200") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("38400") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("57600") );
	m_comboBox_NewLwM2MDevice_DataRate->Append( wxT("115200") );
	fgSizer_NewLwM2MDevice_AT->Add( m_comboBox_NewLwM2MDevice_DataRate, 0, wxALL|wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_DataBits = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("数据位:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_NewLwM2MDevice_DataBits->Wrap( -1 );
	fgSizer_NewLwM2MDevice_AT->Add( m_staticText_NewLwM2MDevice_DataBits, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choice_NewLwM2MDevice_DataBitsChoices[] = { wxT("8"), wxT("7") };
	int m_choice_NewLwM2MDevice_DataBitsNChoices = sizeof( m_choice_NewLwM2MDevice_DataBitsChoices ) / sizeof( wxString );
	m_choice_NewLwM2MDevice_DataBits = new wxChoice( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_NewLwM2MDevice_DataBitsNChoices, m_choice_NewLwM2MDevice_DataBitsChoices, 0 );
	m_choice_NewLwM2MDevice_DataBits->SetSelection( 0 );
	fgSizer_NewLwM2MDevice_AT->Add( m_choice_NewLwM2MDevice_DataBits, 0, wxALL|wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_StopBits = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("停止位:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_NewLwM2MDevice_StopBits->Wrap( -1 );
	fgSizer_NewLwM2MDevice_AT->Add( m_staticText_NewLwM2MDevice_StopBits, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choice_NewLwM2MDevice_StopBitsChoices[] = { wxT("1"), wxT("1.5"), wxT("2") };
	int m_choice_NewLwM2MDevice_StopBitsNChoices = sizeof( m_choice_NewLwM2MDevice_StopBitsChoices ) / sizeof( wxString );
	m_choice_NewLwM2MDevice_StopBits = new wxChoice( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_NewLwM2MDevice_StopBitsNChoices, m_choice_NewLwM2MDevice_StopBitsChoices, 0 );
	m_choice_NewLwM2MDevice_StopBits->SetSelection( 0 );
	fgSizer_NewLwM2MDevice_AT->Add( m_choice_NewLwM2MDevice_StopBits, 0, wxALL|wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_FlowControl = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("流控:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_NewLwM2MDevice_FlowControl->Wrap( -1 );
	fgSizer_NewLwM2MDevice_AT->Add( m_staticText_NewLwM2MDevice_FlowControl, 0, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5 );

	wxString m_choice_NewLwM2MDevice_FlowControlChoices[] = { wxT("none"), wxT("software"), wxT("hardware") };
	int m_choice_NewLwM2MDevice_FlowControlNChoices = sizeof( m_choice_NewLwM2MDevice_FlowControlChoices ) / sizeof( wxString );
	m_choice_NewLwM2MDevice_FlowControl = new wxChoice( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_NewLwM2MDevice_FlowControlNChoices, m_choice_NewLwM2MDevice_FlowControlChoices, 0 );
	m_choice_NewLwM2MDevice_FlowControl->SetSelection( 0 );
	fgSizer_NewLwM2MDevice_AT->Add( m_choice_NewLwM2MDevice_FlowControl, 0, wxALL|wxEXPAND, 5 );

	m_staticText_NewLwM2MDevice_Parity = new wxStaticText( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("校验:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText_NewLwM2MDevice_Parity->Wrap( -1 );
	fgSizer_NewLwM2MDevice_AT->Add( m_staticText_NewLwM2MDevice_Parity, 0, wxALL|wxALIGN_RIGHT, 5 );

	wxString m_choice_NewLwM2MDevice_ParityChoices[] = { wxT("none"), wxT("odd"), wxT("even") };
	int m_choice_NewLwM2MDevice_ParityNChoices = sizeof( m_choice_NewLwM2MDevice_ParityChoices ) / sizeof( wxString );
	m_choice_NewLwM2MDevice_Parity = new wxChoice( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice_NewLwM2MDevice_ParityNChoices, m_choice_NewLwM2MDevice_ParityChoices, 0 );
	m_choice_NewLwM2MDevice_Parity->SetSelection( 0 );
	fgSizer_NewLwM2MDevice_AT->Add( m_choice_NewLwM2MDevice_Parity, 0, wxALL|wxEXPAND, 5 );


	fgSizer_NewLwM2MDevice_AT->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer_NewLwM2MDevice_AT;
	bSizer_NewLwM2MDevice_AT = new wxBoxSizer( wxHORIZONTAL );

	m_button_NewLwM2MDevice_AT_Get = new wxButton( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxT("获取设备信息"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer_NewLwM2MDevice_AT->Add( m_button_NewLwM2MDevice_AT_Get, 1, wxALL, 5 );


	fgSizer_NewLwM2MDevice_AT->Add( bSizer_NewLwM2MDevice_AT, 1, wxEXPAND, 5 );


	gbSizer_NewLwM2MDevice_AT->Add( fgSizer_NewLwM2MDevice_AT, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxEXPAND, 5 );

	m_staticline3 = new wxStaticLine( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	gbSizer_NewLwM2MDevice_AT->Add( m_staticline3, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxEXPAND | wxALL, 5 );

	m_textCtrl_NewLwM2MDevice_AT_ReadMe = new wxTextCtrl( m_scrolledWindow_NewLwM2MDevice_AT, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	m_textCtrl_NewLwM2MDevice_AT_ReadMe->SetMinSize( wxSize( -1,200 ) );

	gbSizer_NewLwM2MDevice_AT->Add( m_textCtrl_NewLwM2MDevice_AT_ReadMe, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL|wxEXPAND, 5 );


	m_scrolledWindow_NewLwM2MDevice_AT->SetSizer( gbSizer_NewLwM2MDevice_AT );
	m_scrolledWindow_NewLwM2MDevice_AT->Layout();
	gbSizer_NewLwM2MDevice_AT->Fit( m_scrolledWindow_NewLwM2MDevice_AT );
	m_auinotebook_NewLwM2MDevice->AddPage( m_scrolledWindow_NewLwM2MDevice_AT, wxT("AT指令"), false, wxNullBitmap );

	bSizer_NewLwM2MDevice->Add( m_auinotebook_NewLwM2MDevice, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer_NewLwM2MDevice );
	this->Layout();
	bSizer_NewLwM2MDevice->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	m_button_NewLwM2MDevice_Manual_OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewLwM2MDeviceDialog::OnNewLwM2MDeviceManualOK ), NULL, this );
	m_button_NewLwM2MDevice_AT_Get->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewLwM2MDeviceDialog::OnNewLwM2MDeviceATGet ), NULL, this );
}

NewLwM2MDeviceDialog::~NewLwM2MDeviceDialog()
{
	// Disconnect Events
	m_button_NewLwM2MDevice_Manual_OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewLwM2MDeviceDialog::OnNewLwM2MDeviceManualOK ), NULL, this );
	m_button_NewLwM2MDevice_AT_Get->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewLwM2MDeviceDialog::OnNewLwM2MDeviceATGet ), NULL, this );

}
