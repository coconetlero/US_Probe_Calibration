CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(US_Probe_Calibration)

IF(COMMAND CMAKE_POLICY)
	   CMAKE_POLICY(SET CMP0003 NEW)
ENDIF(COMMAND CMAKE_POLICY)

FIND_PACKAGE(ITK)
IF(ITK_FOUND)
	INCLUDE(${ITK_USE_FILE})
ELSE(ITK_FOUND)
	MESSAGE(FATAL_ERROR "Cannot build US Probe Calibration without ITK.  Please set ITK_DIR.")
ENDIF(ITK_FOUND)

FIND_PACKAGE (VTK)
IF (VTK_FOUND)
   INCLUDE(${USE_VTK_FILE})
ELSE(VTK_FOUND)
	MESSAGE(FATAL_ERROR "Cannot build US Probe Calibration without VTK.  Please set ITK_DIR.")   
ENDIF(VTK_FOUND)


# Find QT 
FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE( ${QT_USE_FILE} )

# support for out-of-source build
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_BINARY_DIR} #this is where ui_ImageViewerUI.h is generated
  ${CMAKE_CURRENT_SOURCE_DIR}
)


#----------------------------  for levmar --------------------------

INCLUDE_DIRECTORIES(levmar-2.5)


# levmar library source files
ADD_LIBRARY(levmar STATIC
  levmar-2.5/lm.c levmar-2.5/Axb.c levmar-2.5/misc.c levmar-2.5/lmlec.c 
  levmar-2.5/lmbc.c levmar-2.5/lmblec.c levmar-2.5/lmbleic.c levmar-2.5/levmar.h
  levmar-2.5/misc.h levmar-2.5/compiler.h
)

# demo program
LINK_DIRECTORIES(${LAPACKBLAS_DIR})
LINK_DIRECTORIES(.)


#----------------------------  for levmar --------------------------


 
# Set your files and resources here
SET(AppSrcs main.cpp mainwindow.cpp QVTKImageWidget.cpp QVTKImageWidgetCommand.cpp
    ProbeCalibrationWidget.cpp)
    
SET(AppHeaders mainwindow.h QVTKImageWidget.h QVTKImageWidgetCommand.h ProbeCalibrationWidget.h)
    
SET(AppUI mainwindow.ui ProbeCalibrationWidget.ui)
 
 
# for generate qt aditional files 
QT4_WRAP_UI(UISrcs ${AppUI})
QT4_WRAP_CPP(MOCSrcs ${AppHeaders} )
 
 
# Packaging source code in same files 
SOURCE_GROUP("Resources" FILES
  ${AppUI}
)
 
SOURCE_GROUP("Generated" FILES
  ${UISrcs}
  ${MOCSrcs}
)
 
ADD_EXECUTABLE(US_Probe_Calibration ${AppSrcs} ${AppHeaders} ${UISrcs} ${MOCSrcs}
    levmar-2.5/levmar.h)

#TARGET_LINK_LIBRARIES(US_Probe_Calibration QVTK ${VTK_LIBRARIES} ${ITK_LIBRARIES})

IF(HAVE_F2C) 
    TARGET_LINK_LIBRARIES(US_Probe_Calibration QVTK ${VTK_LIBRARIES} ${ITK_LIBRARIES} 
        levmar ${LAPACK_LIB} ${BLAS_LIB} ${F2C_LIB})
ELSE(HAVE_F2C)
    TARGET_LINK_LIBRARIES(US_Probe_Calibration QVTK ${VTK_LIBRARIES} ${ITK_LIBRARIES} 
        levmar ${LAPACK_LIB} ${BLAS_LIB} ${F77_LIB} ${I77_LIN})
ENDIF(HAVE_F2C)

