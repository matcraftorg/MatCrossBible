@cls

rmdir build /s /q
rmdir debug /s /q
rmdir release /s /q
del Makefile* /s
del object_script* /s
del .qmake.stash /s

qmake
mingw32-make

pause

rmdir build /s /q
rmdir debug /s /q
rmdir release /s /q
del Makefile* /s
del object_script* /s
del .qmake.stash /s
