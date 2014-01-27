@echo off

rem 在工程中生成download文件夹，并复制相关文件

cd *-Release
set R_dir=%CD%
cd ..

IF not EXIST download  md download 
cp -u %R_dir%/release/*.exe download
cp -u readme.txt download
cp -u source/*.xml download