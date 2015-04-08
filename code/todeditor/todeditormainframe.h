#pragma once
#include "todcore/node.h"
#include "todcore/simplepropertybinder.h"
#include "todcore/enumpropertybinder.h"
#include "todeditor/precompiled.h"
namespace tod
{


class TodEditorMainFrame : public Derive<TodEditorMainFrame, Node>
{
public:
    TodEditorMainFrame():
    mainFrame(nullptr)
    {
        this->mainFrame = new Frame();
    }

    void show()
    {
        this->mainFrame->auiMgr.Update();
        this->mainFrame->Show();
    }

    wxFrame* getMainFrame()
    {
        return this->mainFrame;
    }

    wxAuiManager* getAuiManager()
    {
        return &this->mainFrame->auiMgr;
    }

    static void bindProperty()
    {
    }

private:
    class Frame : public wxFrame
    {
    public:
        Frame()
        {
            this->Create(0, -1, "Tod Editor");
            this->SetSize(1000, 500);
            this->auiMgr.SetManagedWindow(this);


            //Main Menu bar
            this->mainMenuBar = new wxMenuBar(0);
            this->SetMenuBar(this->mainMenuBar);

            this->fileMenu = new wxMenu();
            this->fileMenu->Append(new wxMenuItem(this->fileMenu, 1, "New Project"));
            this->mainMenuBar->Append(this->fileMenu, "File");
        }
        OVERRIDE bool Destroy()
        {
            this->auiMgr.UnInit();
            return wxFrame::Destroy();
        }

    public:
        wxAuiManager auiMgr;
        wxMenuBar* mainMenuBar;
        wxMenu* fileMenu;
    };

private:
    Frame* mainFrame;
};


}
