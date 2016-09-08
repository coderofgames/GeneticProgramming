Genetic Programming

This example successfully breeds math expressions to find the pythagoras theorem, 
and if you leave it running it will also find other functions that fit the sample
set (these may or may not be pythagoras theorom after simplification).

The math expressions are stored in an Abstract Syntax Tree built from a simple script
interpreter that was originally written in javascript. I simply converted the script 
interpreter to C++ then added the AST functionality to the Dijkstra shunting yard algorithm.
I then wrote the code to compute the Genetic algorithm, to perform mutation and crossover. 

The genetic programming algorithm was demonstrated notably in the early 90's by Koza, 1992, 1994. 
For more information please see the book "Artificial Intelligence, A guide to Intelligent Systems" 
by Michael Negnevitsky. 

Note: some of the string functions were from stack overflow