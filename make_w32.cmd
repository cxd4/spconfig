@ECHO OFF

set target=i386
REM set target=amd64

set DDK=C:\WinDDK\7600.16385.1
set MSVC=%DDK%\bin\x86\x86
set incl=/I"%DDK%\inc\crt" /I"%DDK%\inc\api"
set libs=/LIBPATH:"%DDK%\lib\crt\%target%" /LIBPATH:"%DDK%\lib\wnet\%target%"

set C_FLAGS=/Wall /Ox /Ob1 /Oi /GS- /MD /TC
set LINK_FLAGS=%libs% /ENTRY:"main" /FILEALIGN:512 /MERGE:.rdata=.text

%MSVC%\cl.exe %CD%\spconfig.c %incl% %C_FLAGS% /link %LINK_FLAGS%

pause
