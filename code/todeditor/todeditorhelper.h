#pragma once
#include "precompiled.h"
namespace tod
{


class TodEditorHelper
{
public:
    static wxImageList* loadImageList()
    {
        //wxImageList* new_image_list = new wxImageList();
        //wxImage image;
        //image.AddHandler(new wxPNGHandler());
        //image.LoadFile((TodEditorHelper::s_art_path + "close_tree_item.png"), wxBITMAP_TYPE_PNG);

        return 0;
    }


    static std::string s_art_path;
};


}
