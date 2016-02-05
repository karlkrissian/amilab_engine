#!/bin/bash

for classname in $* 
do
  echo "cp wrap/wrap_wx${classname}.h ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.8"
  cp wrap/wrap_wx${classname}.h ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.8

  echo "cp wrap/wrap_wx${classname}.cpp ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.8"
  cp wrap/wrap_wx${classname}.cpp ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.8
done
