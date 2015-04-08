#pragma once
#include "todcore/node.h"
#include "todcore/property.h"
#include "todcore/simpleproperty.h"
#include "todcore/enumproperty.h"
#include "todcore/type.h"
#include "todcore/typeid.h"
namespace tod
{


class TodEditorInspector : public Derive<TodEditorInspector, Node>
{
public:
    TodEditorInspector()
    {
    }

    void initialize(wxWindow* parent)
    {
        this->mainPanel = new MainPanel(parent);
    }

    wxPanel* getMainPanel()
    {
        return this->mainPanel;
    }

    void setNodes(const Selections& nodes)
    {
        this->mainPanel->setNodes(nodes);
    }

private:
    class FolderPanel : public wxWindow
    {
    public:
        FolderPanel(wxWindow* parent, const wxString& subject):
        wxWindow(parent, -1),
        subjectPanel(nullptr),
        container(nullptr)
        {
            wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
            this->SetSizer(sizer);
            this->SetBackgroundColour(TodEditorInspector::s_backgroundColor2);

            //subject
            this->subjectPanel = new SubjectPanel(this, subject);
            sizer->Add(this->subjectPanel, 0, wxEXPAND);
        }
        void setContainer(wxWindow* container)
        {
            this->container = container;
            this->GetSizer()->Clear();
            this->GetSizer()->Add(this->subjectPanel, 0, wxEXPAND);
            this->GetSizer()->AddSpacer(1);
            this->GetSizer()->Add(this->container, 0, wxEXPAND);
        }

        void fold()
        {
            this->container->Hide();
            this->GetGrandParent()->Layout();
        }

        void unfold()
        {
            this->container->Show();
            this->GetGrandParent()->Layout();
        }

    private:
        class SubjectPanel : public wxWindow
        {
        public:
            SubjectPanel(wxWindow* parent, const wxString& subject):
            wxWindow(parent, -1),
            subject(subject)
            {
                this->SetFont(wxFont(9, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, "Consolas"));
                this->SetMinSize(wxSize(this->GetTextExtent(this->subject).GetWidth() + 10, 22));
                this->Connect(wxEVT_PAINT, (wxObjectEventFunction)&SubjectPanel::on_paint, 0, this);
                this->Connect(wxEVT_LEFT_UP, (wxObjectEventFunction)&SubjectPanel::on_mouse_left_up, 0, this);
            }
            void on_paint(wxPaintEvent& e)
            {
                wxPaintDC dc(this);
                dc.GradientFillLinear(this->GetRect(), TodEditorInspector::s_backgroundColor1, wxColour(28, 30, 24), wxSOUTH);
                dc.SetTextForeground(*wxWHITE);
                dc.SetFont(this->GetFont());
                dc.DrawText(this->subject, 5, 3);
            }
            void on_mouse_left_up(wxMouseEvent& e)
            {
                FolderPanel* folder_panel = static_cast<FolderPanel*>(this->GetParent());
                if (folder_panel->container->IsShown()) folder_panel->fold();
                else folder_panel->unfold();
            }
            wxString subject;
        };

    private:
        SubjectPanel* subjectPanel;
        wxWindow* container;
    };

