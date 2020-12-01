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