#
# Macro to traverse all the subdirectories of a specific directory
#
MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

#
# Function to add the theme implementation to the specific library of the theme
#
FUNCTION (InjectThemeImplementation THEME)
  
  target_sources(${THEME} PUBLIC
    ${CMAKE_SOURCE_DIR}/theme_impl.cpp
  )

ENDFUNCTION()
