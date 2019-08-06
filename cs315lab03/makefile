CFLAGS= -ggdb -std=c++11 -Wall -Wextra


all: binTree.x


binTree.x:  TreeNode.o BinSearchTree.o
	g++ $(CFLAGS) -c -o binTree.x  TreeNode.o BinSearchTree.o

TreeNode.o: TreeNode.hpp
	g++ $(CFLAGS) -c -o TreeNode.o TreeNode.hpp

BinSearchTree.o: BinSeacrhTree.cpp BinSearchTree.hpp
	g++ $(CFLAGS) -c -o BinSearchTree.o BinSearchTree.cpp

