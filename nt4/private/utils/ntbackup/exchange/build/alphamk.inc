!IF 0

Copyright (c) 1994  Microsoft Corporation

Module Name:

    alphamk.inc

Abstract:

        This module contains the ALPHA specific build controls.  It is included
        by makefile.def.

Author:

    Jeff Havens (jhavens) 13-Feb-1994

Revision History:

!ENDIF

#
# Alpha option control
#

UMBASE=$(UMBASE:*=alpha)
UMLIBS=$(UMLIBS:*=alpha)
NTRES=$(NTRES:*=alpha)
UMRES=$(UMRES:*=alpha)
UMOBJS=$(UMOBJS:*=alpha)
LINKLIBS=$(LINKLIBS:*=alpha)
DLLBASE=$(DLLBASE:*=alpha)
DLLDEF=$(DLLDEF:*=alpha)
MACHINE_TARGETLIBS=$(MACHINE_TARGETLIBS:*=alpha)
TARGET=$(TARGET:*=alpha)
DYNLINK_LIB=$(DYNLINK_LIB:*=alpha)
TARGETEXEFILES=$(TARGETEXEFILES:*=alpha)
TARGETLIBFILES=$(TARGETLIBFILES:*=alpha)
TARGETOBJFILES=$(TARGETOBJFILES:*=alpha)
UMOBJFILES=$(UMOBJFILES:*=alpha)
UMEXEFILES=$(UMEXEFILES:*=alpha)
HEADERFILE=$(HEADERFILE:*=alpha)
HEADEROBJNAME=$(HEADEROBJNAME:*=alpha)
HEADEROBJ=$(HEADEROBJ:*=alpha)
PRECOMPILED=$(PRECOMPILED:*=alpha)
PRECOMPILED_CXX=$(PRECOMPILED_CXX:*=alpha)
PRECOMPILED_TARGET=$(PRECOMPILED_TARGET:*=alpha)

!ifdef NTTARGETFILES
NTTARGETFILES=$(NTTARGETFILES:*=alpha)
!endif
!ifdef NTTARGETFILE0
NTTARGETFILE0=$(NTTARGETFILE0:*=alpha)
!endif
!ifdef NTTARGETFILE1
NTTARGETFILE1=$(NTTARGETFILE1:*=alpha)
!endif

!IF "$(GPSIZE)" != "0"

LIBC_LIB=$(BASEDIR)\public\sdk\lib\alpha\small.lib $(LIBC_LIB)
LINKGPSIZE=-gpsize:$(GPSIZE)

!ENDIF

ENTRY_SUFFIX=
GDI_ENTRY_SUFFIX=

!IF "$(MSC_OPTFLAGS)" == "/Oxs"
DBGFLAGS=$(MSC_OPTFLAGS:/Oxs=/Ox)
!ENDIF

!IFDEF ALPHA_WARNING_LEVEL
MSC_WARNING_LEVEL=$(ALPHA_WARNING_LEVEL)
!ENDIF

!IFDEF ALPHA_OPTIMIZATION
MSC_OPTIMIZATION=$(ALPHA_OPTIMIZATION)
!ENDIF

!IFDEF ALPHA_CPPFLAGS
MSC_CPPFLAGS=$(ALPHA_CPPFLAGS)
!ENDIF

ALPHA_AS=asaxp -nologo

ALPHA_START_FILE=start.obj

# Use /Z7 instead of /Zi

DBGFLAGS=$(DBGFLAGS:/Zi=/Z7)

ENV_DEFINES=$(LIBC_DEFINES) $(C_DEFINES) $(NET_C_DEFINES) $(MSC_CPPFLAGS) $(NTCPPFLAGS)
STD_DEFINES=-DALPHA=1 -D_ALPHA_=1 -DNO_EXT_KEYS -DCONDITION_HANDLING=1 $(STD_DEFINES)

STDFLAGS= /c /Zel /Zp8 /Gy $(MSC_WARNING_LEVEL) $(MFC_FLAGS)

CDEFINES=$(STD_DEFINES) $(TARGET_DBG_DEFINES) $(ENV_DEFINES)
CFLAGS=$(ALPHA_FLAGS) $(NTALPHAFLAGS) $(STDFLAGS) $(DBGFLAGS) $(ALPHA_PERFFLAGS) \
       -D__stdcall= -D__cdecl=

ALPHA_CDEFINES=$(CDEFINES)
ALPHA_CFLAGS=$(CFLAGS)

!IFNDEF _AXPACC_
_AXPACC_=0
!ENDIF

