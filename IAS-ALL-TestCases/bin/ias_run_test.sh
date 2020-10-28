#!/bin/bash

script_dir=$(dirname $(readlink -f ${0}))

if [ ! -d ${script_dir}/../spec ] ; then
echo "Test cases cannot be found. This directory is missing: " ${script_dir}/../spec
fi

export IAS_LANG_XSD=${script_dir}/../xsd/customer.xsd
export IAS_LANG_SRC_DIRS=lang:${script_dir}/../lang

_copy=NO

cd ${script_dir}/../spec/


function run_test {

  _case=${1?}

  cd ${_case}

  _out_dir=/tmp/ias_test/${_case?}
  mkdir -p ${_out_dir?}/output
  rm -f ${_out_dir?}/*.* ${_out_dir?}/output/*.*

  ${_debug} ias_qs_processor \
    -o dir:${_out_dir?}/output/'${MID}' -l run main  \
    >${_out_dir?}/output/stdout.txt \
    2>${_out_dir?}/output/stderr.txt

  if [ ${_copy} == YES ]
  then
    mkdir -p output
    cp ${_out_dir}/output/* output
  fi

  diff -bw ${_out_dir?}/output output 2> ${_out_dir}/output.diff 1>&2

  if [ $? == 0 ]
  then
    _result=1
  else
    _result=0
  fi

  printf "TestCase: %48s : %30s | %d : %ld : %6ld : %s \n" ${_case} caseOne ${_result} 0 0 ""

}

function help {
     echo
     echo "IAS test cases:"
     echo `basename $0` "<parameters>"
     echo "Parameters:"
     echo "  -t <testnames>   Testcase names (comma separated)."
     echo "  -c copy answer to specification."
     echo
     #echo $*
     echo
     exit 1
}


while getopts hdct: opt
do
  case $opt in
    h)
      help 0
    ;;
    t)
      _case_names=$( echo $OPTARG|tr , " ")
    ;;
    c)
      _copy=YES
    ;;
    d)
      _debug=d
    ;;
    *)
      help Invalid option.
     ;;
  esac
done

if [ -z "${_case_names}" ]; then
_case_names=$(ls)
echo "Running all cases: " ${_case_names}
fi

echo
echo Copy cases to specification directory: ${_copy}
echo
for c in ${_case_names}
do
 ( run_test $c )
done

echo
