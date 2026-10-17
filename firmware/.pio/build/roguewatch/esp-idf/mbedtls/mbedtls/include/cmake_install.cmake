# Install script for directory: P:/packages/framework-espidf/components/mbedtls/mbedtls/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/msa_canary")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "P:/packages/toolchain-xtensa-esp-elf/bin/xtensa-esp32-elf-objdump.exe")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/mbedtls" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/aes.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/aria.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/asn1.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/asn1write.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/base64.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/bignum.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/block_cipher.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/build_info.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/camellia.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ccm.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/chacha20.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/chachapoly.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/check_config.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/cipher.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/cmac.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/compat-2.x.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_crypto.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_legacy_from_psa.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_from_legacy.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_psa_superset_legacy.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_ssl.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_adjust_x509.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/config_psa.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/constant_time.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ctr_drbg.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/debug.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/des.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/dhm.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecdh.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecdsa.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecjpake.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ecp.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/entropy.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/error.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/gcm.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/hkdf.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/hmac_drbg.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/lms.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/mbedtls_config.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/md.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/md5.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/memory_buffer_alloc.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/net_sockets.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/nist_kw.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/oid.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pem.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pk.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pkcs12.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pkcs5.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/pkcs7.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/platform.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/platform_time.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/platform_util.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/poly1305.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/private_access.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/psa_util.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ripemd160.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/rsa.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha1.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha256.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha3.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/sha512.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_cache.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_ciphersuites.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_cookie.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/ssl_ticket.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/threading.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/timing.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/version.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509_crl.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509_crt.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/mbedtls/x509_csr.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/psa" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/build_info.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_auto_enabled.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_dependencies.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_key_pair_types.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_adjust_config_synonyms.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_builtin_composites.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_builtin_key_derivation.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_builtin_primitives.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_compat.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_config.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_common.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_composites.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_key_derivation.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_driver_contexts_primitives.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_extra.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_legacy.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_platform.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_se_driver.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_sizes.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_struct.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_types.h"
    "P:/packages/framework-espidf/components/mbedtls/mbedtls/include/psa/crypto_values.h"
    )
endif()