ALPHA_CC = cl $(CBSTRING) -nologo -d2"switch no*check*" $(USER_C_FLAGS)

C_COMPILER_NAME = $(ALPHA_CC)
CXX_COMPILER_NAME = $(ALPHA_CC)
C_PREPROCESSOR_NAME = $(ALPHA_CC)

GLOBAL_C_FLAGS = -Ialpha\ -I. $(INCPATH0) $(CDEFINES) \
                $(ALPHA_OPTIONS) $(CFLAGS) \
                /Gt$(GPSIZE) -DFPO=1

C_COMPILER_FLAGS = $(GLOBAL_C_FLAGS) $(PRECOMPILED) $(COMPILER_WARNINGS)
CXX_COMPILER_FLAGS = $(GLOBAL_C_FLAGS) $(PRECOMPILED_CXX) $(COMPILER_WARNINGS)
C_PREPROCESSOR_FLAGS = $(GLOBAL_C_FLAGS) -EP -Tc

C_COMPILER= $(C_COMPILER_NAME) $(C_COMPILER_FLAGS)
CXX_COMPILER=$(CXX_COMPILER_NAME) $(CXX_COMPILER_FLAGS)
C_PREPROCESSOR = $(C_PREPROCESSOR_NAME) $(C_PREPROCESSOR_FLAGS)

ALPHA_ASSEMBLER=$(ALPHA_AS) -O1 -Ialpha\ -I. $(INCPATH0) $(CDEFINES) \
                    $(ALPHA_FLAGS) $(NTALPHAFLAGS) $(ADBGFLAGS) \
                    -D_LANGUAGE_ASSEMBLY

ECHO_MSG=ClAlpha $<            " $(C_COMPILER) "
ECHO_PRECOMPILED_MSG=CpAlpha $(PRECOMPILED_INCLUDE) " $(C_COMPILER) /Yl$(TARGETNAME) /Yc$(?F) $(HEADERFILE) $(HEADEROBJ) $(PRECOMPILED_FLAG)"

{..\alpha\}.s{obj\alpha\}.obj:
    @-erase $@ >nul 2>&1
    @echo AsAlpha $<            " $(ALPHA_ASSEMBLER) "
    @$(ALPHA_ASSEMBLER) -o $@ $(MAKEDIR)\..\alpha\$(<F)

{alpha\}.s{obj\alpha\}.obj:
    @-erase $@ >nul 2>&1
    @echo AsAlpha $<            " $(ALPHA_ASSEMBLER) "
    @$(ALPHA_ASSEMBLER) -o $@ $(MAKEDIR)\alpha\$(<F)

.SUFFIXES: .il

{}.il{}.cod:
    @-erase $@ >nul 2>&1
    @type <<
$(ECHO_MSG)
<<NOKEEP
    @$(C_COMPILER_NAME) @<< -FAac -Fa$(<B).cod -B1..\bootbin\null.exe -Bk$(<B). -Fo$(MAKEDIR)\obj\alpha\$(<B).o $(MAKEDIR)\$(<B).c
$(C_COMPILER_FLAGS: =
)
<<NOKEEP
    @del obj\alpha\$(<B).o

{}.il{obj\alpha\}.obj:
    @-erase $@ >nul 2>&1
    @type <<
$(ECHO_MSG)
<<NOKEEP
    @$(C_COMPILER_NAME) @<< -B1..\bootbin\null.exe -Bk$(<B). -Fo$(MAKEDIR)\$@  $(MAKEDIR)\$(<B).c
$(C_COMPILER_FLAGS: =
)
<<NOKEEP

LIBRARY_OBJS=$(OBJECTS) $(LINKLIBS)

!IFDEF TUKWILA
_NTTREE=$(_NTALPHATREE)
!ENDIF

!IFDEF CAIRO_PRODUCT
!IFDEF _CAIROALPHATREE
_NTTREE=$(_CAIROALPHATREE)
!ENDIF
!ELSE
!IFDEF _NTALPHATREE
_NTTREE=$(_NTALPHATREE)
!ENDIF
!ENDIF

!IFDEF KERNEL_MODE
_NTTREE=$(_NTALPHATREE)\km
!ENDIF

!IFDEF _NTALPHALIBS
_NTLIBS=$(_NTALPHALIBS)
!ENDIF

COPYDST=$(ALPHACOPYDST)

LIB_COPY=ntalphacp.cmd

NTTEST_LINK_OPTIONS= -base:0x80080000 -fixed -entry:KiSystemStartup
