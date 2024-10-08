//main.cpp for OpenBaseball
//https://github.com/svet-am/openBaseball
//written by Tony McDowell (svet.am@gmail.com)
#include <time.h>
#include <stdlib.h> 
#include <iostream>
#include "WX/WX.h"
#include "wx/sizer.h"
#include "WX/display.h"
#include "wx/image.h"
#include "wx/file.h"
#include "wx/bitmap.h"
#include "wx/filename.h"
#include "wx/stdpaths.h"
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

// This frame is very simple because it will only be for showing the logo
class LogoFrame : public wxFrame
{
public:
    LogoFrame()
    :wxFrame(NULL, -1, wxString(), wxDefaultPosition, wxSize(64,64), wxBORDER_NONE) {
    }

private:

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
    LogoFrame *lFrame = new LogoFrame();
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    lFrame->SetClientSize(wxSize(512, 512));
    lFrame->SetSizer(sizer);
    lFrame->Centre();
    lFrame->Show(true);
    //Load options and dependencies
    //This is just a Sleep() in early development
    // update display
	
    Sleep(5000);
    lFrame->Close(true);

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

