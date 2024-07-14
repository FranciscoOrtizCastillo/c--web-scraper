# Web scraping en C++

[Web scraping con C++ paso a paso](https://brightdata.es/blog/procedimientos/web-scraping-in-c-plus-plus)

```bash

git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh

# Añadir vcpkg al PATH
# en el archivo .zshrc 
#export VCPKG_ROOT=~/vcpkg
#PATH=$VCPKG_ROOT:$PATH

mkdir c++-web-scraper
cd c++-web-scraper

vcpkg new --application
vcpkg add port cpr libxml2 --triplet=x64-osx

cmake --preset=default
cmake --build build
./build/main

```


En la consola del Navegador, una vez abierto www.race.es

$x("//div[contains(@class, 'vc_gitem-zone-mini')]")

Mostrara los 4 elementos

