cmake_minimum_required(VERSION 3.26)

# when using SetApi, first parameter is the target directory,
# second is whether it is exported from the engine, third is
# whether it is exported from the editor
function(SetExportMacro TARGET API_NAME EXPORT)
    if (MSVC)
        # To define ENGINE_API
        if(${EXPORT})
            target_compile_definitions(${TARGET} PRIVATE ${API_NAME}=__declspec\(dllexport\))
        else()
            target_compile_definitions(${TARGET} PRIVATE ${API_NAME}=__declspec\(dllimport\))
        endif()

    elseif (GNU)
        # To define EDITOR_API
        if(${EXPORT})
            target_compile_definitions(${TARGET} PRIVATE ${API_NAME}=__attribute__\((dllexport\)))
        else()
            target_compile_definitions(${TARGET} PRIVATE ${API_NAME}=__attribute__\((dllimport\)))
        endif()
    endif ()
endfunction()