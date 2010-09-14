#include <cstddef>
#include <proto/exec.h>
#include <mgl/minigl.h>


#define DEFINE_PATCH_FUNCTION(TYPE, NAME, PARAMS) \
	typedef TYPE(*NAME##_function)PARAMS; \
	NAME##_function original##NAME##_function = NULL;

#define PATCH_FUNCTION(FUNCTION) \
	original##FUNCTION##_function = reinterpret_cast<FUNCTION##_function>(IExec->SetMethod(reinterpret_cast<Interface*>(IGLContext), offsetof(struct GLContextIFace, FUNCTION) , reinterpret_cast<APTR>(Patched##FUNCTION)));

DEFINE_PATCH_FUNCTION(void, SwitchDisplay, (struct GLContextIFace *self))
DEFINE_PATCH_FUNCTION(void, GLAlphaFunc, (struct GLContextIFace *Self, GLenum func, GLclampf ref))
DEFINE_PATCH_FUNCTION(void, GLBegin, (struct GLContextIFace *Self, GLenum mode))
DEFINE_PATCH_FUNCTION(void, GLBindTexture, (struct GLContextIFace *Self, GLenum target, GLuint texture))
DEFINE_PATCH_FUNCTION(void, GLBlendFunc, (struct GLContextIFace *Self, GLenum sfactor, GLenum dfactor))
DEFINE_PATCH_FUNCTION(void, GLClear, (struct GLContextIFace *Self, GLbitfield mask))
DEFINE_PATCH_FUNCTION(void, GLClearColor, (struct GLContextIFace *Self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha))
DEFINE_PATCH_FUNCTION(void, GLClearDepth, (struct GLContextIFace *Self, GLclampd depth))
DEFINE_PATCH_FUNCTION(void, glColor4f, (struct GLContextIFace *Self, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha))
DEFINE_PATCH_FUNCTION(void, GLColorTable, (struct GLContextIFace *Self, GLenum target, GLenum internalformat, GLint width, GLenum format, GLenum type, const GLvoid* data))
DEFINE_PATCH_FUNCTION(void, GLCullFace, (struct GLContextIFace *Self, GLenum mode))
DEFINE_PATCH_FUNCTION(void, GLDeleteTextures, (struct GLContextIFace *Self, GLsizei n, const GLuint *textures))
DEFINE_PATCH_FUNCTION(void, GLDepthFunc, (struct GLContextIFace *Self, GLenum func))
DEFINE_PATCH_FUNCTION(void, GLDepthMask, (struct GLContextIFace *Self, GLboolean flag))
DEFINE_PATCH_FUNCTION(void, GLDepthRange, (struct GLContextIFace *Self, GLclampd n, GLclampd f))
DEFINE_PATCH_FUNCTION(void, GLDrawBuffer, (struct GLContextIFace *Self, GLenum mode))
DEFINE_PATCH_FUNCTION(void, GLEnd, (struct GLContextIFace *Self))


void PatchedSwitchDisplay(struct GLContextIFace* self)
{
	IExec->DebugPrintF("Switch display called by: 0x%08x\n", IExec->FindTask(NULL));
	originalSwitchDisplay_function(self);
}

void PatchedGLBegin(struct GLContextIFace* self, GLenum mode)
{
	IExec->DebugPrintF("glBegin called with mode: %d\n", mode);
	originalGLBegin_function(self, mode);
}

void PatchGLContextIFace(struct GLContextIFace* IGLContext)
{
	PATCH_FUNCTION(SwitchDisplay)
	PATCH_FUNCTION(GLBegin)
}
