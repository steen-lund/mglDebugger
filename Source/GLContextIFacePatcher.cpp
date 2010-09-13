#include <cstddef>
#include <proto/exec.h>
#include <mgl/minigl.h>

typedef void(*SwitchDisplay_function)(struct GLContextIFace *Self);
SwitchDisplay_function originalSwitchDisplayFunction = NULL;

void PatchedSwitchDisplay(struct GLContextIFace* self)
{
	IExec->DebugPrintF("Switch display called by: 0x%08x\n", IExec->FindTask(NULL));
	originalSwitchDisplayFunction(self);
}

void PatchGLContextIFace(struct GLContextIFace* IGLContext)
{
	originalSwitchDisplayFunction = reinterpret_cast<SwitchDisplay_function>(IExec->SetMethod(reinterpret_cast<Interface*>(IGLContext), offsetof(struct GLContextIFace, SwitchDisplay) , reinterpret_cast<APTR>(PatchedSwitchDisplay)));
}
