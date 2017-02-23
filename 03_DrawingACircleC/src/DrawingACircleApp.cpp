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
	auto rect = Rectf(ivec2(0), getWindowSize());
	auto geometry = geom::Rect().rect(rect);
	auto shaders = gl::GlslProg::create(
		// Vertex shader
		CI_GLSL(150,
			uniform mat4 ciModelViewProjection;
			in vec4 ciPosition;
			void main(void) {
				gl_Position = ciModelViewProjection * ciPosition;
			}
		),
		// Fragment shader
		CI_GLSL(150,
			out vec4 oColor;
			
			void main(void) {
				oColor = vec4(1, 1, 1, 1);
			}
		)
	);
	
	mBatch = gl::Batch::create(geometry, shaders);
}

void DrawingACircleApp::draw() {
	gl::clear();
	mBatch->draw();
}

CINDER_APP(DrawingACircleApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(DrawingACircleApp, RendererGl());

