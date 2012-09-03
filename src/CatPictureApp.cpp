/**
 * CatPictureApp.cpp
 * A simple app that displays a picture of a cat
 *
 * @author Stevie Yakkel
 * @Date 8/30/2012
 */

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class CatPictureApp : public AppBasic {
  public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

  private:
	Surface* mySurface_;
	uint8_t* pixels;
	gl::Texture* myTexture_;
	static const int appWidth=800;
	static const int appHeight=600;
	static const int textureSize=1024;
	void rectangle(int x, int y, int width, int height, Color8u color, uint8_t* pixels);
	  
};

void CatPictureApp::setup()
{
	Surface cat_picture(loadImage( loadResource(RES_SNOWBOARD) ));
	mySurface_ = new Surface(textureSize,textureSize,false);
	myTexture_ = new gl::Texture(cat_picture);
	uint8_t* pixels = cat_picture.getData();
	
}

void CatPictureApp::rectangle(int x, int y, int width, int height, Color8u color, uint8_t* pixels){

	x = 0;
	y = 0;
	width = 1000;
	height = 100;
	Color8u c = Color8u(0,0,0);
	for(x; x<width; x++){
		pixels[3*x] = c.r;
		pixels[3*x+1] = c.b;
		pixels[3*x+2] = c.g;

	}
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	
}

void CatPictureApp::draw()
{
	
	gl::draw(*myTexture_);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
