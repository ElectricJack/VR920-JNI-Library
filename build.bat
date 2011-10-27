"..\..\..\My Tools\swigwin\swig.exe" -java -c++ -package net.minecraft.client -module ModVR920 VR920.i
gcc -c IWRsdk.c
g++ -c VR920.cpp VR920_wrap.cxx
g++ -Wall -D_JNI_IMPLEMENTATION_ -Wl,--kill-at -shared VR920_wrap.o VR920.o IWRsdk.o -lopengl32 -o VR920JNI.dll
mkdir JNI
copy *.java JNI\*
copy VR920JNI.dll JNI\*
del *.java
del *.cxx
del *.o
del *.dll
