#!/usr/bin/env ruby
# -----------------------------------------------------------------------------
# 'MakeCorrelatorResponseStandalone.rb'
# Derek Anderson
# 05.16.2024
#
# Short script to run the 'MakeCorrelatorResponseStandalone.cxx' macro.
# -----------------------------------------------------------------------------

if ARGV[0] == "condor"
  exec("condor_submit MakeCorrelatorResponseStandalone.job")
else
  exec("root -b -q MakeCorrelatorResponseStandalone.cxx")
end

# end -------------------------------------------------------------------------

