#pragma once
#include "precompiled.h"
#include "todcore/kernel.h"
#include "todeditor/todeditormainframe.h"
#include "todeditor/todeditorobjectviewer.h"
#include "todeditor/todeditorinspector.h"
#include "todirrlicht/main.h"
#include "todirrlicht/todirrlichtdevice.h"
namespace tod
{


class TodEditor : public wxApp
{
public:
    bool OnInit()
    {
        //_CrtSetBreakAlloc(9459);
        
        if (!wxApp::OnInit()) return false;

        BEGIN_MODULE(TodEditor);
            ADD_TYPE(TodEditor, TodEditorMainFrame);
            ADD_TYPE(TodEditor, TodEditorObjectViewer);
            ADD_TYPE(TodEditor, TodEditorInspector);
        END_MODULE(TodEditor);


        init_todirrlichtlib();


        //Main Frame
		this->mainFrame =
            static_cast<TodEditorMainFrame*>
            (Kernel::instance()->
            create(S("TodEditorMainFrame"), S("/editor/mainframe")));
		this->SetTopWindow(this->mainFrame->getMainFrame());		
        

        //Object Viewer
        TodEditorObjectViewer* object_viewer =
            static_cast<TodEditorObjectViewer*>
            (Kernel::instance()->
            create(S("TodEditorObjectViewer"), S("/editor/objectviewer")));
		object_viewer->initialize(this->mainFrame->getMainFrame());
        object_viewer->setRoot(Kernel::instance()->getRoot());
		this->mainFrame->getAuiManager()->
            AddPane(object_viewer->getMainPanel(),
            wxAuiPaneInfo().Caption("Object Viewer").Left().MinSize(300, 300).
            Floatable().Dockable().CloseButton(false).Movable().Resizable());


        //Inspector
        TodEditorInspector* inspector =
            static_cast<TodEditorInspector*>
            (Kernel::instance()->
            create(S("TodEditorInspector"), S("/editor/inspector")));
		inspector->initialize(this->mainFrame->getMainFrame());
        object_viewer->addEventListener(
            TodEditorObjectViewer::EVENT_SELECTED_NODE,
            inspector, [object_viewer, inspector](void*)
        {
            inspector->setNodes(object_viewer->getSelections());
        });
		this->mainFrame->getAuiManager()->
            AddPane(inspector->getMainPanel(),
            wxAuiPaneInfo().Caption("Inspector").Right().MinSize(300, 300).
            Floatable().Dockable().CloseButton(false).Movable().Resizable());

       

        //Center
        this->centerPanel = new wxPanel(this->mainFrame->getMainFrame(), -1);
        this->centerPanel->SetBackgroundColour(wxColour(39, 40, 34));
        this->mainFrame->getAuiManager()->AddPane(this->centerPanel, wxAuiPaneInfo().CenterPane().MinSize(10, 10));        

		this->mainFrame->show();


		this->irrlichtDevice = static_cast<TodIrrlichtDevice*>(Kernel::instance()->create(S("TodIrrlichtDevice"), S("/irricht/scene")));
        this->irrlichtDevice->initialize(this->centerPanel->GetHandle());



        this->updateTimer = new wxTimer();
        this->updateTimer->Connect(wxEVT_TIMER, (wxObjectEventFunction)&TodEditor::on_update_timer, 0, this);
        this->updateTimer->Start(1);


        return true;
    }

    void on_update_timer(wxTimerEvent& e)
    {
        this->irrlichtDevice->resizeViewport(this->centerPanel->GetClientSize().GetWidth(), this->centerPanel->GetClientSize().GetHeight());
        this->irrlichtDevice->pump();
    }

private:
	TodEditorMainFrame* mainFrame;
	TodIrrlichtDevice* irrlichtDevice;
    wxTimer* updateTimer;
    wxPanel* centerPanel;
};


DECLARE_APP(TodEditor);
IMPLEMENT_APP(TodEditor);


}
