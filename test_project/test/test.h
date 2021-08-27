#ifndef TEST_H
#define TEST_H

/* If defined, the following flags inhibit definition of the indicated items */
#define NOGDICAPMASKS // CC_, LC_, PC_, CP_, TC_, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES // WM_, EM_, LB_, CB_
#define NOWINSTYLES // WS_, CS_, ES_, LBS_, SBS_, CBS_
#define NOSYSMETRICS // SM_*
#define NOMENUS // MF_*
#define NOICONS // IDI_*
#define NOKEYSTATES // MK_*
#define NOSYSCOMMANDS // SC_*
#define NORASTEROPS // Binary and Tertiary raster ops
#define NOSHOWWINDOW // SW_*
#define OEMRESOURCE // OEM Resource values
#define NOATOM // Atom Manager routines
#define NOCLIPBOARD // Clipboard routines
#define NOCOLOR // Screen colors
#define NOCTLMGR // Control and Dialog routines
#define NODRAWTEXT // DrawText() and DT_*
#define NOGDI // All GDI defines and routines
#define NOKERNEL // All KERNEL defines and routines
#define NOUSER // All USER defines and routines
#define NONLS // All NLS defines and routines/
#define NOMB // MB_* and MessageBox()
#define NOMEMMGR // GMEM_, LMEM_, GHND, LHND, associated routines
#define NOMETAFILE // typedef METAFILEPICT
#define NOMINMAX // Macros min(a,b) and max(a,b)
#define NOMSG // typedef MSG and associated routines
#define NOOPENFILE // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL // SB_* and scrolling routines
#define NOSERVICE // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND // Sound driver routines
#define NOTEXTMETRIC // typedef TEXTMETRIC and associated routines
#define NOWH // SetWindowsHook and WH_*
#define NOWINOFFSETS // GWL_, GCL_, associated routines
#define NOCOMM // COMM driver routines
#define NOKANJI // Kanji support stuff.
#define NOHELP // Help engine interface.
#define NOPROFILER // Profiler interface.
#define NODEFERWINDOWPOS // DeferWindowPos routines
#define NOMCX // Modem Configuration Extensions

// #define CATCH_CONFIG_MAIN
// #include <catch.hpp>

#include <string.h>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "engine.h"

static Engine useLua(sol::state& lua)
{
  Engine e = Engine();
  e.initLua(lua);
  e.bind(lua);
  return e;
}

static void runLua(sol::state& l, const char* script, const char* file, int line)
{
  auto result = l.safe_script(script, sol::script_pass_on_error);
  if (!result.valid())
  {
    sol::error err = result;
    ADD_FAIL_AT(file, line, err.what());
  }
}

static void checkLua(sol::state& l, const char* assertion, const char* file, int line)
{
  auto result = l.safe_script("assert("+std::string(assertion)+R"())", sol::script_pass_on_error);
  if (!result.valid())
  {
    sol::error err = result;
    ADD_FAIL_AT(file, line, err.what());
  }
}

#define RUN_LUA(lua, s) runLua(lua, s, __FILE__, __LINE__)
#define CHECK_LUA(lua, assertion) checkLua(lua, assertion, __FILE__, __LINE__)

#endif