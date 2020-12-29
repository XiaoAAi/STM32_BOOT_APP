::copy ..\Output\release.hex ..\%date:~0,4%%date:~5,2%%date:~8,2%0%time:~1,1%%time:~3,2%%time:~6,2%.hex
::copy ..\Output\release.bin ..\%date:~0,4%%date:~5,2%%date:~8,2%0%time:~1,1%%time:~3,2%%time:~6,2%.bin
copy ..\Output\release.hex ..\release_F103.hex
copy ..\Output\release.bin ..\realease.bin
MergeHex.exe --merge BootApp190417 ..\release_F103.hex --output ..\realease.hex
del ..\release_F103.hex