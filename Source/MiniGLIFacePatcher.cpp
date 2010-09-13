#include <cstddef>
#include <proto/exec.h>
#include <mgl/minigl.h>
#include "GLContextIFacePatcher.h"

typedef void*(*createContext_function)(struct MiniGLIFace*, struct TagItem*);
createContext_function originalCreateContext = NULL;

void* patchedCreateContext(struct MiniGLIFace* Self, struct TagItem* tagList)
{
	struct Task* task = IExec->FindTask(NULL);
	IExec->DebugPrintF("Task: 0x%08x created a context\n", task);
	struct GLContextIFace* the_context = static_cast<struct GLContextIFace*>(originalCreateContext(Self, tagList));
	PatchGLContextIFace(the_context);	
	return static_cast<void*>(the_context);
}

void PatchMiniGLIFace(struct MiniGLIFace* IMiniGL)
{
	originalCreateContext = reinterpret_cast<createContext_function>(IExec->SetMethod(reinterpret_cast<Interface*>(IMiniGL), offsetof(struct MiniGLIFace, CreateContext) , reinterpret_cast<APTR>(patchedCreateContext)));
}

void RestoreMiniGLIFace(struct MiniGLIFace* IMiniGL)
{
	// Restore the original interface
	IExec->SetMethod(reinterpret_cast<Interface*>(IMiniGL), offsetof(struct MiniGLIFace, CreateContext), reinterpret_cast<APTR>(originalCreateContext));
}
