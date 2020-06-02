FILE(GLOB project_headers *.h)
FILE(GLOB project_sources *.cc)

SET(files_project ${project_headers} ${project_sources} )

add_library(Allocator ${files_project})