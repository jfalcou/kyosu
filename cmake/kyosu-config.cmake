##======================================================================================================================
##  Kyosu - Complex Without Complexes
##  Copyright : KYOSU Contributors & Maintainers
##  SPDX-License-Identifier: BSL-1.0
##======================================================================================================================

##======================================================================================================================
## Reuse install.cmake to preapre package properly
##======================================================================================================================
include("${CMAKE_CURRENT_LIST_DIR}/kyosu-targets.cmake")
set(KYOSU_LIBRARIES kyosu::kyosu)