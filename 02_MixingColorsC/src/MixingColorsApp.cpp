#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class MixingColorsApp : public App {
  public:
	void setup() override;
	void draw() override;
	
protected:
	gl::BatchRef mBatch;
};

void MixingColorsApp::setup() {
	auto rect = Rectf(ivec2(0), getWindowSize());
	auto geometry = geom::Rect()
		.rect(rect)
		.colors(ColorAf(0, 0, 0, 1), ColorAf(1, 0, 0, 1),
				ColorAf(1, 1, 0, 1), ColorAf(0, 1, 0, 1));

	auto shaders = gl::GlslProg::create(
		// Vertex shader
		CI_GLSL(150,
			uniform mat4 ciModelViewProjection;
			in vec4 ciPosition;
			in vec4 ciColor;
			out vec4 vColor;
				
			void main(void) {
				vColor = ciColor;
				gl_Position = ciModelViewProjection * ciPosition;
			}
		),
		// Fragment shader
		CI_GLSL(150,
			in vec4 vColor;
			out vec4 oColor;
			
			void main(void) {
				oColor = vColor;
			}
		)
	);
	
	mBatch = gl::Batch::create(geometry, shaders);
}

void MixingColorsApp::draw() {
	gl::clear();
	mBatch->draw();
}

CINDER_APP(MixingColorsApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(MixingColorsApp, RendererGl());

