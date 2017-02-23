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
	auto geometry = geom::Rect().rect(rect);
	auto shaders = gl::GlslProg::create(
			// Vertex shader
			CI_GLSL(150,
				uniform mat4 ciModelViewProjection;
				in vec4 ciPosition;
				out vec4 vPosition;
					
				void main(void) {
					vPosition = ciPosition;
					gl_Position = ciModelViewProjection * ciPosition;
				}
			),
			// Fragment shader
			CI_GLSL(150,
				uniform vec2 uSize;
				in vec4 vPosition;
				out vec4 oColor;
				
				void main(void) {
					vec4 color = vec4(vPosition.x / uSize.x, vPosition.y / uSize.y, 0, 1);
					oColor = color;
				}
			)
	);
	
	mBatch = gl::Batch::create(geometry, shaders);
	mBatch->getGlslProg()->uniform("uSize", rect.getSize());
}

void MixingColorsApp::draw() {
	gl::clear();
	mBatch->draw();
}

CINDER_APP(MixingColorsApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(MixingColorsApp, RendererGl());

