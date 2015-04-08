#pragma once
#include "todcore/node.h"
#include "todcore/kernel.h"
#include "todcore/ref.h"
#include "todcore/eventdispatcher.h"
#include "todcore/serializer.h"
#include "todeditor/todeditorbasetype.h"
#include "todeditor/todeditorhelper.h"
namespace tod
{


class TodEditorObjectViewer : public EventDispatcher<Derive<TodEditorObjectViewer, Node>>
{
public:
    static const char* EVENT_SELECTED_NODE;

public:
    TodEditorObjectViewer():
    mainPanel(nullptr)
    {
    }

    void initialize(wxWindow* parent)
    {
        this->mainPanel = new Panel(parent);
        this->mainPanel->self = this;
    }

    wxPanel* getMainPanel()
    {
        return this->mainPanel;
    }

    void setRoot(Node* root)
    {
        this->mainPanel->setRoot(root);
    }

    Selections& getSelections()
    {
        return this->selections;
    }

private:
    class CreateNodeDialog : public wxDialog
    {
    public:
        CreateNodeDialog(wxWindow* parent, Node* parent_node):
        wxDialog(parent, -1, "Create Node Dialog", wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER),
        parentNode(parent_node)
        {
            wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
            this->SetSizer(main_sizer);
            this->SetSize(wxSize(500, 500));

            wxStaticBoxSizer* sbox1 = new wxStaticBoxSizer(wxVERTICAL, this, "Creation Information");
            main_sizer->Add(sbox1, 0, wxEXPAND | wxALL, 5);
            sbox1->GetStaticBox()->SetAutoLayout(true);
            sbox1->AddSpacer(5);


            //Node Type
            wxBoxSizer* line1 = new wxBoxSizer(wxHORIZONTAL);
            sbox1->Add(line1, 0, wxEXPAND);
            wxStaticText* label1 = new wxStaticText(sbox1->GetStaticBox(), -1, "Node Type", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
            label1->SetMinSize(wxSize(100, 22));
            line1->Add(label1);
            line1->AddSpacer(10);
            wxArrayString as;
            for (auto i : Kernel::instance()->getTypes()) as.Add(i.first);
            wxComboBox* type_combobox = new wxComboBox(sbox1->GetStaticBox(), -1, "Node", wxDefaultPosition, wxDefaultSize, as);
            line1->Add(type_combobox, 1, wxEXPAND);
            sbox1->AddSpacer(5);


            //Node Name
            wxBoxSizer* line2 = new wxBoxSizer(wxHORIZONTAL);
            sbox1->Add(line2, 0, wxEXPAND);
            wxStaticText* label2 = new wxStaticText(sbox1->GetStaticBox(), -1, "Node Name", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
            label2->SetMinSize(wxSize(100, 22));
            line2->Add(label2);
            line2->AddSpacer(10);
            wxTextCtrl* name_textctrl = new wxTextCtrl(sbox1->GetStaticBox(), -1, wxEmptyString);
            line2->Add(name_textctrl, 1, wxEXPAND);


            //Modules
            wxStaticBoxSizer* sbox2 = new wxStaticBoxSizer(wxHORIZONTAL, this, "Modules");
            main_sizer->Add(sbox2, 1, wxEXPAND | wxALL, 5);
            main_sizer->AddSpacer(5);
            sbox2->GetStaticBox()->SetAutoLayout(true);

            /*wxArrayString as2;
            for (auto i : Kernel::instance()->getModules()) as2.Add(i.first);
            wxListCtrl* module_listctrl = new wxListCtrl(sbox2->GetStaticBox(), -1);
            module_listctrl->SetMinSize(wxSize(100, 100));
            module_listctrl->Connect(wxEVT_LISTBOX, (wxObjectEventFunction)&CreateNodeDialog::on_module_listbox, 0, this);
            sbox2->Add(module_listctrl, 1, wxEXPAND | wxALL, 5);

            this->typeListBox = new wxListCtrl(sbox2->GetStaticBox(), -1);
            sbox2->Add(this->typeListBox, 2, wxEXPAND | wxALL, 5);*/
        }

    private:
        void on_module_listbox(wxCommandEvent& e)
        {
        }

    private:
        Node* parentNode;
        wxListCtrl* typeListBox;
    };

    class Panel : public wxPanel
    {
    public:
        enum
        {
            CONTEXTMENU_ADDNODE = 1,
            CONTEXTMENU_REMOVENODE,
            CONTEXTMENU_RENAME,
            CONTEXTMENU_SAVE,
            CONTEXTMENU_LOAD,
            CONTEXTMENU_EDITOR,
        };

    public:
        Panel(wxWindow* parent):
        wxPanel(parent, -1),
        searchCtrl(nullptr),
        objectTree(nullptr),
        contextMenu(nullptr),
        editorContextMenuItem(nullptr),
        self(nullptr)
        {
            //Main Sizer
            wxBoxSizer* main_sizer = new wxBoxSizer(wxVERTICAL);
            this->SetSizer(main_sizer);


            //Button List
            wxBoxSizer* btn_list_sizer = new wxBoxSizer(wxHORIZONTAL);
            main_sizer->Add(btn_list_sizer);
            //wxButton* btn_refresh = new wxButton(this, -1, "Refresh");
            //Sbtn_list_sizer->Add(btn_refresh);


            //Search
            this->searchCtrl = new wxSearchCtrl(this, -1);
            this->searchCtrl->ShowCancelButton(true);
            this->searchCtrl->ShowSearchButton(true);
            main_sizer->Add(this->searchCtrl, 0, wxEXPAND | wxALL, 1);
            

            //Object Tree
            wxImageList* image_list = TodEditorHelper::loadImageList();
            this->objectTree = new wxTreeCtrl(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE | wxTR_EDIT_LABELS | wxTR_HAS_BUTTONS | wxTR_LINES_AT_ROOT | wxTR_NO_LINES | wxTR_MULTIPLE);
            this->objectTree->Connect(wxEVT_TREE_SEL_CHANGED, (wxObjectEventFunction)&Panel::on_tree_sel_changed, 0, this);
            this->objectTree->Connect(wxEVT_TREE_ITEM_EXPANDING, (wxObjectEventFunction)&Panel::on_tree_item_expanding, 0, this);
            this->objectTree->Connect(wxEVT_TREE_ITEM_EXPANDED, (wxObjectEventFunction)&Panel::on_tree_item_expanded, 0, this);
            this->objectTree->Connect(wxEVT_TREE_ITEM_MENU, (wxObjectEventFunction)&Panel::on_tree_item_menu, 0, this);
            this->objectTree->Connect(wxEVT_TREE_BEGIN_DRAG, (wxObjectEventFunction)&Panel::on_tree_begin_drag, 0, this);
            this->objectTree->Connect(wxEVT_TREE_END_DRAG, (wxObjectEventFunction)&Panel::on_tree_end_drag, 0, this);
            this->objectTree->SetBackgroundColour(wxColour(230, 230, 230));
            main_sizer->Add(this->objectTree, 1, wxALL | wxEXPAND);


            //Context Menu
            this->contextMenu = new wxMenu();
            this->contextMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction)&Panel::on_context_menu_selected, 0, this);
            this->contextMenu->Append(new wxMenuItem(this->contextMenu, CONTEXTMENU_ADDNODE, "Add Node"));
            this->contextMenu->Append(new wxMenuItem(this->contextMenu, CONTEXTMENU_REMOVENODE, "Remove Node"));
            this->contextMenu->Append(new wxMenuItem(this->contextMenu, CONTEXTMENU_RENAME, "Rename Node"));
            this->contextMenu->AppendSeparator();
            this->contextMenu->Append(new wxMenuItem(this->contextMenu, CONTEXTMENU_SAVE, "Save"));
            this->contextMenu->Append(new wxMenuItem(this->contextMenu, CONTEXTMENU_LOAD, "Load"));
            this->contextMenu->AppendSeparator();
            this->contextMenu->Append(this->editorContextMenuItem = new wxMenuItem(this->contextMenu, CONTEXTMENU_EDITOR, "Editor"));
        }
        virtual~Panel()
        {
            SAFE_DELETE(this->contextMenu);
        }

