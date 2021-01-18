::cls
REM del *.o *.exe
"C:\MinGW\bin\g++.exe" -c data_structure.cpp
"C:\MinGW\bin\g++.exe" -c main.cpp
"C:\MinGW\bin\g++.exe" -o vnc-app data_structure.o main.o
vnc-app.exe
