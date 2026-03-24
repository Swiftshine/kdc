#include <revolution/OS.h>
#include <runtime/GCN_mem_alloc.h>

//Note: OSGetArenaLo and OSGetArenaHi ARE merged with their OSGetMEM1 variants, hence the slight mismatches
inline static void InitDefaultHeap(void) {
	void* arenaLo;
	void* arenaHi;

	OSReport("GCN_Mem_Alloc.c : InitDefaultHeap. No Heap Available\n");
	OSReport("Metrowerks CW runtime library initializing default heap\n");

	arenaLo = OSGetArenaLo();
	arenaHi = OSGetArenaHi();

	arenaLo = OSInitAlloc(arenaLo, arenaHi, 1);
	OSSetArenaLo(arenaLo);

	arenaLo = (void*)OSRoundUp32B(arenaLo);
	arenaHi = (void*)OSRoundDown32B(arenaHi);

	OSSetCurrentHeap(OSCreateHeap(arenaLo, arenaHi));
	OSSetArenaLo(arenaLo = arenaHi);
}

DECL_WEAK void __sys_free(void* block) {
    if (__OSCurrHeap == -1) {
        InitDefaultHeap();
    }

    OSFreeToHeap(__OSCurrHeap, block);
}
