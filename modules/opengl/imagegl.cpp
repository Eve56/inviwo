#include "imagegl.h"
#include "glwrap/shader.h"

namespace inviwo {

    ImageGL::ImageGL()
        : ImageRepresentation(ivec2(256,256))
    {
        initialize();
    }

    ImageGL::ImageGL(ivec2 dimensions)
        : ImageRepresentation(dimensions)
    {
        initialize();
    }

    ImageGL::~ImageGL() {}

    void ImageGL::initialize() {
        frameBufferObject_ = new FrameBufferObject();
        frameBufferObject_->activate();
        colorTexture_ = new Texture2D(dimensions_, GL_RGBA, GL_RGBA8, GL_UNSIGNED_BYTE, GL_LINEAR);
        colorTexture_->bind();
        colorTexture_->upload();
        frameBufferObject_->attachTexture(colorTexture_);
        depthTexture_ = new Texture2D(dimensions_, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT16, GL_FLOAT, GL_LINEAR);
        depthTexture_->bind();
        depthTexture_->upload();
        frameBufferObject_->attachTexture(depthTexture_, GL_DEPTH_ATTACHMENT);
        frameBufferObject_->deactivate();
        frameBufferObject_->checkStatus();

        shader_ = new Shader("img_texturequad.frag");
    }

    void ImageGL::deinitialize() {
        frameBufferObject_->deactivate();
        delete frameBufferObject_;
        frameBufferObject_ = 0;
        colorTexture_->unbind();
        delete colorTexture_;
        colorTexture_ = 0;
        depthTexture_->unbind();
        delete depthTexture_;
        depthTexture_ = 0;
        delete shader_;
        shader_=0;
    }

    DataRepresentation* ImageGL::clone() {
        ImageGL* newImageGL = new ImageGL(dimensions_);  

        if (getColorTexture()->getTexels()) {
            memcpy(newImageGL->getColorTexture()->getTexels(), getColorTexture()->getTexels(), 
                   dimensions_.x*dimensions_.y*sizeof(GLubyte));
        }
        if (getDepthTexture()->getTexels()) {
            memcpy(newImageGL->getDepthTexture()->getTexels(), getDepthTexture()->getTexels(),
                   dimensions_.x*dimensions_.y*sizeof(GLubyte));
        }
        return newImageGL;
    }

    void ImageGL::activateBuffer() {
        frameBufferObject_->activate();
        glViewport(0, 0, colorTexture_->getWidth(), colorTexture_->getHeight());
    }

    void ImageGL::deactivateBuffer() {
        frameBufferObject_->deactivate();
    }

    void ImageGL::bindColorTexture(GLenum texUnit) {
        glActiveTexture(texUnit);
        colorTexture_->bind();
    }

    void ImageGL::bindDepthTexture(GLenum texUnit) {
        glActiveTexture(texUnit);
        depthTexture_->bind();
    }

    void ImageGL::bindTextures(GLenum colorTexUnit, GLenum depthTexUnit) {
        bindColorTexture(colorTexUnit);
        bindDepthTexture(depthTexUnit);
    }

    void ImageGL::unbindDepthTexture() {
        depthTexture_->unbind();
    }

    void ImageGL::unbindColorTexture() {
        colorTexture_->unbind();
    }

    void ImageGL::resize(ivec2 dimensions) {
        dimensions_ = dimensions;        
        colorTexture_->unbind();
        colorTexture_->setWidth(dimensions_.x);
        colorTexture_->setHeight(dimensions_.y);
        colorTexture_->upload();
        colorTexture_->unbind();

        depthTexture_->unbind();
        depthTexture_->setWidth(dimensions_.x);
        depthTexture_->setHeight(dimensions_.y);
        depthTexture_->upload();
        depthTexture_->unbind();
    }

    void ImageGL::copyAndResizeImage(DataRepresentation* targetRep) {
        
        ImageGL* source = this;
        ImageGL* target = dynamic_cast<ImageGL*>(targetRep);

        if (!target) return;

        //TODO: Fix FBO blit

        //Resize by FBO blit
        /*FrameBufferObject* srcFBO = source->getFBO();
        FrameBufferObject* tgtFBO = target->getFBO();
        Texture2D* sTex = source->getColorTexture();
        Texture2D* tTex = target->getColorTexture();
        
        FrameBufferObject::deactivate();
        source->activateBuffer();
        srcFBO->setRead_Blit(); 
        //glReadBuffer(GL_COLOR_ATTACHMENT0_EXT);

        FrameBufferObject::deactivate();
        target->activateBuffer();
        tgtFBO->setDraw_Blit();
        //glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);        
                
        //srcFBO->attachTexture(sTex);
        //tgtFBO->attachTexture(tTex);        
        FrameBufferObject::deactivate();
        glDisable(GL_SCISSOR_TEST);
        glBlitFramebufferEXT(0, 0, sTex->getWidth(), sTex->getHeight(),
                             0, 0, tTex->getWidth()/2, tTex->getHeight()/2,
                             GL_COLOR_BUFFER_BIT, GL_LINEAR);
             
        srcFBO->setRead_Blit(false); 
        tgtFBO->setDraw_Blit(false);        
        FrameBufferObject::deactivate();
        */         
        
        //Resize by rendering
        ivec2 csize = target->dimension();        
        source->bindColorTexture(GL_TEXTURE0);
        target->activateBuffer();
        shader_->activate();
        shader_->setUniform("colorTex_", 0);
        shader_->setUniform("dimension_", vec2( 1.f / csize[0],  1.f / csize[1]) );
        renderImagePlaneQuad();
        shader_->deactivate();
        FrameBufferObject::deactivate();
        source->unbindColorTexture();        
    }

    void ImageGL::renderImagePlaneQuad() const {
        glDisable(GL_CULL_FACE);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glDepthFunc(GL_ALWAYS);
        glBegin(GL_QUADS);
        glTexCoord2f(0.f, 0.f); glVertex2f(-1.f, -1.f);
        glTexCoord2f(1.f, 0.f); glVertex2f( 1.f, -1.f);
        glTexCoord2f(1.f, 1.f); glVertex2f( 1.f,  1.f);
        glTexCoord2f(0.f, 1.f); glVertex2f(-1.f,  1.f);
        glEnd();
        glDepthFunc(GL_LESS);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

} // namespace
