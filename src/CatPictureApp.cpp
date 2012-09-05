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
	int leftEyeSize;
	int rightEyeSize;
	int eyeColor;
	int movingx;
	int movingy;
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

	mySurface_ = new Surface(textureSize,textureSize,false);
	myTexture_ = new gl::Texture(*mySurface_);
	uint8_t* pixelArray = (*mySurface_).getData();
	leftEyeSize = 30;
	rightEyeSize = 40;
	eyeColor = 255;
	movingx = 25;
	movingy = 25;
	
}

void CatPictureApp::circle(uint8_t* pixels, int radius, int centerx, int centery, Color8u c){

	if(radius <= 0) 
		return;

	for(int y = centery - radius; y <= centery + radius; y++){
		// starts from top of circle
		for(int x = centerx - radius; x <= centerx + radius; x++){
			//starts from left side of circle and draws a horizontal line

			if(y < 0 || x < 0 || x >= appWidth || y >= appHeight) 
				continue;

			int distance = (int) sqrt(pow((x - centerx), 2.0)  + pow((y - centery), 2.0));
			// use distance formula to find the distance between the pixel the program is at
			// and the center pixel of the circle.

			if(distance <= radius){
				pixels[3 * (x + y * textureSize)] = c.r;
				pixels[3 * (x + y * textureSize) + 1] = c.g;
				pixels[3 * (x + y * textureSize) + 2] = c.b;
			}
		}
	}
}

void CatPictureApp::triangle(uint8_t* pixels, int length, int x, int y, Color8u c){

	if(((x + length) <= appWidth) && ((y + length) <= appHeight)){

		int height = length;

		for(int count1 = 0; count1 <= height; count1++){
			// starts from bottom of the triangle
			for(int count2 = 0; count2 <= length; count2++){
				// starts from the left of the triangle and draws a horizontal line

		        pixels[(3 * x) + (y * textureSize * 3 )] = c.r;
		        pixels[(3 * x) + (y * textureSize * 3 ) + 1] = c.g;
		        pixels[(3 * x) + (y * textureSize * 3 ) + 2] = c.b;
		        x++;
	        }
			x = x - length; // reset x so you start above the last horizontal line
			length = length - 2; // subtract 1 pixel from each side of the next line
			y--; // moves to the row of pixels above the last line we drew
		}
    }
}


void CatPictureApp::gradient(uint8_t* pixels, int x, int y){
	
	Color8u c = Color8u(255, 0, 0);
	
	for(int y = 0; y < textureSize; y++){
		// starts from the top of the window
		for(int x = 0; x < appWidth; x++){
			// starts from the left of the window

			int num = (int)((256 * x) / appWidth);
			// number that you add to the color so that you don't reset to black or
			// go past the appWidth
        
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
	// these determine which are the starting and ending points of the rectangle

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
		// starts from top
		for(int x = startx; x < endx; x++){
			// starts from the left and draws a horizontal line

		pixels[(3 * x) + (y * textureSize * 3 )] = c.r;
		pixels[(3 * x) + (y * textureSize * 3) + 1] = c.g;
		pixels[(3 * x) + (y * textureSize * 3) + 2] = c.b;
		}
	}
}

void CatPictureApp::mouseDown( MouseEvent event ){
}

void CatPictureApp::update(){

	if(leftEyeSize < 40)
		leftEyeSize++;
	else
		leftEyeSize = 30;
	// animates size of left eye

	if(eyeColor <= 255 && eyeColor != 0)
		eyeColor--;
	else
		eyeColor = 255;
	// animates color of both eyes

	if(rightEyeSize > 30)
		rightEyeSize--;
	else
		rightEyeSize = 40;
	// animates size of right eye

	uint8_t* pixelArray = (*mySurface_).getData();
	gradient(pixelArray, 0, 0);
	triangle(pixelArray, 230, 350, 170, Color8u(175, 175, 175)); // right ear
	triangle(pixelArray, 230, 230, 170, Color8u(175, 175, 175)); // left ear
	circle(pixelArray, 175, 400, 300, Color8u(100, 100, 100)); // head
	triangle(pixelArray, 55, 375, 300, Color8u(30, 30, 30)); // nose
	circle(pixelArray, leftEyeSize, 250, 225, Color8u(0, 0, eyeColor)); // left eye
	circle(pixelArray, rightEyeSize, 550, 225, Color8u(eyeColor, 0, 0)); // right eye
	rectangle(pixelArray, 495, 520, 400, 450,Color8u(255,0,0)); // tounge
	rectangle(pixelArray, 300, 525, 375, 400, Color8u(255,0,0)); // mouth

	circle(pixelArray, 25, movingx, movingy, Color(255, 255, 255));

	if((movingx < (appWidth - 25)) && (movingy < (appHeight - 25))) 
		movingx = movingx + 25;
	else if((movingx == (appWidth - 25)) && (movingy < (appHeight - 25))) 
		movingy = movingy + 25;
	else if((movingx <= (appWidth - 25)) && (movingy == (appHeight - 25)))
		movingx = movingx - 25;
	else
		movingy = movingy - 25; 
}

void CatPictureApp::draw(){
	
	gl::draw(*mySurface_);
	
}

CINDER_APP_BASIC( CatPictureApp, RendererGl )
