#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class DrawingACircleApp : public App {
public:
	void setup() override;
	void draw() override;
	
protected:
	gl::BatchRef mBatch;
};

void DrawingACircleApp::setup() {
	auto geometry = geom::Circle()
		.subdivisions(128)
		.radius(getWindowHeight() * 0.5f)
		.center(vec2(getWindowSize()) * 0.5f);
	auto shaders = gl::getStockShader(gl::ShaderDef().color());
	mBatch = gl::Batch::create(geometry, shaders);
	gl::enableWireframe();
}

void DrawingACircleApp::draw() {
	gl::clear();
	mBatch->draw();
}

CINDER_APP(DrawingACircleApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(DrawingACircleApp, RendererGl());

