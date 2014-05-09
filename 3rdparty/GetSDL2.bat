REM Getting SDL2, SDL2_Image and SDL2_Mixer
REM ---------------------------------------

set prefix1=http://www.libsdl.org/release
set filename1=SDL2-devel-2.0.3-VC.zip

set prefix2=https://www.libsdl.org/projects/SDL_image/release
set filename2=SDL2_image-devel-2.0.0-VC.zip

set prefix3=http://www.libsdl.org/projects/SDL_mixer/release
set filename3=SDL2_mixer-devel-2.0.0-VC.zip

cscript dl.vbs %prefix1%/%filename1% %filename1%
cscript dl.vbs %prefix2%/%filename2% %filename2%
cscript dl.vbs %prefix3%/%filename3% %filename3%

cscript unzip.vbs %filename1%
cscript unzip.vbs %filename2%
cscript unzip.vbs %filename3%

del %filename1%
del %filename2%
del %filename3%

