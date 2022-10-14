#bin/sh
rm Programme_SQL.o
g++ mainSQL.cpp ./Jeu/*.cpp ./Jeu/sql/sqlite3.o -o Programme_SQL.o --std=c++11 -ldl -lpthread
chmod +x Programme_SQL.o
./Programme_SQL.o
