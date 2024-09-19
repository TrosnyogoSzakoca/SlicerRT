project(vtkSlicer${MODULE_NAME}ModuleLogic)

set(KIT ${PROJECT_NAME})


set(${KIT}_EXPORT_DIRECTIVE "VTK_SLICER_${MODULE_NAME_UPPER}_LOGIC_EXPORT")

set(${KIT}_INCLUDE_DIRECTORIES
  ${SlicerRtCommon_INCLUDE_DIRS}
  ${vtkSlicerBeamsModuleMRML_INCLUDE_DIRS}
  ${vtkSlicerSubjectHierarchyModuleLogic_INCLUDE_DIRS}
  ${vtkIECTransformLogic_INCLUDE_DIRS}
  #${vtkIECTransformLogic_DIR}
  )

set(${KIT}_SRCS
  vtkSlicer${MODULE_NAME}ModuleLogic.cxx
  vtkSlicer${MODULE_NAME}ModuleLogic.h
  #vtkSlicerIECTransformLogic.cxx
  #vtkSlicerIECTransformLogic.h
  vtkSlicerMLCPositionLogic.cxx
  vtkSlicerMLCPositionLogic.h
  )

SET (${KIT}_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${vtkSlicerBeamsModuleMRML_INCLUDE_DIRS} ${vtkIECTransformLogic_INCLUDE_DIRS} CACHE INTERNAL "" FORCE)

#message("ZZZ vtkIECTransformLogic: ${vtkIECTransformLogic_LIBS}")
#message("ZZZ vtkAddon_LIBS: ${vtkAddon_LIBS}")
#message("ZZZ VTK_LIBRARIES: ${VTK_LIBRARIES}")
find_package(vtkIECTransformLogic REQUIRED)

set(${KIT}_TARGET_LIBRARIES
  vtkSlicer${MODULE_NAME}ModuleMRML
  vtkSlicerRtCommon
  vtkSlicerMarkupsModuleMRML
  vtkSlicerSubjectHierarchyModuleLogic
  ${ITK_LIBRARIES}
  ${VTK_LIBRARIES}
  #${vtkIECTransformLogic_LIBS}
  vtkIECTransformLogic
  )
  

#-----------------------------------------------------------------------------
SlicerMacroBuildModuleLogic(
  NAME ${KIT}
  EXPORT_DIRECTIVE ${${KIT}_EXPORT_DIRECTIVE}
  INCLUDE_DIRECTORIES ${${KIT}_INCLUDE_DIRECTORIES}
  SRCS ${${KIT}_SRCS}
  TARGET_LIBRARIES ${${KIT}_TARGET_LIBRARIES}
  )
  
