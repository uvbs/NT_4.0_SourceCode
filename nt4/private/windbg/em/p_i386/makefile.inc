!IF 0

Copyright (c) 1989  Microsoft Corporation

Module Name:

    makefile.inc

Abstract:

    This file tells nmake the correct dependency relationships
    for objects created from c files in this directory which are
    wrappers for c files in another directory.


Author:

    Kent Forschmiedt


!ENDIF

SRCDIR=..

!INCLUDE $(SRCDIR)\common.inc

obj\$(TARGET_DIRECTORY)\d3em.obj: d3.c
