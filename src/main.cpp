//main.cpp for OpenBaseball
//https://github.com/svet-am/openBaseball
//written by Tony McDowell (svet.am@gmail.com)
#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include "wx/wx.h"
#include "wx/sizer.h"
#include "wx/display.h"
#include "wx/image.h"
#include "wx/file.h"
#include "wx/bitmap.h"
#include "wx/filename.h"
#include "wx/stdpaths.h"
#include "wx/splash.h"
#include "wx/aui/aui.h"
#include "wx/ribbon/bar.h"
#include "wx/ribbon/buttonbar.h"
#include "wx/artprov.h"

#include "obb_version.hpp"
#include "obb_utils.hpp"

using namespace std;

class OBBApp : public wxApp
{
public:
    bool OnInit() override;
};
 
wxIMPLEMENT_APP(OBBApp);
 
class MyFrame : public wxFrame
{
public:
    MyFrame();
 
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

enum
{
    ID_Hello = 1
};
 
bool OBBApp::OnInit()
{
    wxFileName binaryLocation(wxStandardPaths::Get().GetExecutablePath());
    wxString binaryBasePath(binaryLocation.GetPath());

    //Initialize various wxWidgets Handlers
    wxInitAllImageHandlers();

    //Create the loading / logo screen
	wxBitmap bitmap;
	if (bitmap.LoadFile(binaryBasePath + "/img/obb_logo.png", wxBITMAP_TYPE_PNG))
	{
		wxSplashScreen* splash = new wxSplashScreen(bitmap,
			wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_TIMEOUT,
			2000, NULL, -1, wxDefaultPosition, wxDefaultSize,
			wxBORDER_SIMPLE|wxSTAY_ON_TOP);
	}

    // Create the primary game window
    MyFrame *frame = new MyFrame();
    frame->SetClientSize(wxSize((int)(wxDisplay().GetGeometry().GetWidth()*.85) , (int)(wxDisplay().GetGeometry().GetHeight()*.80)));
    frame->Centre();
    frame->Show(true);
    return true;
}
 
MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, OBB_NAME, wxDefaultPosition, wxSize(1024,768))
{
	// Ribbon
    wxRibbonBar *ribbonBar = new wxRibbonBar(this, -1, wxDefaultPosition, wxDefaultSize, wxRIBBON_BAR_FLOW_HORIZONTAL
                                | wxRIBBON_BAR_SHOW_PAGE_LABELS
                                | wxRIBBON_BAR_SHOW_PANEL_EXT_BUTTONS
                                | wxRIBBON_BAR_SHOW_TOGGLE_BUTTON
                                );
 
    wxRibbonPage *homeRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Master Data"), wxNullBitmap);
    wxRibbonPage *editRibbonPage = new wxRibbonPage(ribbonBar, wxID_ANY, wxT("Edit Page"), wxNullBitmap);
 
    wxRibbonPanel *homeRibbonPanel = new wxRibbonPanel(homeRibbonPage, wxID_ANY, wxT("Home"), wxNullBitmap,
                                  wxDefaultPosition, wxDefaultSize,
                                  wxRIBBON_PANEL_NO_AUTO_MINIMISE);
    wxRibbonPanel *itemRibbonPanel = new wxRibbonPanel(homeRibbonPage, wxID_ANY, wxT("Data Item"),
                                        wxNullBitmap, wxDefaultPosition, wxDefaultSize,
                                        wxRIBBON_PANEL_NO_AUTO_MINIMISE);
 
    wxRibbonButtonBar *homeRibbonButtonBar = new wxRibbonButtonBar(homeRibbonPanel);
    wxRibbonButtonBar *itemRibbonButtonBar = new wxRibbonButtonBar(itemRibbonPanel);
 
    homeRibbonButtonBar->AddButton(wxID_ANY, wxT("Home Menu"),
                                   wxArtProvider::GetBitmap(wxART_ADD_BOOKMARK, wxART_TOOLBAR, wxSize(16,15)));
 
    itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Daftar Guru"),
                    wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16,15)));
    itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Tambah Guru"),
                    wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16,15)));
    itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Daftar Siswa"),
                    wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16,15)));
    itemRibbonButtonBar->AddButton(wxID_ANY, wxT("Tambah Siswa"),
                    wxArtProvider::GetBitmap(wxART_QUESTION, wxART_TOOLBAR, wxSize(16,15)));
 
    ribbonBar->AddPageHighlight(ribbonBar->GetPageCount() - 1);
    ribbonBar->Realize();
 
    // set style msw provider
    ribbonBar->DismissExpandedPanel();
    ribbonBar->SetArtProvider(new wxRibbonMSWArtProvider);
 
    // aui notebook
    wxSize client_size = GetClientSize();
 
    wxAuiNotebook *auiNotebook = new wxAuiNotebook(this, wxID_ANY,
                                    wxPoint(client_size.x, client_size.y),
                                    wxSize(430,200),
                                    wxAUI_NB_CLOSE_BUTTON | wxAUI_NB_SCROLL_BUTTONS);
    auiNotebook->Freeze();
    wxBitmap page_bmp = wxArtProvider::GetBitmap(wxART_NORMAL_FILE, wxART_OTHER, wxSize(16,16));
 
    auiNotebook->AddPage(new wxTextCtrl(auiNotebook, wxID_ANY, wxT("Some text"),
                                        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER),
                                        wxT("Home"), false, page_bmp);
    auiNotebook->AddPage(new wxTextCtrl(auiNotebook, wxID_ANY, wxT("Some text"),
                                        wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxNO_BORDER),
                                        wxT("Item 1"), false, page_bmp);
 
    auiNotebook->SetPageToolTip(0, "Menu utama sistem informasi akademik");
    auiNotebook->Thaw();
 
    // set layout
    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(ribbonBar, 0, wxEXPAND);
    sizer->Add(auiNotebook, 1, wxEXPAND);
    SetSizer(sizer);
 
    Centre();
	
/*  RIBBON MENU STYLE
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string shown in status bar for this menu item");
    //menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
 
    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
 
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
 
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

*/
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
}
 
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}

