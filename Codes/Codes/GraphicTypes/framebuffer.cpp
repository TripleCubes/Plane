#include <Codes/GraphicTypes/framebuffer.h>

#include <Codes/GraphicTypes/graphicTypesManager.h>
#include <glad/glad.h>

#include <Codes/Debug/print.h>

Framebuffer::Framebuffer() {}

void Framebuffer::init(int width, int height, int numberOfTextures, bool multisample) {
    dataPtr = std::make_shared<GraphicTypeData_Framebuffer>();
    dataPtr->init(width, height, numberOfTextures, multisample);
    GraphicTypesManager::addGraphicTypeData(dataPtr);
}

Framebuffer::~Framebuffer() {
    dataPtr->release();
    GraphicTypesManager::removeGraphicTypeData(dataPtr);
}

void Framebuffer::bind() const {
    dataPtr->bind();
}

unsigned int Framebuffer::getFBO() const {
    return dataPtr->getFBO();
}

unsigned int Framebuffer::getTextureId(int index) const {
    return dataPtr->getTextureId(index);
}



extern int currentWindowWidth;
extern int currentWindowHeight;

void GraphicTypeData_Framebuffer::init(int width, int height, int numberOfTextures, bool multisample) {
    if (initialized) {
        LINEINFORMATION();
        PRINTLN("Framebuffer already initialized");
        return;
    }

    framebufferWidth = width;
    framebufferHeight = height;
    this->numberOfTextures = numberOfTextures;
    
    if (numberOfTextures < 1) {
        LINEINFORMATION();
        PRINTLN("NumberOfTextures cant be less than 1");
        return;
    }

    if (framebufferWidth == 0) {
        framebufferWidth = currentWindowWidth;
    }
    if (framebufferHeight == 0) {
        framebufferHeight = currentWindowHeight;
    }

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    unsigned int attachments[numberOfTextures]; 
    textureIdList.resize(numberOfTextures, 0);
    for (int i = 0; i < numberOfTextures; i++) {
        glGenTextures(1, &textureIdList[i]);
        
        if (!multisample) {
            glBindTexture(GL_TEXTURE_2D, textureIdList[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, framebufferWidth, framebufferHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureIdList[i], 0); 
        } else {
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, textureIdList[i]);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA16F, framebufferWidth, framebufferHeight, GL_TRUE);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D_MULTISAMPLE, textureIdList[i], 0); 
        }

        attachments[i] = GL_COLOR_ATTACHMENT0 + i; 
    }
    if (!multisample) {
        glBindTexture(GL_TEXTURE_2D, 0);
    } else {
        glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
    }
    glDrawBuffers(numberOfTextures, attachments);



    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO); 

    if (!multisample) {
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, framebufferWidth, framebufferHeight); 
    } else {
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, framebufferWidth, framebufferHeight);
    }

    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        LINEINFORMATION();
        PRINTLN("Cant init frame buffer");
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    initialized = true;
}

void GraphicTypeData_Framebuffer::release() {
    if (released) {
        return;
    }

    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Cant release not initailized framebuffer");
        return;
    }

    for (unsigned int &textureId: textureIdList) {
        glDeleteTextures(1, &textureId);
    }
    glDeleteRenderbuffers(1, &RBO);
    glDeleteFramebuffers(1, &FBO);

    released = true;
}

void GraphicTypeData_Framebuffer::bind() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Framebuffer not initialized");
        return;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Framebuffer already released");
        return;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}

unsigned int GraphicTypeData_Framebuffer::getFBO() const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Framebuffer not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Framebuffer already released");
        return 0;
    }

    return FBO;
}

unsigned int GraphicTypeData_Framebuffer::getTextureId(int index) const {
    if (!initialized) {
        LINEINFORMATION();
        PRINTLN("Framebuffer not initialized");
        return 0;
    }

    if (released) {
        LINEINFORMATION();
        PRINTLN("Framebuffer already released");
        return 0;
    }

    if (index < 0 || (std::size_t)index >= textureIdList.size()) {
        LINEINFORMATION();
        PRINTLN("Invalid index");
        return 0;
    }

    return textureIdList[index];
}
