# ZPR_Gra-logiczna-z-drzewem-gry

## Wymagania
#### Linux
- Biblioteka Boost (1.71+) wykrywana przez CMake
- Python (3.8+) wykrywany przez CMake
#### Windows
- Biblioteka Boost wykrywana przez kompilator (np. vcpkg zintegrowane z MSBuild)
- Python (3.8+) wykrywany przez CMake

## Budowanie i uruchomienie
Budowanie:
```
mkdir cmake-build
cd cmake-build
cmake ..
cmake --build .
cd ..
```
Uruchomienie:
#### Windows
```
./bin/Debug/hello.exe
```
#### Linux
```
./bin/hello
```
## Generowanie i uruchomienie testow
Flaga BUILD_TESTS w CMakeLists.txt kontroluje uruchamianie testów przy budowie
```
set(BUILD_TESTS True)
```
Po zbudowaniu z flaga BUILD_TESTS:
#### Windows
```
./build/Debug/tests.exe
```
#### Linux
```
./build/tests
```