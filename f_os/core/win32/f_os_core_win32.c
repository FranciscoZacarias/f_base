#include <Windows.h>
#include <userenv.h>

//~ OS entry point
#if IS_COMMAND_LINE_PROGRAM
int main(int argc, char** argv) {
  entry_main_thread(entry_point, (u64)__argc, __argv);
  return 0;
}
#else
int WinMain(HINSTANCE instance, HINSTANCE prev_instance, LPSTR lp_cmd_line, int n_show_cmd) {
  entry_main_thread(entry_point, (u64)__argc, __argv);
  return 0;
}
#endif // IS_COMMAND_LINE_PROGRAM

//~ Init
internal void
os_init() {
  
}

//~ Window


//~ Memory
internal void*
os_memory_reserve(u64 size) {
  void* result = VirtualAlloc(0, size, MEM_RESERVE, PAGE_NOACCESS);
  return result;
}

internal b32
os_memory_commit(void* memory, u64 size) {
  b32 result = (VirtualAlloc(memory, size, MEM_COMMIT, PAGE_READWRITE) != 0);
  return result;
}

internal void
os_memory_decommit(void* memory, u64 size) {
  VirtualFree(memory, size, MEM_DECOMMIT);
}

internal void
os_memory_release(void* memory, u64 size) {
  VirtualFree(memory, 0, MEM_RELEASE);
}

internal u64
os_memory_get_page_size() {
  SYSTEM_INFO sysinfo = {0};
  GetSystemInfo(&sysinfo);
  return(sysinfo.dwPageSize);
}