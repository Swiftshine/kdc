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
    "-i libs/nrel/include",
    f"-i build/{config.version}/src",
    f"-DBUILD_VERSION={version_num}",
    f"-DVERSION_{config.version}",
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
        "progress_category": "sdk",  # str | List[str]
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
        "progress_category": "msl",  # str | List[str]
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
            # Object(NonMatching, "revolution/SC/scapi.c"),
            Object(NonMatching, "revolution/ARC/arc.c"),
        ],
    },
    {
        "lib": "nw4r/g3d",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "nw4r/g3d/dcc/g3d_basic.cpp"),
            Object(NonMatching, "nw4r/g3d/dcc/g3d_maya.cpp"),
            Object(Matching, "nw4r/g3d/g3d_camera.cpp"),
        ],
    },
    {
        "lib": "nw4r/lyt",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "nw4r/lyt/lyt_pane.cpp"),
            Object(NonMatching, "nw4r/lyt/lyt_group.cpp"),
        ],
    },
    {
        "lib": "hel/geo",
        "mw_version": config.linker_version,
        "cflags": cflags_hel,
        "progress_category": "hel",
        "objects": [
            Object(NonMatching, "hel/geo/Rect.cpp"),
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
        "lib": "donut",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Matching, "donut/Main.cpp"),
        ],
    },
    {
        "lib": "donut/app",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/app/AppImpl.cpp"),
            Object(Matching, "donut/app/Locale.cpp"),
            Object(Matching, "donut/app/Message.cpp"),
        ],
    },
    {
        "lib": "gfc",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/gfx/EasyRender3D.cpp", extra_cflags=["-O3,s"]),
            Object(Equivalent, "donut/gfx/FullScreenPlate.cpp"),
            Object(Matching, "donut/gfx/GameScreen.cpp"),
            Object(NonMatching, "donut/gfx/GXFifoMemoryManager.cpp"),
            Object(Equivalent, "donut/gfx/GXFifoProtectCanceler.cpp"),
            Object(Matching, "donut/gfx/TexBuffer.cpp"),
            Object(NonMatching, "donut/gfx/TPLTexture.cpp", extra_cflags=["-O3,s"]),
            Object(NonMatching, "donut/gfx/VISetting.cpp", extra_cflags=["-O3,s"]),

        ],
    },
    {
        "lib": "ocoll",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/ocoll/Gimmick.cpp", extra_cflags=["-O3,s"]),
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
        "lib": "scn/step/enemy",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/scn/step/enemy/Param.cpp"),
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
        "lib": "snd",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(NonMatching, "donut/snd/BgmPlayer.cpp"),
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

        ],
    },
    {
        "lib": "mem",
        "mw_version": config.linker_version,
        "cflags": cflags_donut,
        "progress_category": "donut",
        "objects": [
            Object(Matching, "donut/mem/MemBlock.cpp"),
            Object(Matching, "donut/mem/DataBlock.cpp"),
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
