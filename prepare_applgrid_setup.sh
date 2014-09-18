#!/bin/bash

user=$USER
U=${user:0:1}

export WORK=/afs/cern.ch/work/${U}/${USER}

export platform=x86_64-slc6-gcc46-opt

export external=/afs/cern.ch/sw/lcg/external
export releases=/afs/cern.ch/sw/lcg/app/releases
export contrib=/afs/cern.ch/sw/lcg/contrib

source ${contrib}/gcc/4.6/${platform}/setup.sh

export ROOTSYS=/afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.05/${platform}/root
export HOPPET=${WORK}/usr/hoppet/1.1.5

export PATH=${HOPPET}/bin:${ROOTSYS}/bin:${PATH}
export LD_LIBRARY_PATH=${HOPPET}/lib:${ROOTSYS}/lib:${LD_LIBRARY_PATH}
