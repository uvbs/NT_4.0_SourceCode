/*
   Enhanced NCSA Mosaic from Spyglass
   "Guitar"

   Copyright 1994 Spyglass, Inc.
   All Rights Reserved

   Portions of this file were derived from
   the CERN libwww, version 2.15.
*/

#include "all.h"

PUBLIC void HTFormatInit(HTList * c)
{
	HTSetConversion(c, "*/*",          "www/present",      GTR_Present,                (float) 0.3);
#ifdef FEATURE_JPEG
	HTSetConversion(c, "image/jpeg", "www/inline_image", (void *) Image_JPEG, (float) 1.0);
#endif
	HTSetConversion(c, "image/x-xbitmap", "www/inline_image", (void *) Image_XBM, (float) 0.8);
	HTSetConversion(c, "image/gif", "www/inline_image", (void *) Image_GIF, (float) 1.0);

	HTSetConversion(c, "text/html", "www/present", GTR_Present, (float) 1.0);
	HTSetConversion(c, "text/plain", "www/present", GTR_Present, (float) 1.0);
#ifdef FEATURE_IMAGE_VIEWER
	HTSetConversion(c, "image/jpeg", "www/present", GTR_Present, (float) 1.0);
#endif
#ifdef FEATURE_IMG_INLINE
	HTSetConversion(c, "image/x-xbitmap", "www/present", GTR_Present, (float) 1.0);
#endif
#ifdef FEATURE_IMAGE_VIEWER
	HTSetConversion(c, "image/gif", "www/present", GTR_Present, (float) 1.0);
#endif
#ifdef FEATURE_SOUND_PLAYER
	HTSetConversion(c, "audio/basic", "www/present", GTR_Present, (float) 1.0);
	HTSetConversion(c, "audio/x-aiff", "www/present", GTR_Present, (float) 1.0);
#endif

#ifdef OLD_HOTLIST
	HTSetConversion(c, "text/html", "www/hotlist", HTMLToHotList, (float) 1.0);
#endif
	HTSetConversion(c, "text/html", "www/global_history", HTMLToGlobalHistory, (float) 1.0);
#ifdef FEATURE_CLIENT_IMAGEMAP
	HTSetConversion(c, "text/html", "www/map", HTMLToMap, (float) 1.0);
#endif

	HTSetConversion(c, "audio/basic",  "www/bgsound",      GTR_DownloadBackgroundBlob, (float) 1.0);
	HTSetConversion(c, "audio/x-aiff", "www/bgsound",      GTR_DownloadBackgroundBlob, (float) 1.0);
    HTSetConversion(c, "video/avi",    "www/mci",          GTR_DownloadBackgroundBlob, (float) 1.0);

#ifdef FEATURE_VRML
    HTSetConversion(c, "x-world/x-vrml","www/vrml",          GTR_DownloadBackgroundBlob, (float) 1.0);
#endif

	HTSetConversion(c, "*/*",          "www/unknown",      GTR_DoDownLoad,             (float) 0.3);
	HTSetConversion(c, "*/*",          "www/signed",       GTR_DownloadSigned,         (float) 0.3);
	HTSetConversion(c, "*/*",          "www/bgsound",      GTR_DownloadBackgroundBlob, (float) 0.3);
 HTSetConversion(c, "*/*",          "www/mci",          GTR_DownloadBackgroundBlob, (float) 0.3);
#ifdef FEATURE_VRML
 HTSetConversion(c, "*/*",       "www/vrml",          GTR_DownloadBackgroundBlob, (float) 0.3);
#endif

	
	HTSetConversion(c, "*/*",          "www/x-forcedownload", GTR_DoDownLoadNoUndefDlg,(float) 1.0);	
}


