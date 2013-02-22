LIBRARY_VERSION = 0:1:0

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OGRE_CFLAGS) $(CEGUI_CFLAGS) $(CEGUI_OGRE_CFLAGS) $(OIS_CFLAGS) 

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libogf-0.1.la

libogf_0_1_la_SOURCES =\
OGF/core/Bootstrap.cpp \
OGF/core/GuiScene.cpp \
OGF/core/InputManager.cpp \
OGF/core/ISceneFactory.cpp \
OGF/core/Log.cpp \
OGF/core/LogFactory.cpp \
OGF/core/ModelFactory.cpp \
OGF/core/Scene.cpp \
OGF/core/SceneController.cpp

libogf_0_1_la_LDFLAGS = -version-info $(LIBRARY_VERSION)
libogf_0_1_la_LIBADD = $(OGRE_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS) $(OIS_LIBS)

library_includedir = $(includedir)/OGF/

library_include_HEADERS =\
OGF.h \
OGF/core/Bootstrap.h \
OGF/core/GuiScene.h \
OGF/core/InputManager.h \
OGF/core/ISceneFactory.h \
OGF/core/Log.h \
OGF/core/LogFactory.h \
OGF/core/ModelFactory.h \
OGF/core/Scene.h \
OGF/core/SceneController.h \
OGF/core/Types.h
