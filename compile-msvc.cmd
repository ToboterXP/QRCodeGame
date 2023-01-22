python make_levels.py
cl /O2 /Os /MT /GS- main.c kernel32.lib /link /ALIGN:16 /NODEFAULTLIB /NOLOGO /ENTRY:_start /SUBSYSTEM:CONSOLE /MERGE:.rdata=.data /DYNAMICBASE:NO /STUB:empty_mz.exe
IF %ERRORLEVEL% NEQ 0 goto error


:end
dir main.exe
python make_qrcode.py

:error
