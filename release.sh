#!/bin/sh

# get the latest and greatest
echo updating the local repository
git clone https://github.com/micooke/arduino-nRF5-smartwatches.git
cd arduino-nRF5-smartwatches

# save the path
fullpath=$(pwd)
path=${PWD##*/}

# update submodules
git submodule update --init --recursive
cd libraries/Kx022-1020 && git pull origin master && cd $fullpath
cd libraries/SoftwareI2C && git pull origin master && cd $fullpath
cd libraries/sparkfun_OLED && git pull origin master && cd $fullpath
cd libraries/HP203B && git pull origin master && cd $fullpath
cd libraries/Si1143 && git pull origin master && cd $fullpath
cd libraries/SoftwareSerial && git pull origin master && cd $fullpath
return
read -p "Release number (e.g. 0.2.1):" version

# copy the folder
cd ..
cp -r $path $path-$version
cd $path-$version

# remove all .git folders
rm -Rf .git
rm -Rf libraries/Kx022-1020/.git
rm -Rf libraries/SoftwareI2C/.git
rm -Rf libraries/sparkfun_OLED/.git
rm -Rf libraries/HP203B/.git
rm -Rf libraries/Si1143/.git
rm -Rf libraries/SoftwareSerial/.git

# gzip it up
cd ..
tar -czvf $version.tar.gz $path-$version

# clean up
rm -Rf $path-$version

# output size and md5
md5_=$(md5sum $version.tar.gz)
size_=$(wc -c $version.tar.gz)
echo md5 : $md5_
echo size : $size_
