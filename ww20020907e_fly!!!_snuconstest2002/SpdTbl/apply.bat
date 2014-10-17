@echo off
echo Copying speed table to relative folder...
echo ; Wing(main) / Swing / Turn / iTurn Folder
copy speed.tbl ..\swing	> null
copy speed.tbl ..\turn	> null
copy speed.tbl ..\iturn	> null
copy speed.tbl ..	> null
