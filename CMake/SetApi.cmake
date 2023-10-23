cmake_minimum_required(VERSION 3.26)


# when using SetApi, first parameter is the target directory,
# second is whether it is exported from the engine, third is
# whether it is exported from the editor
function(SetApi TARGET ENGINE_EXPORT EDITOR_EXPORT)
    if (MSVC)
        # To define FORCEINLINE
        target_compile_definitions(${TARGET} PRIVATE FORCEINLINE=__forceinline)

        # To define ENGINE_API
        if(${ENGINE_EXPORT})
            target_compile_definitions(${TARGET} PRIVATE ENGINE_API=__declspec\(dllexport\))
        else()
            target_compile_definitions(${TARGET} PRIVATE ENGINE_API=__declspec\(dllimport\))
        endif()

        # To define EDITOR_API
        if(${EDITOR_EXPORT})
            target_compile_definitions(${TARGET} PRIVATE EDITOR_API=__declspec\(dllexport\))
        else()
            target_compile_definitions(${TARGET} PRIVATE EDITOR_API=__declspec\(dllimport\))
        endif()
    elseif (GNU)
        # To define FORCEINLINE
        target_compile_definitions(${TARGET} PRIVATE FORCEINLINE=__attribute__\((always_inline\)))

        # To define ENGINE_API
        if(${ENGINE_EXPORT})
            target_compile_definitions(${TARGET} PRIVATE ENGINE_API=__attribute__\((dllexport\)))
        else()
            target_compile_definitions(${TARGET} PRIVATE ENGINE_API=__attribute__\((dllimport\)))
        endif()

        # To define EDITOR_API
        if(${EDITOR_EXPORT})
            target_compile_definitions(${TARGET} PRIVATE EDITOR_API=__attribute__\((dllexport\)))
        else()
            target_compile_definitions(${TARGET} PRIVATE EDITOR_API=__attribute__\((dllimport\)))
        endif()
    endif ()
endfunction()