if (CBLAS_INCLUDES AND CBLAS_LIBRARIES)
    set(CBLAS_FIND_QUIETLY TRUE)
endif (CBLAS_INCLUDES AND CBLAS_LIBRARIES)
find_path(CBLAS_INCLUDES
        NAMES
        cblas.h
        PATHS
        $ENV{CBLASDIR}/include
        ${INCLUDE_INSTALL_DIR}
        )
find_library(CBLAS_LIBRARIES
        cblas
        PATHS
        $ENV{CBLASDIR}/lib
        /usr/lib/atlas-base
        ${LIB_INSTALL_DIR}
        )
find_file(CBLAS_LIBRARIES
        libcblas.so
        libcblas.so.3
        PATHS
        /usr/lib
        /usr/lib/atlas-base
        $ENV{CBLASDIR}/lib
        ${LIB_INSTALL_DIR}
        )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CBLAS DEFAULT_MSG
        CBLAS_INCLUDES CBLAS_LIBRARIES)
mark_as_advanced(CBLAS_INCLUDES CBLAS_LIBRARIES)