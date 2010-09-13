#include <cstddef>
#include <proto/exec.h>
#include <mgl/minigl.h>


#define DEFINE_PATCH_FUNCTION(TYPE, NAME, PARAMS) \
	typedef TYPE(*NAME)PARAMS; \
	NAME original##NAME = NULL;

#define PATCH_FUNCTION(FUNCTION, ORIGINAL_NAME, PATCHED_NAME) \
	original##FUNCTION = reinterpret_cast<FUNCTION>(IExec->SetMethod(reinterpret_cast<Interface*>(IGLContext), offsetof(struct GLContextIFace, ORIGINAL_NAME) , reinterpret_cast<APTR>(PATCHED_NAME)));

DEFINE_PATCH_FUNCTION(void, SwitchDisplay_function, (struct GLContextIFace *self))
DEFINE_PATCH_FUNCTION(void, GLAlphaFunc_function, (struct GLContextIFace *Self, GLenum func, GLclampf ref))
DEFINE_PATCH_FUNCTION(void, GLBegin_function, (struct GLContextIFace *Self, GLenum mode))
DEFINE_PATCH_FUNCTION(void, GLBindTexture_function, (struct GLContextIFace *Self, GLenum target, GLuint texture))
//typedef void(*GLBlendFunc_function)(struct GLContextIFace *Self, GLenum sfactor, GLenum dfactor);
//typedef void(*GLClear_function)(struct GLContextIFace *Self, GLbitfield mask);
//typedef void(*GLClearColor_function)(struct GLContextIFace *Self, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
//typedef void(*GLClearDepth_function)(struct GLContextIFace *Self, GLclampd depth);
//typedef void(*GLColor4f_function)(struct GLContextIFace *Self, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
//typedef void(*GLColorTable_function)(struct GLContextIFace *Self, GLenum target, GLenum internalformat, GLint width, GLenum format, GLenum type, const GLvoid* data);
//typedef void(*GLCullFace_function)(struct GLContextIFace *Self, GLenum mode);
//typedef void(*GLDeleteTextures_function)(struct GLContextIFace *Self, GLsizei n, const GLuint *textures);
//typedef void(*GLDepthFunc_function)(struct GLContextIFace *Self, GLenum func);
//typedef void(*GLDepthMask_function)(struct GLContextIFace *Self, GLboolean flag);
//typedef void(*GLDepthRange_function)(struct GLContextIFace *Self, GLclampd n, GLclampd f);
//typedef void(*GLDrawBuffer_function)(struct GLContextIFace *Self, GLenum mode);
//typedef void(*GLEnd_function)(struct GLContextIFace *Self);


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
	PATCH_FUNCTION(SwitchDisplay_function, SwitchDisplay, PatchedSwitchDisplay)
	PATCH_FUNCTION(GLBegin_function, GLBegin, PatchedGLBegin)
	//originalSwitchDisplay_function = reinterpret_cast<SwitchDisplay_function>(IExec->SetMethod(reinterpret_cast<Interface*>(IGLContext), offsetof(struct GLContextIFace, SwitchDisplay) , reinterpret_cast<APTR>(PatchedSwitchDisplay)));
}
