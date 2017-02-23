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
	gl::Texture2dRef mTextureA;
	gl::Texture2dRef mTextureB;
};

void BlendingTexturesApp::setup() {
	auto rect = Rectf(ivec2(0), getWindowSize());
	auto geometry = geom::Rect().rect(rect);
	auto shaders = gl::GlslProg::create(
		// Vertex shader
		CI_GLSL(150,
			uniform mat4 ciModelViewProjection;
			in vec4 ciPosition;
			in vec2 ciTexCoord0;
			out vec2 vTexCoord0;
			
			void main(void) {
				vTexCoord0 = ciTexCoord0;
				gl_Position = ciModelViewProjection * ciPosition;
			}
		),
		// Fragment shader
		CI_GLSL(150,
			const float M_PI = 3.14159265359;
			uniform sampler2D uTex0;
			uniform sampler2D uTex1;
			uniform float ciElapsedSeconds;
			in vec2 vTexCoord0;
			out vec4 oColor;
			
			void main(void) {
				vec4 colorA = texture(uTex0, vTexCoord0);
				vec4 colorB = texture(uTex1, vTexCoord0);
				oColor = mix(colorA, colorB, 0.5 + 0.5 * sin(ciElapsedSeconds + vTexCoord0.x));
			}
		)
	);

	mBatch = gl::Batch::create(geometry, shaders);

	mTextureA = gl::Texture2d::create(loadImage(loadAsset("texture01.jpg")));
	mTextureB = gl::Texture2d::create(loadImage(loadAsset("texture02.jpg")));

	mTextureA->bind(0); // set as the currently bound texture at index 0
	mTextureB->bind(1); // set as the currently bound texture at index 1

	mBatch->getGlslProg()->uniform("uTex0", 0); // uTex0 is defined as 0 by default in Cinder
	mBatch->getGlslProg()->uniform("uTex1", 1); // uTex1 is not defined by Cinder, so we have to do this
}

void BlendingTexturesApp::draw() {
	gl::clear();
	mBatch->draw();
}

CINDER_APP(BlendingTexturesApp, RendererGl(RendererGl::Options().msaa(8)));
//CINDER_APP(BlendingTexturesApp, RendererGl());

