@echo off
setlocal enabledelayedexpansion

REM 遍历当前目录中的所有文件
for %%i in (*) do (
    REM 检查文件扩展名，如果不是 .ewp, .eww 或 .bat 则删除
    if "%%~xi" neq ".ewp" (
        if "%%~xi" neq ".eww" (
            if "%%~xi" neq ".ewd" (
				if "%%~xi" neq ".bat" (
					del "%%i"
				)
            )
        )
    )
)

REM 删除所有子文件夹
for /d %%i in (*) do (
    rmdir /s /q "%%i"
)

endlocal
echo All done.
pause
