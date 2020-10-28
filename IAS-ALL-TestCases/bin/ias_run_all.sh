#!/bin/bash
trap "kill 0" EXIT

script_dir=$(dirname $(readlink -f ${0}))


cd ${script_dir}/..

_dir=/tmp/ias_all_tests/

rm -rf ${_dir}
mkdir -p ${_dir}

(
  while true ; do
  sleep 1
  printf "\r\033[0K Cases : %d" $(grep ^TestCase ${_dir}/*.out.txt |wc -l)
  done
)&
##############################################################################
# Common Lib
printf "Testing: %20s" CommonLib
commonlib-testcases > ${_dir}/commonlib.out.txt  2> ${_dir}/commonlib.err.txt
printf ", done! \n"
##############################################################################
# Lang Lib
printf "Testing: %20s"  LangLib
( cd ../IAS-LangLib-TestCases; . ./setenv.sh; ias_lang_testcases) \
  > ${_dir}/langlib.out.txt  2> ${_dir}/langlib.err.txt
printf ", done! \n"
##############################################################################
# IAS general
printf "Testing: %20s"  "IAS General"

./bin/ias_run_test.sh > ${_dir}/ias.out.txt  2> ${_dir}/ias.err.txt
printf ", done! \n"
##############################################################################
# Databases
which sqlplus >/dev/null 2>/dev/null
if [[ $? == 0 ]]
then
printf "Testing: %20s"  "Databases: Oracle"
(
  cd ../IAS-QSystemDS-TestCases
. ./bin/setenv.sh
./db/oracle/bin/setup.sh
./bin/run_all_tests.sh -d oracle

) > ${_dir}/db-oracle.out.txt  2> ${_dir}/db-oracle.err.txt
printf ", done! \n"
fi
##############################################################################

cd ${_dir}
grep ^TestCase *.out.txt |sed s/::/_/g | cut -d: -f 1,3,4 > results.txt

echo Checking for errors :
grep -v '| 1' results.txt > errors.txt
if [[ $? != 0 ]]
then
  echo No errors;
else
  printf " %d error(s) found \n" $(cat errors.txt | wc -l)
  cat errors.txt
fi