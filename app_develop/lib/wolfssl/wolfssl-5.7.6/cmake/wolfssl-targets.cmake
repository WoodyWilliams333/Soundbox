# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.8)
   message(FATAL_ERROR "CMake >= 2.8.0 required")
endif()
if(CMAKE_VERSION VERSION_LESS "2.8.3")
   message(FATAL_ERROR "CMake >= 2.8.3 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.8.3...3.24)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_cmake_targets_defined "")
set(_cmake_targets_not_defined "")
set(_cmake_expected_targets "")
foreach(_cmake_expected_target IN ITEMS wolfssl::wolfssl)
  list(APPEND _cmake_expected_targets "${_cmake_expected_target}")
  if(TARGET "${_cmake_expected_target}")
    list(APPEND _cmake_targets_defined "${_cmake_expected_target}")
  else()
    list(APPEND _cmake_targets_not_defined "${_cmake_expected_target}")
  endif()
endforeach()
unset(_cmake_expected_target)
if(_cmake_targets_defined STREQUAL _cmake_expected_targets)
  unset(_cmake_targets_defined)
  unset(_cmake_targets_not_defined)
  unset(_cmake_expected_targets)
  unset(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT _cmake_targets_defined STREQUAL "")
  string(REPLACE ";" ", " _cmake_targets_defined_text "${_cmake_targets_defined}")
  string(REPLACE ";" ", " _cmake_targets_not_defined_text "${_cmake_targets_not_defined}")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_cmake_targets_defined_text}\nTargets not yet defined: ${_cmake_targets_not_defined_text}\n")
endif()
unset(_cmake_targets_defined)
unset(_cmake_targets_not_defined)
unset(_cmake_expected_targets)


# Create imported target wolfssl::wolfssl
add_library(wolfssl::wolfssl SHARED IMPORTED)

set_target_properties(wolfssl::wolfssl PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "WOLFSSL_DLL;HAVE___UINT128_T;HAVE_THREAD_LS;HAVE_PTHREAD;_POSIX_THREADS;TFM_TIMING_RESISTANT;ECC_TIMING_RESISTANT;WC_RSA_BLINDING;GCM_TABLE_4BIT;HAVE_AESGCM;WOLFSSL_USE_ALIGN;WOLFSSL_SHA512;WOLFSSL_SHA384;HAVE_HKDF;NO_DSA;HAVE_ECC;TFM_ECC256;ECC_SHAMIR;WC_RSA_PSS;WOLFSSL_PSS_LONG_SALT;WOLFSSL_BASE64_ENCODE;NO_DES3_TLS_SUITES;WOLFSSL_SHA224;WOLFSSL_SHA3;WOLFSSL_NO_SHAKE256;WOLFSSL_NO_SHAKE128;HAVE_POLY1305;HAVE_ONE_TIME_AUTH;HAVE_CHACHA;HAVE_HASHDRBG;HAVE_TLS_EXTENSIONS;HAVE_SUPPORTED_CURVES;HAVE_FFDHE_2048;HAVE_SUPPORTED_CURVES;WOLFSSL_TLS13;HAVE_TLS_EXTENSIONS;HAVE_EXTENDED_MASTER;NO_RC4;HAVE_ENCRYPT_THEN_MAC;NO_PSK;NO_MD4;WOLFSSL_X86_64_BUILD;WC_NO_ASYNC_THREADING;HAVE_DH_DEFAULT_PARAMS;NO_DES3;WOLFSSL_SYS_CA_CERTS;HAVE_TLS_EXTENSIONS;HAVE_SNI"
  INTERFACE_INCLUDE_DIRECTORIES "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6;/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake"
  INTERFACE_LINK_LIBRARIES "Threads::Threads;m"
)

# Import target "wolfssl::wolfssl" for configuration ""
set_property(TARGET wolfssl::wolfssl APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(wolfssl::wolfssl PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "/home/dell/TEMP/wolfssl-5.7.6/wolfssl-5.7.6/cmake/libwolfssl.so.43.0.0"
  IMPORTED_SONAME_NOCONFIG "libwolfssl.so.43"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