    class PropertyItem : public wxWindow
    {
    public:
        PropertyItem(wxWindow* parent):
        wxWindow(parent, -1)
        {
            wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
            this->SetSizer(sizer);
            this->SetBackgroundColour(TodEditorInspector::s_backgroundColor1);
        }
        void setTarget(Node* node, Property* prop)
        {
            if (this->node == node && this->property == prop) return;
            this->node = node;
            this->property = prop;
            this->GetSizer()->Clear(true);

            //property name
            wxStaticText* prop_name_static_text = new wxStaticText(this, -1, prop->getName());
            prop_name_static_text->SetFont(TodEditorInspector::s_font1);
            if (this->property->isReadOnly()) prop_name_static_text->SetForegroundColour(TodEditorInspector::s_textColor2);
            else prop_name_static_text->SetForegroundColour(TodEditorInspector::s_textColor1);
            prop_name_static_text->SetBackgroundColour(TodEditorInspector::s_backgroundColor1);
            prop_name_static_text->SetMinSize(wxSize(100, 18));
            this->GetSizer()->AddSpacer(10);
            this->GetSizer()->Add(prop_name_static_text, 0, wxEXPAND);
            this->GetSizer()->AddSpacer(1);

            //property editor
            wxWindow* editor = this->create_editor(node, prop);
            editor->SetFont(TodEditorInspector::s_font1);
            if (this->property->isReadOnly()) editor->SetForegroundColour(TodEditorInspector::s_textColor2);
            else editor->SetForegroundColour(TodEditorInspector::s_textColor1);
            editor->SetBackgroundColour(TodEditorInspector::s_backgroundColor1);
            this->GetSizer()->Add(editor, 1, wxEXPAND | wxALIGN_CENTRE_VERTICAL);

        }

    public:
        wxWindow* create_editor(Node* node, Property* prop)
        {
            if (prop->isEnumable())
            {
                if (TypeId<int>::check(prop->getType()))
                {
                    typedef EnumProperty<int> EP;
                    EP* eprop = static_cast<EP*>(prop);
                    wxArrayString as;
                    for (auto i : eprop->getEnumList(node)) as.Add(i);
                    
                    int option = wxBORDER_SIMPLE | wxTE_PROCESS_ENTER;
                    if (prop->isReadOnly()) option |= wxTE_READONLY;
                    wxComboBox* combo = new wxComboBox(this, -1, wxEmptyString, wxDefaultPosition, wxDefaultSize, as, option);
                    
                    return combo;
                }
            }
            else if (TypeId<bool>::check(prop->getType()))
            {
                typedef SimpleProperty<bool> SP;
                SP* sprop = static_cast<SP*>(prop);

                wxCheckBox* checkbox = new wxCheckBox(this, -1, wxEmptyString);
                checkbox->SetValue(sprop->get(node));
                if (prop->isReadOnly()) checkbox->Disable();

                return checkbox;
            }
            else if (
                TypeId<int>::check(prop->getType()) ||
                TypeId<unsigned int>::check(prop->getType()) ||
                TypeId<int32>::check(prop->getType()) ||
                TypeId<uint32>::check(prop->getType()) ||
                TypeId<float>::check(prop->getType()) ||
                TypeId<double>::check(prop->getType()) ||
                TypeId<const char*>::check(prop->getType()) ||
                TypeId<const String&>::check(prop->getType()))
            {
                String value;
                prop->toString(node, value);

                int option = wxBORDER_NONE | wxTE_PROCESS_ENTER;
                if (prop->isReadOnly()) option |= wxTE_READONLY;
                wxTextCtrl* text_ctrl = new wxTextCtrl(this, -1, value, wxDefaultPosition, wxDefaultSize, option);
                text_ctrl->SetMinSize(wxSize(100, 16));
                text_ctrl->SetMaxSize(wxSize(9999, 16));
                return text_ctrl;
            }
            else if (TypeId<const Color&>::check(prop->getType()))
            {
                wxColourPickerCtrl* colour_picker_ctrl = new wxColourPickerCtrl(this, -1, wxStockGDI::COLOUR_BLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_USE_TEXTCTRL);
                //colour_picker_ctrl->Connect(wxEVT_COLOURPICKER_CHANGED, (wxObjectEventFunction)&PropertyEditSlot::on_update_colour_picker, 0, this);
                if (prop->isReadOnly()) colour_picker_ctrl->Disable();

                wxTextCtrl* text_ctrl = colour_picker_ctrl->GetTextCtrl();
                text_ctrl->SetWindowStyleFlag(wxBORDER_NONE);
                text_ctrl->SetMinSize(wxSize(100, 16));
                text_ctrl->SetMaxSize(wxSize(9999, 16));
                if (this->property->isReadOnly()) text_ctrl->SetForegroundColour(TodEditorInspector::s_textColor2);
                else text_ctrl->SetForegroundColour(TodEditorInspector::s_textColor1);
                text_ctrl->SetBackgroundColour(TodEditorInspector::s_backgroundColor1);
                return colour_picker_ctrl;
            }

            return nullptr;
        }

