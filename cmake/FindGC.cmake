if (GC_INCLUDES AND GC_LIBRARIES)
    set(GC_FIND_QUIETLY TRUE)
endif (GC_INCLUDES AND GC_LIBRARIES)
find_path(GC_INCLUDES
        NAMES
        gc.h
        PATHS
        $ENV{GCDIR}/include
        ${INCLUDE_INSTALL_DIR}
        )
find_library(GC_LIBRARIES
        GC
        PATHS
        $ENV{GCDIR}/lib
        /usr/lib/atlas-base
        ${LIB_INSTALL_DIR}
        )
find_file(GC_LIBRARIES
        libgc.so
        libgc.a
        PATHS
        /usr/lib
        /usr/lib/x86_64-linux-gnu
        $ENV{GCDIR}/lib
        ${LIB_INSTALL_DIR}
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GC DEFAULT_MSG
        GC_INCLUDES GC_LIBRARIES)
mark_as_advanced(GC_INCLUDES GC_LIBRARIES)