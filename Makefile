CC=gcc
CXX=g++

all: build/sparsepp build/btree build/stl_unordered_map build/boost_unordered_map build/google_sparse_hash_map build/google_dense_hash_map 

build/glib_hash_table: src/glib_hash_table.c Makefile src/template.cc
	$(CC) -ggdb -O2 -DNDEBUG -lm `pkg-config --cflags --libs glib-2.0` src/glib_hash_table.c -o build/glib_hash_table

build/stl_unordered_map: src/stl_unordered_map.cc Makefile src/template.cc
	$(CXX) -O2 -DNDEBUG  -lm src/stl_unordered_map.cc -o build/stl_unordered_map -std=c++0x

build/boost_unordered_map: src/boost_unordered_map.cc Makefile src/template.cc
	$(CXX) -O2 -DNDEBUG  -lm src/boost_unordered_map.cc -o build/boost_unordered_map

build/google_sparse_hash_map: src/google_sparse_hash_map.cc Makefile src/template.cc
	$(CXX) -O2 -DNDEBUG  -lm src/google_sparse_hash_map.cc -o build/google_sparse_hash_map

build/google_dense_hash_map: src/google_dense_hash_map.cc Makefile src/template.cc
	$(CXX) -O2 -DNDEBUG  -lm src/google_dense_hash_map.cc -o build/google_dense_hash_map

build/sparsepp: src/sparsepp.cc Makefile src/template.cc
	$(CXX) -O2 -DNDEBUG  -lm src/sparsepp.cc -I.. -o build/sparsepp

build/btree: src/btree.cc Makefile src/template.cc
	$(CXX) -std=c++11 -O2 -DNDEBUG  -lm src/btree.cc -I. -o build/btree


build/qt_qhash: src/qt_qhash.cc Makefile src/template.cc
	$(CXX) -O2 -DNDEBUG  -lm `pkg-config --cflags --libs QtCore` src/qt_qhash.cc -o build/qt_qhash

build/python_dict: src/python_dict.c Makefile src/template.cc
	$(CXX)  -O2 -DNDEBUG  -lm -I/usr/include/python2.6 -lpython2.6 src/python_dict.c -o build/python_dict
