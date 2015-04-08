#include <python.h>
#include "todcore/kernel.h"
#include "todpython/todpythonscriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyMODINIT_FUNC inittodpython(void)
{
    BEGIN_MODULE(TodPython);
        ADD_TYPE(TodPython, TodPythonScriptServer);
    END_MODULE(TodPython);

    Kernel::instance()->create(S("TodPythonScriptServer"), S("/sys/svr/script"));
}
