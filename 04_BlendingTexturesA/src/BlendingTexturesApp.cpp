#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BlendingTexturesApp : public App {
public:
	void setup() override;
	void draw() override;
	
protected:
	gl::BatchRef mBatch;
	gl::Texture2dRef mTexture;
};

void BlendingTexturesApp::setup() {
	auto rect = Rectf(ivec2(0), getWindowSize());
	auto geometry = geom::Rect().rect(rect);
	auto shaders = gl::getStockShader(gl::ShaderDef().texture()); // .texture() this will draw the currently bound texture
	
	auto image = loadImage(loadAsset("texture01.jpg"));
	mTexture = gl::Texture2d::create(image);
	
	mBatch = gl::Batch::create(geometry, shaders);
}

void BlendingTexturesApp::draw() {
	gl::clear();
	mTexture->bind(); // set as the currently bound texture
	mBatch->draw();
}

CINDER_APP(BlendingTexturesApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(BlendingTexturesApp, RendererGl());

