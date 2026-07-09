#!/usr/bin/env python3

###
# Generates build files for the project.
# This file also includes the project configuration,
# such as compiler flags and the object matching status.
#
# Usage:
#   python3 configure.py
#   ninja
#
# Append --help to see available options.
###

import argparse
import sys
from pathlib import Path
from typing import Any, Dict, List

from tools.project import (
    Object,
    ProgressCategory,
    ProjectConfig,
    calculate_progress,
    generate_build,
    is_windows,
)

# Game versions
DEFAULT_VERSION = 0
VERSIONS = [
    "S72E01",  # 0
]

parser = argparse.ArgumentParser()
parser.add_argument(
    "mode",
    choices=["configure", "progress"],
    default="configure",
    help="script mode (default: configure)",
    nargs="?",
)
parser.add_argument(
    "-v",
    "--version",
    choices=VERSIONS,
    type=str.upper,
    default=VERSIONS[DEFAULT_VERSION],
    help="version to build",
)
parser.add_argument(
    "--build-dir",
    metavar="DIR",
    type=Path,
    default=Path("build"),
    help="base build directory (default: build)",
)
parser.add_argument(
    "--binutils",
    metavar="BINARY",
    type=Path,
    help="path to binutils (optional)",
)
parser.add_argument(
    "--compilers",
    metavar="DIR",
    type=Path,
    help="path to compilers (optional)",
)
parser.add_argument(
    "--map",
    action="store_true",
    help="generate map file(s)",
)
parser.add_argument(
    "--debug",
    action="store_true",
    help="build with debug info (non-matching)",
)
if not is_windows():
    parser.add_argument(
        "--wrapper",
        metavar="BINARY",
        type=Path,
        help="path to wibo or wine (optional)",
    )
parser.add_argument(
    "--dtk",
    metavar="BINARY | DIR",
    type=Path,
    help="path to decomp-toolkit binary or source (optional)",
)
parser.add_argument(
    "--objdiff",
    metavar="BINARY | DIR",
    type=Path,
    help="path to objdiff-cli binary or source (optional)",
)
parser.add_argument(
    "--sjiswrap",
    metavar="EXE",
    type=Path,
    help="path to sjiswrap.exe (optional)",
)
parser.add_argument(
    "--ninja", metavar="BINARY", type=Path, help="path to ninja binary (optional)"
)
parser.add_argument(
    "--verbose",
    action="store_true",
    help="print verbose output",
)
parser.add_argument(
    "--non-matching",
    dest="non_matching",
    action="store_true",
    help="builds equivalent (but non-matching) or modded objects",
)
parser.add_argument(
    "--warn",
    dest="warn",
    type=str,
    choices=["all", "off", "error"],
    help="how to handle warnings",
)
parser.add_argument(
    "--no-progress",
    dest="progress",
    action="store_false",
    help="disable progress calculation",
)
args = parser.parse_args()

config = ProjectConfig()
config.version = str(args.version)
version_num = VERSIONS.index(config.version)

# Apply arguments
config.build_dir = args.build_dir
config.dtk_path = args.dtk
config.objdiff_path = args.objdiff
config.binutils_path = args.binutils
config.compilers_path = args.compilers
config.generate_map = args.map
config.non_matching = args.non_matching
config.sjiswrap_path = args.sjiswrap
config.ninja_path = args.ninja
config.progress = args.progress
if not is_windows():
    config.wrapper = args.wrapper
# Don't build asm unless we're --non-matching
if not config.non_matching:
    config.asm_dir = None

# Tool versions
config.binutils_tag = "2.42-1"
config.compilers_tag = "20250812"
config.dtk_tag = "v1.8.2"
config.objdiff_tag = "v3.0.0-beta.14"
config.sjiswrap_tag = "v1.2.1"
config.wibo_tag = "1.0.3"

# Project
config.config_path = Path("config") / config.version / "config.yml"
config.check_sha_path = Path("config") / config.version / "build.sha1"
config.asflags = [
    "-mgekko",
    "--strip-local-absolute",
    "-I include",
    f"-I build/{config.version}/include",
    f"--defsym BUILD_VERSION={version_num}",
]
config.ldflags = [
    "-fp hardware",
    "-nodefaults",
    "-code_merging all",
    "-map",
]
if args.debug:
    config.ldflags.append("-g")  # Or -gdwarf-2 for Wii linkers
