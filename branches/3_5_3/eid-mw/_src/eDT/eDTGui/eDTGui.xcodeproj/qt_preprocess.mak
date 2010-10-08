#############################################################################
# Makefile for building: eDTGui.app/Contents/MacOS/eDTGui
# Generated by qmake (2.01a) (Qt 4.5.0) on: Wed Mar 18 10:39:53 2009
# Project:  eDTGui.pro
# Template: app
# Command: /usr/bin/qmake -spec /usr/local/Qt4.5/mkspecs/macx-xcode -macx -o eDTGui.xcodeproj/project.pbxproj eDTGui.pro
#############################################################################

MOC       = /Developer/Tools/Qt/moc
UIC       = /Developer/Tools/Qt/uic
LEX       = flex
LEXFLAGS  = 
YACC      = yacc
YACCFLAGS = -d
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
INCPATH       = -I/usr/local/Qt4.5/mkspecs/macx-xcode -I. -I/Library/Frameworks/QtCore.framework/Versions/4/Headers -I/usr/include/QtCore -I/Library/Frameworks/QtGui.framework/Versions/4/Headers -I/usr/include/QtGui -I/usr/include -I../../eDTGui -I../../eDTGui -I../../eDTGui -I/usr/local/include -I/System/Library/Frameworks/CarbonCore.framework/Headers -I.
DEL_FILE  = rm -f
MOVE      = mv -f

IMAGES = 
PARSERS =
preprocess: $(PARSERS) compilers
clean preprocess_clean: parser_clean compiler_clean

parser_clean:
mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compilers: ./moc_edtgui.cpp ./moc_qtsingleapplication.cpp ./qrc_edtgui.cpp ./ui_edtgui.h
compiler_objective_c_make_all:
compiler_objective_c_clean:
compiler_moc_header_make_all: moc_edtgui.cpp moc_qtsingleapplication.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_edtgui.cpp moc_qtsingleapplication.cpp
ui_edtgui.h: edtgui.ui
	/Developer/Tools/Qt/uic edtgui.ui -o ui_edtgui.h

moc_edtgui.cpp: ui_edtgui.h \
		enginethread.h \
		edtgui.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ edtgui.h -o moc_edtgui.cpp

moc_qtsingleapplication.cpp: qtsingleapplication.h
	/Developer/Tools/Qt/moc $(DEFINES) $(INCPATH) -D__APPLE__ -D__GNUC__ qtsingleapplication.h -o moc_qtsingleapplication.cpp

compiler_rcc_make_all: qrc_edtgui.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_edtgui.cpp
qrc_edtgui.cpp: edtgui.qrc
	/Developer/Tools/Qt/rcc -name edtgui edtgui.qrc -o qrc_edtgui.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_rez_source_make_all:
compiler_rez_source_clean:
compiler_uic_make_all: ui_edtgui.h
compiler_uic_clean:
	-$(DEL_FILE) ui_edtgui.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 
