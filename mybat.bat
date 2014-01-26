@echo off

set cur_dir=%CD%

cd *-Release
set R_dir=%CD%
cd ..

rem 在工程中生成download文件夹，并复制相关文件
md download 
cp %R_dir%/release/*.exe download
cp README.md download/readme.txt
cp source/*.xml download