    public:
        Node* node;
        Property* property;
    };

    class PropertyListPanel : public wxWindow
    {
    public:
        PropertyListPanel(wxWindow* parent, Type* type, Node* node):
        wxWindow(parent, -1)
        {
            this->SetBackgroundColour(TodEditorInspector::s_backgroundColor2);
            this->SetSizer(new wxBoxSizer(wxVERTICAL));

            this->setup(type, node);
        }

        void setup(Type* type, Node* node)
        {
            FolderPanel* folder_panel = new FolderPanel(this, type->getName());
            this->GetSizer()->Add(folder_panel, 0, wxEXPAND);

            wxWindow* property_panel = new wxWindow(folder_panel, -1);
            property_panel->SetBackgroundColour(TodEditorInspector::s_backgroundColor2);
            folder_panel->setContainer(property_panel);
            wxBoxSizer* property_panel_sizer = new wxBoxSizer(wxVERTICAL);
            property_panel->SetSizer(property_panel_sizer);

            for (auto p : type->getProperties())
            {
                PropertyItem* pitem = new PropertyItem(property_panel);
                pitem->setTarget(node, p.second);
                property_panel_sizer->Add(pitem, 0, wxEXPAND);
                property_panel_sizer->AddSpacer(1);
            }
        }
    };

    class MainPanel : public wxPanel
    {
    public:
        MainPanel(wxWindow* parent):
        wxPanel(parent, -1)
        {
            this->SetBackgroundColour(TodEditorInspector::s_backgroundColor1);
            this->SetSizer(new wxBoxSizer(wxVERTICAL));
        }

        void setNodes(const Selections& nodes)
        {
            this->nodes = nodes;

            //최대로 같은 base type을 찾는다
            auto gct = [](const Selections& nodes) -> Type*
            {
                typedef std::stack<Type*> InheritStruct;
                typedef std::list<InheritStruct> InheritStructList;
                InheritStructList l;
                for (auto i : nodes)
                {
                    l.push_back(InheritStruct());
                    InheritStruct& is = l.back();
                    Type* cur = i.get()->getType();
                    while (cur)
                    {
                        is.push(cur);
                        cur = cur->getBaseType();
                    }
                }

                InheritStruct& is = l.front();
                Type* check_type = nullptr;
                Type* greated_common_type = Object::get_type();
                while (is.size())
                {   
                    check_type = is.top();
                    for (auto& i : l)
                    {
                        if (i.top() == check_type)
                        {
                            i.pop();
                            continue;
                        }
                        else return greated_common_type;
                    }
                    greated_common_type = check_type;
                }

                return greated_common_type;
            };
            Type* type = gct(nodes);
            if (nullptr == type) return;


            //PropertyItem 에디터를 만든다
            this->Freeze();
            this->GetSizer()->Clear(true);            
            Type* cur = type;
            while (cur)
            {
                PropertyListPanel* property_list_panel = new PropertyListPanel(this, cur, nodes.front().get());
                this->GetSizer()->Add(property_list_panel, 0, wxEXPAND);
                cur = cur->getBaseType();
            }            
            this->GetSizer()->Layout();
            this->Thaw();
        }

    private:
        Selections nodes;
    };

private:
    MainPanel* mainPanel;

public:
    static wxColour s_backgroundColor1;
    static wxColour s_backgroundColor2;
    static wxColour s_textColor1;
    static wxColour s_textColor2;
    static wxFont s_font1;
};



}