if args.map:
    config.ldflags.append("-mapunused")
    # config.ldflags.append("-listclosure") # For Wii linkers

# Use for any additional files that should cause a re-configure when modified
config.reconfig_deps = []

# Optional numeric ID for decomp.me preset
# Can be overridden in libraries or objects
config.scratch_preset_id = None

# Base flags, common to most GC/Wii games.
# Generally leave untouched, with overrides added below.
cflags_base = [
    "-nodefaults",
    "-proc gekko",
    "-align powerpc",
    "-enum int",
    "-fp hardware",
    "-Cpp_exceptions off",
    # "-W all",
    # "-O4,p",
    "-inline auto",
    '-pragma "cats off"',
    '-pragma "warn_notinlined off"',
    "-maxerrors 1",
    "-nosyspath",
    "-RTTI off",
    "-fp_contract on",
    "-str reuse",
    # "-multibyte",  # For Wii compilers, replace with `-enc SJIS`
    "-enc SJIS",
    "-i src/",
    "-i libs/",
    "-i libs/MSL/MSL_C/",
    "-i libs/MSL/MSL_C/MSL_Common/Include",
    "-i libs/MSL/MSL_C/MSL_Common_Embedded/Include/",
    "-i libs/MSL/MSL_C++/MSL_Common/Include",
    "-i libs/MSL/MSL_C/PPC_EABI/Include",
    "-i src/revolution/",
    "-i src/nw4r/",
    "-i src/nw4r/ef/drawstrategy",
    "-i libs/libms/include",
    "-i libs/nrel/include",
    "-i src/revolution/BTE/include/",
    "-i src/revolution/BTE/stack/include/",
    "-i src/revolution/BTE/stack/btm/",
    "-i src/revolution/BTE/bta/include/",
    "-i src/revolution/BTE/bta/sys/",
    "-i src/revolution/BTE/gki/common/",
    "-i src/revolution/BTE/gki/platform/",
    f"-i build/{config.version}/src",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
    "-DREVOLUTION",
]

# Debug flags
if args.debug:
    # Or -sym dwarf-2 for Wii compilers
    cflags_base.extend(["-sym on", "-DDEBUG=1"])
else:
    cflags_base.append("-DNDEBUG=1")

# Warning flags
if args.warn == "all":
    cflags_base.append("-W all")
elif args.warn == "off":
    cflags_base.append("-W off")
elif args.warn == "error":
    cflags_base.append("-W error")

# Metrowerks library flags
cflags_runtime = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
    "-O4,s"
]

cflags_msl = [
    *cflags_base,
    "-use_lmw_stmw on",
    "-str reuse,pool,readonly",
    "-gccinc",
    "-common off",
    "-inline auto",
    "-O4,s"
]

# REL flags
cflags_rel = [
    *cflags_base,
    "-sdata 0",
    "-sdata2 0",
]

cflags_rvl = [
    *cflags_base,
    "-O4,p",
    "-func_align 16",
    "-lang=c99",
    "-enc SJIS",
    "-fp_contract off",
    "-ipa file",
]

cflags_nw4r = [
    *cflags_base,
    "-inline on",
    "-fp_contract off",
    "-O4,p",
    "-func_align 16",
    "-ipa file",
]

cflags_hel = [*cflags_base, "-i src/hel/", "-inline noauto", "-O3", "-func_align 4"]

cflags_donut = [
    *cflags_base,
    "-i src/donut/",
    "-inline noauto",
    "-enc SJIS",
    "-O3",
    "-func_align 4",
    "-DNW4R_ASSERT",
]


config.linker_version = "Wii/1.3"


# Helper function for Dolphin libraries
def DolphinLib(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.2.5n",
        "cflags": cflags_base,
        "progress_category": "sdk",
        "objects": objects,
    }


# Helper function for REL script objects
def Rel(lib_name: str, objects: List[Object]) -> Dict[str, Any]:
    return {
        "lib": lib_name,
        "mw_version": "GC/1.3.2",
        "cflags": cflags_rel,
        "progress_category": "game",
        "objects": objects,
    }


Matching = True  # Object matches and should be linked
NonMatching = False  # Object does not match and should not be linked
Equivalent = (
    config.non_matching
)  # Object should be linked when configured with --non-matching


# Object is only matching for specific versions
def MatchingFor(*versions):
    return config.version in versions


