#pragma once
#include "todcore/node.h"
#include "irrlicht.h"
namespace tod
{


class TodIrrlichtDevice : public Derive<TodIrrlichtDevice, Node>
{
public:
	virtual~TodIrrlichtDevice();

	bool initialize(void* window_handle);
	bool pump();
	void resizeViewport(int w, int h);

private:
	irr::IrrlichtDevice* device;
	irr::video::SExposedVideoData videoData;
	irr::video::IVideoDriver* driver;
	irr::scene::ISceneManager* sceneMgr;

public:
    irr::scene::ICameraSceneNode* cam;
};


}
