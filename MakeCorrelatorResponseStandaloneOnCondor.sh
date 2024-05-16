#!/bin/bash
# -----------------------------------------------------------------------------
# 'MakeCorrelatorResponseStandaloneOnCondor.sh'
# Derek Anderson
# 05.16.2024
#
# short script to run 'MakeCorrelatorResponseStandalone.cxx' macro via condor
# -----------------------------------------------------------------------------

# set up environment
export USER="$(id -u -n)"
export LOGNAME=${USER}
export HOME=/sphenix/u/${LOGNAME}
source /opt/sphenix/core/bin/sphenix_setup.sh
printenv

# run macro
root -b -q "MakeCorrealtorResponseStandalone.cxx(true)"

# end -------------------------------------------------------------------------
