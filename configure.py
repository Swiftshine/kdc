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
    "-i src/MSL/MSL_C/",
    "-i src/MSL/MSL_C/internal/",
    "-i src/revolution/",
    "-i src/nw4r/",
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
            Object(NonMatching, "runtime/__init_cpp_exceptions.cpp"),
            # Object(NonMatching, "Runtime.PPCEABI.H/global_destructor_chain.c"),
            # Object(NonMatching, "Runtime.PPCEABI.H/__init_cpp_exceptions.cpp"),
        ],
    },
    {
        "lib": "revolution/OS",
        "mw_version": "Wii/1.0",
        "cflags": cflags_rvl,
        "progress_category": "sdk",
        "objects": [
            Object(Matching, "revolution/OS/OSAlarm.c"),
            Object(NonMatching, "revolution/OS/OSAlloc.c"),
            Object(NonMatching, "revolution/OS/OSStateTM.c"),
            Object(Matching, "revolution/OS/OSThread.c"),
            Object(NonMatching, "revolution/OS/OSTime.c"),
        ],
    },
    {
        "lib": "nw4r/g3d",
        "mw_version": config.linker_version,
        "cflags": cflags_nw4r,
        "progress_category": "sdk",
        "objects": [
            Object(NonMatching, "nw4r/g3d/g3d_basic.cpp"),
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
            Object(NonMatching, "donut/app/Locale.cpp"),
            Object(NonMatching, "donut/app/Message.cpp"),
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
