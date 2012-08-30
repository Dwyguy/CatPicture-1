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
	float brightness;
	  
};

void CatPictureApp::setup()
{
	brightness = 1.0f;
}

void CatPictureApp::mouseDown( MouseEvent event )
{
}

void CatPictureApp::update()
{
	brightness = brightness - 0.01f;
	if( brightness < 0.0f){
		brightness = 1.0f;
	}
}

void CatPictureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( brightness, brightness, brightness ) ); 
	gl::Texture catPicture( loadImage( loadResource( RES_SNOWBOARD ) ) );
	gl::draw(catPicture);
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