config.warn_missing_config = True
config.warn_missing_source = False
config.libs = [
    {
        "lib": "Runtime.PPCEABI.H",
        "mw_version": config.linker_version,
        "cflags": cflags_runtime,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "runtime/ptmf.c"),
            Object(NonMatching, "runtime/runtime.c"),
            Object(NonMatching, "runtime/__init_cpp_exceptions.cpp"),
            Object(NonMatching, "runtime/__mem.c"),
            Object(NonMatching, "runtime/global_destructor_chain.c"),
            Object(NonMatching, "runtime/GCN_mem_alloc.c", extra_cflags=["-O4,p"]),
            Object(NonMatching, "runtime/Gecko_ExceptionPPC.cpp", extra_cflags=["-RTTI on"]),
            Object(NonMatching, "runtime/New.cpp", extra_cflags=["-RTTI on"]),
            Object(NonMatching, "runtime/NMWException.cpp", extra_cflags=["-O4,p"]),
        ],
    },
    {
        "lib": "MSL_C.PPCEABI.bare",
        "src_dir": "libs/",
        "mw_version": config.linker_version,
        "cflags": cflags_msl,
        "progress_category": "msl",
        "objects": [
            Object(Matching, "MSL/MSL_C/MSL_Common/Src/float.c"),
            Object(NonMatching, "MSL/MSL_C/PPC_EABI/SRC/abort_exit_ppc_eabi.c"),
            Object(Matching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_acos.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_asin.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_atan2.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_fmod.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_log.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_log10.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_pow.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_rem_pio2.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_cos.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_rem_pio2.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_sin.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/k_tan.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_atan.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ceil.c", extra_cflags=["-fp_contract off"]),
            Object(Matching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_copysign.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_cos.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_floor.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_frexp.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_ldexp.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_modf.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_sin.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/s_tan.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_acos.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_asin.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_atan2.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_fmod.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_log10.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_pow.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/e_sqrt.c", extra_cflags=["-fp_contract off"]),
            Object(NonMatching, "MSL/MSL_C/MSL_Common_Embedded/Math/Double_precision/w_sqrt.c", extra_cflags=["-fp_contract off"]),

        ],
    },
    {
        "lib": "revolution/OS",
        "mw_version": "Wii/1.0",
        "cflags": cflags_rvl,
        "progress_category": "sdk",
        "objects": [
            # Object(NonMatching, "revolution/OS/OS.c"),
            Object(Matching, "revolution/OS/OSAlarm.c"),
            Object(Matching, "revolution/OS/OSAlloc.c"),
            Object(NonMatching, "revolution/OS/OSStateTM.c"),
            Object(Matching, "revolution/OS/OSThread.c"),
            Object(NonMatching, "revolution/OS/OSTime.c"),
            Object(Matching, "revolution/BASE/PPCArch.c"),
            Object(Matching, "revolution/DB/db.c"),
            Object(NonMatching, "revolution/VI/vi.c"),
            Object(Matching, "revolution/AI/ai.c"),
            Object(Matching, "revolution/AX/AX.c"),
            Object(Matching, "revolution/AX/AXAlloc.c"),
            Object(Matching, "revolution/AX/AXAux.c"),
            Object(Matching, "revolution/AX/AXCL.c"),
            Object(Matching, "revolution/AX/AXOut.c"),
            Object(Matching, "revolution/AX/AXSPB.c"),
            Object(Matching, "revolution/AX/AXVPB.c"),
            Object(Matching, "revolution/AX/AXComp.c"),
            Object(Matching, "revolution/AX/DSPCode.c"),
            Object(Matching, "revolution/AX/AXProf.c"),
            Object(Matching, "revolution/AXFX/AXFXReverbHi.c"),
            Object(NonMatching, "revolution/AXFX/AXFXReverbHiExp.c"),
            Object(Matching, "revolution/AXFX/AXFXHooks.c"),
            Object(Matching, "revolution/CX/CXUncompression.c"),
            Object(NonMatching, "revolution/CX/CXSecureUncompression.c"),
            Object(NonMatching, "revolution/DSP/dsp.c"),
            Object(Matching, "revolution/DSP/dsp_debug.c"),
            Object(NonMatching, "revolution/DSP/dsp_task.c"),
            Object(NonMatching, "revolution/NAND/nand.c"),
            Object(Matching, "revolution/NAND/NANDOpenClose.c"),
            Object(NonMatching, "revolution/NAND/NANDCore.c"),
            Object(Equivalent, "revolution/SC/scapi.c"),
            Object(NonMatching, "revolution/ARC/arc.c"),
            Object(Matching, "revolution/MEM/mem_list.c"),
        ],
    },
    {
        "lib": "nw4r/ef",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "nw4r/ef/ef_effectsystem.cpp"),
            Object(NonMatching, "nw4r/ef/ef_emitter.cpp", extra_cflags=["-sym on"]),
        ],
    },
    {
        "lib": "nw4r/g3d",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "nw4r/g3d/res/g3d_resfile.cpp"),
            Object(Matching, "nw4r/g3d/res/g3d_resmat.cpp"),
            Object(NonMatching, "nw4r/g3d/g3d_state.cpp"),
            Object(Matching, "nw4r/g3d/dcc/g3d_basic.cpp"),
            Object(Matching, "nw4r/g3d/dcc/g3d_maya.cpp"),
            Object(Matching, "nw4r/g3d/g3d_camera.cpp"),
            Object(Matching, "nw4r/g3d/g3d_fog.cpp"),
        ],
    },
    {
        "lib": "nw4r/lyt",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "nw4r/lyt/lyt_pane.cpp"),
            Object(Matching, "nw4r/lyt/lyt_group.cpp"),
        ],
    },
    {
        "lib": "nw4r/ut",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "nw4r/ut/ut_list.cpp"),
        ],
    },
    {
        "lib": "donut",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Matching, "donut/Main.cpp"),
            Object(NonMatching, "donut/TPL.cpp"),
        ],
    },
    {
        "lib": "app",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/app/AddOnMint.cpp"),
            Object(NonMatching, "donut/app/AlertMint.cpp"),
            Object(NonMatching, "donut/app/AppImpl.cpp"),
            Object(NonMatching, "donut/app/Application.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/AutoResetTimer.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/BackupFileAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/DvdWatch.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/DvdWatch_ENG.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/EntryPoint.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/HIDErrorMenu.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/app/Locale.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/app/Message.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/NANDErrorMenu.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/PerformanceController.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/Random.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/Reset.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/ResidentFile.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/app/RomFontWrapper.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/SaveInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/app/System.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "dynamics",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/dynamics/Dynamics.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/dynamics/ModelNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/dynamics/ModelTree.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/dynamics/Util.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "effect",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/effect/Group.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/Requestor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/StdRequestor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/CameraInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/DrawInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/Effect.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/EffectComponent.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/EffectManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/EffectObjListUtil.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/G3DAutoReqAnimCallback.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/GenContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/GenContextTable.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/ManagerContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PolyEffect.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PolyEffectAllocator.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PolyEffectManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PolyEffectMemManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PolyEffectRes.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PtclEffect.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PtclEffectManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PtclEffectMemManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/PtclEffectRes.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/RequestArg.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/effect/detail/RequestArgOption.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "fdg",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/fdg/CallBackObj.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/fdg/FDGAccessor.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "file",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/file/DNOption.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/file/FDGManager.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/file/FileAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/file/FileClearDisableScope.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/file/FileLoader.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/file/FileManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/file/FileTree.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/file/Utility.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "font",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Equivalent, "donut/font/Font.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/font/FontKindUtil.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/font/FontLoader.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/font/FontManager.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "freeze",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/freeze/Console.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/Exception.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/FreezeHandler.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/FreezeManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/FreezeThread.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/MapFile.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/Message.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/NW4RAssert.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/freeze/XFBRestore.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "g3d",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/g3d/AddOnMint.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/AutoReqAnim.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/AutoReqAnimReqInfo.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/CameraAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/CharaAnimBlender.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/CharaAnimInterpolation.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/CharaAnimInterpolationContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/CharaModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/CharaModelContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ColorAnim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ColorAnimContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ColorAnimFlash.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ColorAnimMaterialTarget.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ColorAnimTevManager.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/FogAccessor.cpp"),
            Object(NonMatching, "donut/g3d/Group.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/LightSetAccessor.cpp"),
            Object(NonMatching, "donut/g3d/MaterialAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/MintModelAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/MintNodeAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/Model.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ModelAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ModelAnim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ModelAnimAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/ModelAnimContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ModelBufferOption.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ModelContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ModelMultiAnim.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/ModelMultiAnimContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/NodeAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/NodeLocalMtx.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/g3d/NodeLocalMtxAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ResAnmAutoReq.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ResFile.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ResFileAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ResFileRepository.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/g3d/ResModel.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/ResModelContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/ResNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/Root.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/g3d/RootContext.cpp"),
            Object(NonMatching, "donut/g3d/SceneAnim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/SceneAnimContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/StdModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/g3d/StdModelContext.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "gfx",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/gfx/EasyRender3D.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/EasyTex3D.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/EFBToLetterBox.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/gfx/FullScreenPlate.cpp"),
            Object(Matching, "donut/gfx/GameScreen.cpp"),
            Object(NonMatching, "donut/gfx/GXFifoMemoryManager.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/gfx/GXFifoProtectCanceler.cpp"),
            Object(NonMatching, "donut/gfx/RenderSetting.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/gfx/TexBuffer.cpp"),
            Object(NonMatching, "donut/gfx/TPLTexture.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/TPLTexturePlate.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/Utility.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/VISetting.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/XFBManager.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "gobj",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/gobj/AddOnMint.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/AnimScript.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/Anim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/ColorAnim.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/gobj/FootState.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/G3DAnimData.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/G3DAnimDataRepos.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/GearAnim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/GearModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/GearModelDesc.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/IG3DModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/IScriptCallback.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/Location.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/LocationDesc.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MeshFlip.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintAnim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintFootState.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintGearAnim.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintLocation.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintMeshFlip.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintMove.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintScript.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MintTarget.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/Model.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/ModelDesc.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/Move.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MoveParamAccel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MoveParamDecel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/MoveParamFall.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/NodeRepos.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/Script.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/Target.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gobj/TargetDesc.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "hbm",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/hbm/DisableIcon.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hbm/HomeButtonMenu.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hbm/Resource.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hbm/ResourceFileName.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "hel/common",
        "mw_version": config.linker_version,
        "cflags": cflags_hel,
        "progress_category": "hel",
        "objects": [
            Object(Matching, "hel/common/Array.cpp"),
            Object(NonMatching, "hel/common/Color.cpp"),
            Object(NonMatching, "hel/common/FixedString.cpp"),
            Object(NonMatching, "hel/common/Locale.cpp"),
            Object(NonMatching, "hel/common/ScopedPtr.cpp"),
            Object(NonMatching, "hel/common/Assert.cpp"),
            Object(NonMatching, "hel/common/Print.cpp"),
        ],
    },
    {
        "lib": "hel/math",
        "mw_version": config.linker_version,
        "cflags": cflags_hel,
        "progress_category": "hel",
        "objects": [
            Object(NonMatching, "hel/math/Direction3.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "hel/math/Matrix34.cpp"),
            Object(NonMatching, "hel/math/Matrix44.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "hel/math/Point2.cpp"),
            Object(Matching, "hel/math/Random.cpp"),
            Object(NonMatching, "hel/math/Vector2.cpp"),
            Object(NonMatching, "hel/math/Vector3.cpp"),
        ],
    },
    {
        "lib": "hel/geo",
        "mw_version": config.linker_version,
        "cflags": cflags_hel,
        "progress_category": "hel",
        "objects": [
            Object(NonMatching, "hel/geo/AABBox.cpp"),
            Object(Equivalent, "hel/geo/Rect.cpp"),
            Object(NonMatching, "hel/geo/Closest.cpp"),
            Object(NonMatching, "hel/geo/Intersection.cpp"),
        ],
    },
    {
        "lib": "hel/mint",
        "mw_version": config.linker_version,
        "cflags": cflags_hel,
        "progress_category": "hel",
        "objects": [
            Object(NonMatching, "hel/mint/AddOnCast.cpp"),
            Object(NonMatching, "hel/mint/AddOnMathDirection3.cpp"),
            Object(NonMatching, "hel/mint/AddOnMathMath.cpp"),
            Object(NonMatching, "hel/mint/AddOnMathVector3.cpp"),
        ],
    },
    {
        "lib": "hid",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Matching, "donut/hid/Accel.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/hid/Button.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/hid/DPD.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/HIDAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/HIDManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/LibInitializer.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/RumbleManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/RumbleRequestor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/RumbleResource.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/SimpleGCHID.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/hid/SimpleWRHID.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/hid/Stick.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "info",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/info/Util.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/sequence/Sequence.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/AddWiiRemote.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/Button.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/ButtonHelp.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/CheckWindow.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/Confirm.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/LowBattery.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/SkipHelp.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/TotalScore.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/common/WiiButton.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/cutin/CutIn.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/cutin/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/ticker/Ticker.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/info/ticker/TickerContext.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "lyt",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/lyt/AllocatorChanger.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/Layout.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/LayoutContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/MaterialAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/PaneAccessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/SystemTagProcessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/TagProcessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/TagUtil.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/UserTagProcessor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/lyt/Utility.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "mcoll",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/mcoll/Actor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/LandManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/ActorDiamond.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/ActorInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollidedAction.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollidedDetectionInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollidedInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollidedLog.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollideTarget.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollideTargetRepos.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/CollideTargetReposSet.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/DetectArg.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/DetectResult.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/DetectResultContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/FixedGridManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/IActor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/IResponder.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LadderInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LandAttribute.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LandGatherOption.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LandGrid.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LandLayer.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LandProperty.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/LandSet.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/MoveGrid.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/MoveGridGroup.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/MoveGridGroupId.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/MoveGridManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/RayChecker.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/ShapeDiamondContext.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mcoll/detail/StdResponder.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "mem",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Matching, "donut/mem/AllocatorHandle.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/mem/AutoHeapExp.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/mem/DataBlock.cpp"),
            Object(NonMatching, "donut/mem/ExplicitScopedPtr.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/mem/GlobalNewDeleteChanger.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapCompaction.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/mem/HeapCompactionNodeHandle.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapCompactionNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapExp.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapExpArray.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapExpArrayUser.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapMapUserRepos.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/HeapUnit.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/IAllocator.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/IHeap.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/mem/MemBlock.cpp"),
            Object(NonMatching, "donut/mem/Memory.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/mem/OperatorNewDelete.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/SDKAllocator.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/UnitHeapMapUser.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mem/Utility.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "mint",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/mint/Engine.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mint/Heap.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mint/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mint/Runner.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mint/ScriptArchive.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "mintglue",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/mintglue/App__Alert.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/App__Random.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/HEL__Math__Vector2.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/HEL__Math__Vector3.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/Scn__ChallengeTitle__Chara.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/Scn__ChallengeTitle__Commander.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/Scn__GrandTitle__Block.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/Scn__GrandTitle__Chara.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintglue/Scn__GrandTitle__Commander.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "mintvm",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/mintvm/BCModule.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/BCOpCode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/MintSetting.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/MintSystemCall.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/N_Mint_Cast.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/N_Mint_Debug.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/Regset.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/Runner.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMCore.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMFunction.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMFunctionList.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMModule.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMObjectType.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMObjectTypeList.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMSymbolTable.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMVariable.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mintvm/VMVariableList.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "mov",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/mov/DvdControl.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mov/MovieAudio.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mov/MovieCommand.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mov/MovieKindUtil.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mov/MoviePlayer.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mov/MovieThread.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/mov/MovieYuv.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "msg",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/msg/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/msg/Message.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/msg/Project.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "nand",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/nand/NandManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/nand/NandThread.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "nururi",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/nururi/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/nururi/Nururi.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "ocoll",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/ocoll/Attack.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/AttackCenter.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/AttackLog.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/AttackNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/AttackResult.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/AttackResultGimmick.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/AttackRoot.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/CollDataTable.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/Gimmick.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/Hit.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/HitNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/HitResult.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/NodeDesc.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/Owner.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/SearchAttack.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/SearchAttackNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/SearchAttackResult.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/SearchHit.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/SearchHitNode.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/SearchHitResult.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ocoll/Shape.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "ostop",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/ostop/Actor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ostop/IActorEventReceiver.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ostop/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/ostop/ReqHandle.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "param",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/param/JITParam.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/param/ParamAccessor.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "pause",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/pause/ButtonPanel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/ClosePanel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/Component.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/Constant.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/ContextInit.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/ContextOpen.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/CursorPanel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/FramePanel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/HID.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/ICallback.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/IPage.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/ManualData.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/PageAbility.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/PageCommand.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/PageDropout.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/PageManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/Pause.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/PlayerEntryInfo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/ResultSetter.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/pause/WindowPanel.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "preload",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/preload/PreLoadManager.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "scn",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/scn/DrawReqInfo.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "scn/step",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/scn/step/Component.cpp"),
            Object(NonMatching, "donut/scn/step/GridPos.cpp"),
        ],
    },
    {
        "lib": "scn/step/block",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/scn/step/block/BlockInfo.cpp"),
        ],
    },
    {
        "lib": "scn/step/boss",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Equivalent, "donut/scn/step/boss/IState.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "scn/step/enemy",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/scn/step/enemy/CustomBase.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/scn/step/enemy/Desc.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/scn/step/enemy/IState.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/scn/step/enemy/Param.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/scn/step/enemy/StateBase.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/scn/step/enemy/damage/StateDeadInWater.cpp", extra_cflags=["-O3,s"]),

            Object(Equivalent, "donut/scn/step/enemy/waddledoo/Custom.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/scn/step/enemy/waddledoo/ModelDesc.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "scn/step/hero",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(
                NonMatching,
                "donut/scn/step/hero/IndiviUtil.cpp",
                extra_cflags=["-O3"],
            ),
        ],
    },
    {
        "lib": "scn/vc",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Matching, "donut/scn/vc/Loader.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/scn/vc/Main.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/scn/vc/SceneVC.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "seq",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/seq/ContextStory.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/ISequence.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceChallengeRoot.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceChallengeTitle.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceFirstDemo.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceGrandMenu.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceHistory.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceLvMapRoot.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceProductRoot.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceRoot.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceStack.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceStaffCredit.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceStep.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/seq/SequenceVC.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "sfx",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/sfx/CinemaScopeModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/Fade.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/FullScreenModel.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/Manager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/Monotone.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/ScreenRemap.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/Utility.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/Warp.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/sfx/Wipe.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "snd",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/snd/AddOnMint.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/BgmPlayer.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/MintSERequestor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/SERequestor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/SoundManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/SoundSystem.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/SystemSERequestor.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/snd/WaveHandle.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "storage",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/storage/BackupData.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/BackupFileData2.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/GhostData.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/GhostFileData.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/StorageData.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/StorageManager.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/StorageUtil.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/storage/VolatileData2.cpp", extra_cflags=["-O3,s"]),
        ],
    },
    {
        "lib": "util",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/util/Alarm.cpp"),
            Object(Equivalent, "donut/util/AnimController.cpp"),
            Object(NonMatching, "donut/util/CharacterEncodeUtil.cpp", extra_cflags=["-O3,s"]),
            Object(Matching, "donut/util/CurveUtility.cpp"),
            Object(Equivalent, "donut/util/FrameCounter.cpp"),
            Object(Matching, "donut/util/Mutex.cpp"),
            Object(NonMatching, "donut/util/Thread.cpp"),
            Object(Equivalent, "donut/util/IState.cpp"),
            Object(Equivalent, "donut/util/IStateCallback.cpp"),
            Object(Equivalent, "donut/util/IStateChanger.cpp"),
            Object(NonMatching, "donut/util/StateChanger.cpp"),
            Object(NonMatching, "donut/util/UIntAABBox.cpp"),
        ],
    },
]


