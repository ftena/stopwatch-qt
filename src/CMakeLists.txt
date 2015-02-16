####################################
####   specific parameters
####################################

## application name
SET( APP_NAME "stopwatch" )

####################################
####   common parameters
####################################

## project name
PROJECT( ${APP_NAME} )

## require a minimum version of CMake
CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 FATAL_ERROR )

## add definitions, compiler switches, etc.
ADD_DEFINITIONS( -Wall -O2 )
SET( CMAKE_CXX_FLAGS -g )

## include (or not) the full compiler output
SET( CMAKE_VERBOSE_MAKEFILE OFF )

## required packages
FIND_PACKAGE( Qt4 REQUIRED)

INCLUDE ( ${QT_USE_FILE} )

FILE( MAKE_DIRECTORY qt_generated_headers )

# important! the next line is for enabling Qt Test
SET (QT_USE_QTTEST TRUE)

#FILE( MAKE_DIRECTORY qt_generated_headers )

## include directories
INCLUDE_DIRECTORIES ( 
	$ENV{QTDIR}/include
)

INCLUDE (
	${QT_USE_FILE}
)

## library paths
LINK_DIRECTORIES(
	$ENV{QTDIR}/lib
)

## sources
FILE( GLOB MAIN_SRC *.cpp )
SET( SOURCES ${MAIN_SRC} )

## headers
FILE( GLOB_RECURSE HEADERS *.h )

## qt uis
FILE( GLOB_RECURSE QT_UIS *.ui )

## Qt projects wrap UI files
## this will run uic on .ui files
SET ( CMAKE_CURRENT_DIR qt_generated_headers )
QT4_WRAP_UI( qt_UIS_HEADERS ${QT_UIS} )

SET ( FLAG 0 )
FILE ( REMOVE .mocs_files.dummy )
FILE ( WRITE .mocs_files.dummy "" )
FOREACH ( FILE_NAME ${HEADERS} )
	IF ( FLAG EQUAL 1 )
		FILE ( APPEND .mocs_files.dummy ";" )
	ENDIF ( FLAG EQUAL 1 )

	FILE ( READ ${FILE_NAME} CAD )
	STRING ( REGEX MATCH Q_OBJECT Q_OBJECT_VAR ${CAD} )

	IF ( Q_OBJECT_VAR )
		FILE ( APPEND .mocs_files.dummy ${FILE_NAME} )
		SET ( FLAG 1 )
		SET ( Q_OBJECT_VAR "" )
	ENDIF ( Q_OBJECT_VAR )
ENDFOREACH ( FILE_NAME ${MOCS} )

FILE ( READ .mocs_files.dummy FILES_NAME )
IF ( FILES_NAME )
	SET ( CMAKE_CURRENT_DIR moc_dir )
	#FILE ( MAKE_DIRECTORY moc_dir )
	QT4_WRAP_CPP ( qt_MOC_FILES ${FILES_NAME} )
ENDIF ( FILES_NAME )
FILE ( REMOVE .mocs_files.dummy )

## executable
ADD_EXECUTABLE( ${APP_NAME} ${SOURCES} ${qt_UIS_HEADERS} ${qt_MOC_FILES} )

## link
TARGET_LINK_LIBRARIES( ${APP_NAME} ${QT_LIBRARIES} )


