#include "todirrlichtdevice.h"

namespace tod
{

//-----------------------------------------------------------------------------
TodIrrlichtDevice::~TodIrrlichtDevice()
{
	if (this->device)
	{
		this->device->closeDevice();
		this->device->drop();
	}
}


//-----------------------------------------------------------------------------	
bool TodIrrlichtDevice::initialize(void* window_handle)
{
	this->videoData.D3D9.HWnd = window_handle;

	irr::SIrrlichtCreationParameters param;
	param.DriverType = irr::video::EDT_OPENGL;
	param.WindowId = window_handle;

	this->device = irr::createDeviceEx(param);
	if (nullptr == device) return false;

	this->driver = this->device->getVideoDriver();
	this->sceneMgr = this->device->getSceneManager();



	this->cam = this->sceneMgr->addCameraSceneNode();    
    this->cam->setTarget(irr::core::vector3df(0, 0, 0));

	irr::scene::ISceneNodeAnimator* anim =
		this->sceneMgr->createFlyCircleAnimator(irr::core::vector3df(0, 15, 0), 30.0f, 0.0001);
	cam->addAnimator(anim);
	anim->drop();

	irr::scene::ISceneNode* cube = this->sceneMgr->addCubeSceneNode(20);

	cube->setMaterialTexture(0, driver->getTexture("../../../resource/wall.bmp"));
	cube->setMaterialTexture(1, driver->getTexture("../../../resource/water.jpg"));
	cube->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	cube->setMaterialType(irr::video::EMT_REFLECTION_2_LAYER);

	this->sceneMgr->addSkyBoxSceneNode(
		driver->getTexture("../../../resource/irrlicht2_up.jpg"),
		driver->getTexture("../../../resource/irrlicht2_dn.jpg"),
		driver->getTexture("../../../resource/irrlicht2_lf.jpg"),
		driver->getTexture("../../../resource/irrlicht2_rt.jpg"),
		driver->getTexture("../../../resource/irrlicht2_ft.jpg"),
		driver->getTexture("../../../resource/irrlicht2_bk.jpg"));

    return true;
}


//-----------------------------------------------------------------------------
bool TodIrrlichtDevice::pump()
{   
	if (!this->device->run()) return false;

	this->driver->beginScene(true, true, 0, this->videoData);
	this->sceneMgr->drawAll();
	this->driver->endScene();

	return true;
}


//-----------------------------------------------------------------------------
void TodIrrlichtDevice::resizeViewport(int w, int h)
{
    this->driver->OnResize(irr::core::dimension2d<irr::u32>(w, h));
    this->cam->setAspectRatio((float)w / h);
}

}
