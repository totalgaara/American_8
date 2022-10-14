#bin/sh
rm Programme_Principal.o
g++ mainJeu.cpp ./Jeu/*.cpp ./Jeu/sql/sqlite3.o -o Programme_Principal.o --std=c++11 -ldl -lpthread
chmod +x Programme_Principal.o
./Programme_Principal.o

