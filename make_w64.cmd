@ECHO OFF

REM set target=i386
set target=amd64

set MSVC=%USERPROFILE%\cmsc\msvc\bin\%target%
set libs=/LIBPATH:"%MSVC%\..\..\lib\%target%"
set incl=/I"%MSVC%\..\..\include\crt"

set C_FLAGS=/Wall /O1 /Os /Ob1 /Oi /GS- /MD /TC
set LINK_FLAGS=%libs% /ENTRY:"main" /FILEALIGN:512 /MERGE:.rdata=.text

%MSVC%\cl.exe %CD%\spconfig.c %incl% %C_FLAGS% %EXTRA_LIBS% /link %LINK_FLAGS%

pause
