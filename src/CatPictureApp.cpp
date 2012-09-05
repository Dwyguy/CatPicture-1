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
	void circle(uint8_t* pixels, int radius, int centerx, int centery, Color8u c);
	void triangle(uint8_t* pixels, int length, int x, int y, Color8u c);
};

void CatPictureApp::prepareSettings(Settings* settings){

	(*settings).setWindowSize(appWidth,appHeight);
	(*settings).setResizable(false);
}

void CatPictureApp::setup(){

	Surface cat_picture(loadImage( loadResource(RES_SNOWBOARD) ));
	mySurface_ = new Surface(textureSize,textureSize,false);
	myTexture_ = new gl::Texture(*mySurface_);
	uint8_t* pixelArray = (*mySurface_).getData();
	
}

void CatPictureApp::circle(uint8_t* pixels, int radius, int centerx, int centery, Color8u c){

	if(radius <= 0)
		return;

	for(int y = centery - radius; y <= centery + radius; y++){
		for(int x = centerx - radius; x <= centerx + radius; x++){

			if(y < 0 || x < 0 || x >= appWidth || y >= appHeight) 
				continue;

			int distance = (int) sqrt(pow((x - centerx), 2.0)  + pow((y - centery), 2.0));

			if(distance <= radius){
				pixels[3 * (x + y * textureSize)] = c.r;
				pixels[3 * (x + y * textureSize) + 1] = c.g;
				pixels[3 * (x + y * textureSize) + 2] = c.b;
			}
		}
	}
}

void CatPictureApp::triangle(uint8_t* pixels, int length, int x, int y, Color8u c){

	if((x + length) <= appWidth){

		int height = length;

		for(int count1 = 0; count1 <= height; count1++){
			for(int count2 = 0; count2 <= length; count2++){

		        pixels[(3 * x) + (y * textureSize * 3 )] = c.r;
		        pixels[(3 * x) + (y * textureSize * 3 ) + 1] = c.g;
		        pixels[(3 * x) + (y * textureSize * 3 ) + 2] = c.b;
		        x++;
	        }
			x = x - length;
			length = length - 2;
			y--;
		}
    }
}


void CatPictureApp::gradient(uint8_t* pixels, int x, int y){
	
	Color8u c = Color8u(0, 0, 0);
	
	for(int y = 0; y < textureSize; y++){
		for(int x = 0; x < appWidth; x++){

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

void CatPictureApp::mouseDown( MouseEvent event ){
}

void CatPictureApp::update(){

	uint8_t* pixelArray = (*mySurface_).getData();
	gradient(pixelArray, 0, 0);
	triangle(pixelArray, 175, 370, 170, Color8u(175, 175, 175)); 
	triangle(pixelArray, 175, 250, 170, Color8u(175, 175, 175));
	circle(pixelArray, 175, 400, 300, Color8u(100, 100, 100));
	triangle(pixelArray, 55, 375, 300, Color8u(30, 30, 30));
	circle(pixelArray, 30, 250, 225, Color8u(70, 255, 70));
	circle(pixelArray, 40, 550, 225, Color8u(70, 255, 70));
	rectangle(pixelArray, 495, 520, 400, 450,Color8u(255,0,0));
	rectangle(pixelArray, 300, 525, 375, 400, Color8u(255,0,0));
}

void CatPictureApp::draw(){
	
	gl::draw(*mySurface_);
	
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
