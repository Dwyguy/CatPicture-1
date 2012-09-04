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
	void prepareSettings(Settings* settings);

  private:
	Surface* mySurface_;
	uint8_t* pixels;
	gl::Texture* myTexture_;
	Surface cat_picture;
	static const int appWidth=800;
	static const int appHeight=600;
	static const int textureSize=1024;
	void rectangle(uint8_t* pixels, int x1, int x2, int y1, int y2, Color8u c);
	void gradient(uint8_t* pixels, int x, int y);
	  
};

void CatPictureApp::prepareSettings(Settings* settings){
	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup()
{
	Surface cat_picture(loadImage( loadResource(RES_SNOWBOARD) ));
	mySurface_ = new Surface(textureSize,textureSize,false);
	myTexture_ = new gl::Texture(*mySurface_);
	uint8_t* pixelArray = (*mySurface_).getData();
	
}

void CatPictureApp::gradient(uint8_t* pixels, int x, int y){
	
	Color8u c = Color8u(0,0,0);
	
	for(int y = 0; y < textureSize; y++){
		for(int x = 0; x < textureSize; x++){

			int num = (int)((256 * x) / appWidth);
        
		pixels[(3 * x) + (y * textureSize * 3 )] = c.r;
		pixels[(3 * x) + (y * textureSize * 3) + 1] = c.g;
		pixels[(3 * x) + (y * textureSize * 3) + 2] = c.b + num;
		
		}
	}
}

void CatPictureApp::rectangle(uint8_t* pixels, int x1, int x2, int y1, int y2, Color8u c){


	int startx = (x1 < x2) ? x1 : x2;
	int endx = (x1 < x2) ? x2 : x1;
	int starty = (y1 < y2) ? y1 : y2;
	int endy = (y1 < y2) ? y2 : y1;

	if(endx < 0)
		return; 
	if(endy < 0) 
		return; 
	if(startx >= appWidth) 
		return; 
	if(starty >= appHeight) 
		return;
	if(endx >= appWidth) endx = appWidth - 1;
	if(endy >= appHeight) endy = appHeight - 1;

	for(int y = starty; y < endy; y++){
		for(int x = startx; x < endx; x++){
		pixels[(3 * x) + (y * textureSize * 3 )] = c.r;
		pixels[(3 * x) + (y * textureSize * 3) + 1] = c.g;
		pixels[(3 * x) + (y * textureSize * 3) + 2] = c.b;
		}
	}
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	
	uint8_t* pixelArray = (*mySurface_).getData();
	gradient(pixelArray,0,0);
	rectangle(pixelArray, 100, 200, 100, 200, Color8u(255,0,0));
	
}

void CatPictureApp::draw()
{
	
	gl::draw(*mySurface_);
	
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
