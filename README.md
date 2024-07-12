# Web scraping en C++

[Web scraping con C++ paso a paso](https://brightdata.es/blog/procedimientos/web-scraping-in-c-plus-plus)

```bash

git clone https://github.com/microsoft/vcpkg
./vcpkg/bootstrap-vcpkg.sh

# Añadir /dev/vcpkg al PATH
# en el archivo /Users/usr_desarrollo/.zshrc al final por ejemplo
# export PATH=$PATH:/Users/usr_desarrollo/Proyectos/Personal/vcpkg

mkdir c++-web-scraper
cd c++-web-scraper

vcpkg install cpr libxml2 --triplet=x64-osx
# En linux :
#cpkg install cpr libxml2 --triplet=x64-linux

vcpkg integrate install


cd build
main
```


En la consola del Navegador, una vez abierto www.race.es

$x("//div[contains(@class, 'vc_gitem-zone-mini')]")

Mostrara los 4 elementos