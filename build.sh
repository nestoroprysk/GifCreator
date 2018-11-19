thirdPartiesPath=ThirdParties
if [ ! -d "$thirdPartiesPath" ]
then
	git clone https://github.com/ginsweater/gif-h.git $thirdPartiesPath
fi
rm -rf Build
mkdir Build
cd Build
cmake ..
