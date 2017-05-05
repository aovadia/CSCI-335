Adam Ovadia 
CSCI 335 Project 2

Project description:
For Project 2, you will implement 3 heuristic approximation algorithms for the traveling salesperson problem:

1) Greedy TSP - Choose edges, in order of weight from lowest to highest, as long as adding the edge doesn't create a cycle before the last vertex is added, and doesn't cause any vertex to be adjacent to more than 2 edges.

2) Nearest insertion - Starting with a degenerate tour of the 2 closest vertices (that is, a tour going from A to B to A), repeatedly choose the non-tour vertex with the minimum distance to its nearest neighbor among the tour vertices, and insert it in between the two consecutive tour vertices for which such an insertion causes the minimum increase in total tour length.

3) Research or design another heuristic approximation algorithm for TSP is in some way better than the previous 2 algorithms (or at least that you can make a good argument as to why you thought it would be better). Implement it, test it, and write about why you thought it would be better, and how it actually performed.

Compile Program: g++ -std=c++11 -o program  Driver.cpp
Execute Program: ./program input.txt
--> input.txt is a text file of the Data Set
--> included files (already converted to .txt) in directory are: 
	(taken from http://www.math.uwaterloo.ca/tsp/world/countries.html)
	1) wi29.txt // working the best
	2) dj38.txt
	3) qa194.txt
	4) uy734.txt
	5) lu980.txt
	6) ym7663.txt

Algorithm descriptions:

A) Nearest Insertion: start off by finding the smallest edge (2 cities located closest together) and add to path.
	Then find the next nearest city that connects to the beginning or end of path and add if it doesn't create a cycle
	Repeat for the remaining cities left

B) Greedy Algorithm: find the smallest edge and add to path.
	Then find the next smallest edge (could either connect to a city already in the path or a separate edge). Add it to the path if no cycles form
	Repeat for all remaining cities

C) Third Algorithm: find the smallest edge.
	Then find the next smallest edge (that are not connected to previous found edges)
	Repeat until non connecting edges are found: (num of cities / 2) = total edges
	Connect the 2 smallest edges together and repeat as long as no cycle is created until forming 1 path