# Optional callback to adjust link order. This can be used to add, remove, or reorder objects.
# This is called once per module, with the module ID and the current link order.
#
# For example, this adds "dummy.c" to the end of the DOL link order if configured with --non-matching.
# "dummy.c" *must* be configured as a Matching (or Equivalent) object in order to be linked.
def link_order_callback(module_id: int, objects: List[str]) -> List[str]:
    # Don't modify the link order for matching builds
    if not config.non_matching:
        return objects
    if module_id == 0:  # DOL
        return objects + ["dummy.c"]
    return objects


# Uncomment to enable the link order callback.
# config.link_order_callback = link_order_callback


# Optional extra categories for progress tracking
# Adjust as desired for your project
config.progress_categories = [
    ProgressCategory("donut", "Game Code"),
    ProgressCategory("hel", "HAL Library Code"),
    ProgressCategory("sdk", "SDK Code"),
    ProgressCategory("msl", "MSL Code"),
]
config.progress_each_module = args.verbose
# Optional extra arguments to `objdiff-cli report generate`
config.progress_report_args = [
    # Marks relocations as mismatching if the target value is different
    # Default is "functionRelocDiffs=none", which is most lenient
    # "--config functionRelocDiffs=data_value",
]

if args.mode == "configure":
    # Write build.ninja and objdiff.json
    generate_build(config)
elif args.mode == "progress":
    # Print progress information
    calculate_progress(config)
else:
    sys.exit("Unknown mode: " + args.mode)
