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
OGF/Bootstrap.cpp \
OGF/GuiScene.cpp \
OGF/InputManager.cpp \
OGF/ISceneFactory.cpp \
OGF/Log.cpp \
OGF/LogFactory.cpp \
OGF/Scene.cpp \
OGF/SceneController.cpp

libogf_0_1_la_LDFLAGS = -version-info $(LIBRARY_VERSION)
libogf_0_1_la_LIBADD = $(OGRE_LIBS) $(CEGUI_LIBS) $(CEGUI_OGRE_LIBS) $(OIS_LIBS)

library_includedir = $(includedir)/OGF/

library_include_HEADERS =\
OGF.h \
OGF/Bootstrap.h \
OGF/GuiScene.h \
OGF/InputManager.h \
OGF/ISceneFactory.h \
OGF/Log.h \
OGF/LogFactory.h \
OGF/Scene.h \
OGF/SceneController.h \
OGF/Types.h
