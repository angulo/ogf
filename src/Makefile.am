LIBRARY_VERSION = 0:1:0

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-I "OGF/core" \
	-I "OGF/util" \
	$(OGRE_CFLAGS) $(CEGUI_CFLAGS) $(CEGUI_OGRE_CFLAGS) $(OIS_CFLAGS) $(SDL_MIXER)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libogf-0.1.la

libogf_0_1_la_SOURCES =\
OGF/core/Bootstrap.cpp \
OGF/core/InputManager.cpp \
OGF/core/ISceneFactory.cpp \
OGF/core/Log.cpp \
OGF/core/LogFactory.cpp \
OGF/core/Scene.cpp \
OGF/core/SceneController.cpp \
OGF/util/ModelBuilder.cpp \
OGF/util/ModelFactory.cpp \
OGF/util/SoundChunk.cpp \
OGF/util/SoundChunkManager.cpp \
OGF/util/SoundTrack.cpp \
OGF/util/SoundTrackManager.cpp

libogf_0_1_la_LDFLAGS = -version-info $(LIBRARY_VERSION)
libogf_0_1_la_LIBADD = $(OGRE_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS) $(OIS_LIBS) $(SDL_MIXER_LIBS)

library_maindir = $(includedir)/OGF/
library_main_HEADERS =\
OGF.h

library_coredir = $(includedir)/OGF/core
library_core_HEADERS =\
OGF.h \
OGF/core/Bootstrap.h \
OGF/core/InputManager.h \
OGF/core/ISceneFactory.h \
OGF/core/Log.h \
OGF/core/LogFactory.h \
OGF/core/Scene.h \
OGF/core/SceneController.h \
OGF/core/Types.h


library_utildir = $(includedir)/OGF/util
library_util_HEADERS =\
OGF/util/ModelBuilder.h \
OGF/util/ModelFactory.h \
OGF/util/SoundChunk.h \
OGF/util/SoundChunkManager.h \
OGF/util/SoundTrack.h \
OGF/util/SoundTrackManager.h
