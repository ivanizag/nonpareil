docker build . --tag nonpareilbuild
docker run --rm -v `pwd`:/src --user $(id -u):$(id -g) nonpareilbuild scons

echo Copying files to dist
mkdir -p dist
cp rom/* dist
cp obj/* dist
cp image/* dist
cp kml/* dist
cp build/posix/nonpareil dist
echo
echo Execute nonpareil in dist, i.e.: ./nonpareil 11c.kml