#include <proto/exec.h>
#include <proto/dos.h>
#include <mgl/minigl.h>
#include <utility/tagitem.h>
#include <cstddef>

#include "MiniGLIFacePatcher.h"

struct Library* MiniGLBase = NULL;
struct MiniGLIFace* IMiniGL = NULL;

int main()
{
	MiniGLBase = IExec->OpenLibrary("minigl.library", 0L);
	IMiniGL =(struct MiniGLIFace*)IExec->GetInterface(MiniGLBase, "main", 1, NULL);
	if (IMiniGL == NULL)
		return false;

	IExec->Forbid();
	PatchMiniGLIFace(IMiniGL);
	IExec->Permit();





	IDOS->Delay(60 * TICKS_PER_SECOND);

	IExec->Forbid();
	RestoreMiniGLIFace(IMiniGL);
	IExec->Permit();
}
