@echo off

        if not "%1"=="" goto ok0
        echo  Error!
        echo  Usage: %0 source_name [hardware_dir]
		goto end
        :ok0

        if exist %1.exe goto ok1
        echo  Error!
        echo  Source file not found: EXE file
        goto end

        :ok1
        if exist %2exe2bin.exe goto ok2
        echo  Error!
        echo  Program not found: %2exe2bin.exe!
        goto end

        :ok2
        if exist %2bin2hex.exe goto ok3
        echo  Error!
        echo  Program not found: %2bin2hex.exe!
        goto end

        :ok3
        if exist %2seg_fix.dat goto ok4
        echo  Error!
        echo  Data file not found: %2seg_fix.dat!
        goto end


rem 6. Source EXE File -> Binary Code

        :ok4
        echo 
        echo ⁄ƒ                    ƒ∑
        echo   [1]   Exe to Bin       
        echo ‘Õ                      

        if exist %1.bin del %1.bin
        %2exe2bin %1.exe < %2seg_fix.dat

        if exist %1.bin goto pass1
        echo  Error!
        goto end


rem 7. Binary Code -> Hex Code

        :pass1
        echo 
        echo ⁄ƒ                    ƒ∑
        echo   [2]   Bin to Hex       
        echo ‘Õ                      

        if exist %1.hex del %1.hex
        %2bin2hex %1.bin > %1.hex

        if exist %1.hex goto  pass2
        echo  Error!
        goto end

rem 8. COM∑° π•∏Å–aìeª° —¬∑•–eîa.
        :pass2
        if exist %2com.exe goto pass3
        echo  Error!
        echo  Program not found: %2com.exe!
        goto end


rem 9. COM∑i ¨a∂w–aµa ∏Â≠∑–eîa.

        :pass3
        echo 
        echo ⁄ƒ                    ƒ∑
        echo   [3]  Communication     
        echo ‘Õ                      

        %2com.exe %1.HEX

rem 10.π∑ûa

        :end
