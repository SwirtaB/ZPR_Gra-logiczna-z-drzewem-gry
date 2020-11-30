# ZPR_Gra-logiczna-z-drzewem-gry

## Wymagania
#### Linux
- Biblioteki Qt5 i Boost (1.71+) wykrywane przez CMake
- Python (3.8+) wykrywany przez CMake
#### Windows
- Biblioteki Qt5 i Boost wykrywane przez kompilator (np. vcpkg zintegrowane z MSBuild)
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
```
./bin/Debug/hello.exe
```
## Generowanie i uruchomienie testow
Flaga BUILD_TESTS w CMakeLists.txt kontroluje uruchamianie testów przy budowie
```
set(BUILD_TESTS True)
```
Po zbudowaniu z flaga BUILD_TESTS:
```
./build/Debug/tests.exe
```