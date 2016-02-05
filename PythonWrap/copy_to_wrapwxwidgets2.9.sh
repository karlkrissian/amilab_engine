#!/bin/bash

for classname in $* 
do
  echo "cp wrap/wrap_wx${classname}.h ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.9"
  cp wrap/wrap_wx${classname}.h ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.9

  echo "cp wrap/wrap_wx${classname}.cpp ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.9"
  cp wrap/wrap_wx${classname}.cpp ~/projects/Sourceforge/amilab/trunk/src/Wrapping/WrapWxWidgets/2.9
done