        void setRoot(Node* root)
        {
            this->root = root;

            this->objectTree->DeleteAllItems();
            TreeItemData* tree_item_data = new TreeItemData(this->root);
            wxTreeItemId root_tree_item_id = this->objectTree->AddRoot("/", -1, -1, tree_item_data);
            if (this->root->getNumChildren() == 0) return;
            this->objectTree->SetItemHasChildren(root_tree_item_id);
        }

    public:
        void on_tree_sel_changed(wxTreeEvent& e)
        {
            wxArrayTreeItemIds ids;
            size_t n = this->objectTree->GetSelections(ids);
            if (n == 0) return;

            this->self->selections.clear();
            for (auto i : ids)
            {
                TreeItemData* tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(i));
                this->self->selections.push_back(tree_item_data->node);
            }
            this->self->dispatchEvent(EVENT_SELECTED_NODE, 0); 
        }
        void on_tree_item_expanding(wxTreeEvent& e)
        {
            TreeItemData* tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(e.GetItem()));
            if (tree_item_data->node->getNumChildren() == 0) return;

            this->objectTree->SetItemHasChildren(e.GetItem());
            this->objectTree->DeleteChildren(e.GetItem());
            for (auto i : tree_item_data->node->getChildren())
            {
                this->add_tree_item(i.second, e.GetItem());
            }
        }
        void on_tree_item_expanded(wxTreeEvent& e)
        {
        }
        void on_tree_item_menu(wxTreeEvent& e)
        {
            this->PopupMenu(this->contextMenu);
        }
        void on_tree_begin_drag(wxTreeEvent& e)
        {
            if (this->objectTree->GetRootItem() == e.GetItem()) return;
            this->dragTreeItemId = e.GetItem();
            e.Allow();
        }
        void on_tree_end_drag(wxTreeEvent& e)
        {
            if (e.GetItem() == this->dragTreeItemId) return;
            TreeItemData* drop_source_tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(this->dragTreeItemId)); 
            TreeItemData* drop_target_tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(e.GetItem()));

            Node* prev_parent_node = drop_source_tree_item_data->node->getParent();
            wxTreeItemId prev_parent_tree_item_id = this->objectTree->GetItemParent(this->dragTreeItemId);

            /*cocos2d::CCPoint prev_wpt = drop_source_data->node->node->convertToWorldSpace(ccp(0, 0));

            drop_source_data->node->removeFromParent();
            drop_target_data->node->addChild(drop_source_data->node);

            cocos2d::CCPoint cur_wpt = drop_source_data->node->node->convertToWorldSpace(ccp(0, 0));
            drop_source_data->node->node->setPosition(drop_source_data->node->node->getPosition() + (prev_wpt - cur_wpt));*/

            this->add_tree_item(drop_source_tree_item_data->node, e.GetItem());
            this->objectTree->Delete(this->dragTreeItemId);

            if (prev_parent_node && prev_parent_node->getNumChildren() == 0)
            {
                this->objectTree->SetItemHasChildren(prev_parent_tree_item_id, false); 
            }
        }
        void on_context_menu_selected(wxTreeEvent& e)
        {
            wxArrayTreeItemIds selections;
            if (this->objectTree->GetSelections(selections)==0) return;

            switch (e.GetId())
            {
            case CONTEXTMENU_ADDNODE:
                {
                    for (auto s : selections)
                    {
                        TreeItemData* tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(s));
                        CreateNodeDialog* create_node_dialog = new CreateNodeDialog(this, tree_item_data->node);
                        if (create_node_dialog->ShowModal() == wxID_OK)
                        {
                            /*this->add_tree_item(create_node_dialog->createdNode, selected_tree_item_id);   
                            this->newNode = create_node_dialog->createdNode;                    
                            this->objectTree->Expand(selected_tree_item_id);
                            this->inspector->setNode(create_node_dialog->createdNode);*/
                        }
                    }
                }
                break;
            case CONTEXTMENU_REMOVENODE:
                {
                    for (auto s : selections)
                    {
                        this->remove_tree_item(s);
                    }
                }
                break;
            case CONTEXTMENU_SAVE:
                {
                    wxFileDialog* d = new wxFileDialog(this, "Save As");
                    if (d->ShowModal() == wxID_OK)
                    {
                        Serializer s;
                        TreeItemData* tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(selections[0]));
                        s.serializeToFile(tree_item_data->node, Serializer::PARSER_JSONCPP, d->GetPath().c_str());
                    }
                }
                break;
            case CONTEXTMENU_LOAD:
                {
                    wxFileDialog* d = new wxFileDialog(this, "Load");
                    if (d->ShowModal() == wxID_OK)
                    {
                        Serializer s;

                        TreeItemData* tree_item_data = nullptr;
                        for (auto i : selections)
                        {
                            tree_item_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(i));
                            Node* load_node = s.deserializeFromFile(Serializer::PARSER_JSONCPP, d->GetPath().c_str());
                            if (nullptr==load_node) return;
                            tree_item_data->node->addChild(load_node);

                            this->add_tree_item(load_node, i);
                            this->objectTree->Expand(i);
                        }
                        
                        this->self->dispatchEvent(EVENT_SELECTED_NODE, tree_item_data->node);
                    }
                }
                break;
            case CONTEXTMENU_EDITOR:
                {
                    //TreeItemData* data = (TreeItemData*)this->objectTree->GetItemData(selected_tree_item_id);
                    //ToolExtensionMgr::instance()->openTool(data->node->getType()->name.c_str(), data->node);
                }
                break;
            }
        }

        wxTreeItemId add_tree_item(Node* node, wxTreeItemId parent_tree_item_id)
        {
            if (!parent_tree_item_id.IsOk()) parent_tree_item_id = this->objectTree->GetSelection();

            //append tree item
            TreeItemData* item_data = new TreeItemData(node);
            wxTreeItemId new_tree_item_id = this->objectTree->AppendItem(parent_tree_item_id, node->getName(), -1, -1, item_data);
            this->objectTree->SetItemHasChildren(parent_tree_item_id);

            //add + mark
            if (node->getNumChildren() == 0) return new_tree_item_id;
            this->objectTree->SetItemHasChildren(new_tree_item_id);

            return new_tree_item_id;
        } 

        void remove_tree_item(wxTreeItemId selected_tree_item_id)
        {
            //remove from parent
            if (selected_tree_item_id == this->objectTree->GetRootItem()) return;
            wxTreeItemId parent_tree_item_id = this->objectTree->GetItemParent(selected_tree_item_id);
            TreeItemData* parent_data = static_cast<TreeItemData*>(this->objectTree->GetItemData(parent_tree_item_id));
            TreeItemData* data = static_cast<TreeItemData*>(this->objectTree->GetItemData(selected_tree_item_id));
            if (data->node->getParent()==0) return;
            data->node->removeFromParent();

            //delete tree item
            this->objectTree->Delete(selected_tree_item_id);
            if (parent_data->node->getNumChildren() == 0) this->objectTree->SetItemHasChildren(parent_tree_item_id, false);
            
            //dispatch select node event
            this->self->dispatchEvent(EVENT_SELECTED_NODE, 0);
        }

    public:
        class TreeItemData : public wxTreeItemData
        {
        public:
            TreeItemData(Node* node):node(node) {}
            tod::Ref<Node> node;
        };

    public:
        wxSearchCtrl* searchCtrl;
        wxTreeCtrl* objectTree;
        wxMenu* contextMenu;
        wxMenuItem* editorContextMenuItem;
        wxTreeItemId dragTreeItemId;

        TodEditorObjectViewer* self;
        tod::Ref<Node> root;
    };

private:
    Panel* mainPanel;
    Selections selections;

};


}


