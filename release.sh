#!/bin/sh
#path=`pwd`
path=${PWD##*/}
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