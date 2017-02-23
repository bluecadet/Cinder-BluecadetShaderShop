#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SimpleVertexShaderApp : public App {
  public:
	void setup() override;
	void draw() override;
	
protected:
	gl::BatchRef mBatch;
};

void SimpleVertexShaderApp::setup() {
	auto rect = Rectf(ivec2(50), getWindowSize() - ivec2(50));
	auto geometry = geom::Rect().rect(rect);
	auto shaders = gl::GlslProg::create(
			// Vertex shader
			CI_GLSL(150,
				uniform float ciElapsedSeconds;
				uniform mat4 ciModelViewProjection;
				in vec4 ciPosition;
				
				void main(void) {
					vec4 pos = ciPosition;
					pos.x += 25.0 * cos(ciElapsedSeconds);
					pos.y += 25.0 * sin(ciElapsedSeconds);
					gl_Position = ciModelViewProjection * pos;
				}
			),
			// Fragment shader
			CI_GLSL(150,
				out vec4 oColor;
				
				void main(void) {
					oColor = vec4(1, 0, 0, 1);
				}
			)
	);
	
	mBatch = gl::Batch::create(geometry, shaders);
}

void SimpleVertexShaderApp::draw() {
	gl::clear();
	mBatch->draw();
}

CINDER_APP(SimpleVertexShaderApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(SimpleVertexShaderApp, RendererGl());

