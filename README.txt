------------------
About this Project
------------------
This project was completed on 29 May 2016 as the fifth coding project in the COEN 12 Abstract Data Types and Data Structures course at Santa Clara University. "tree.c" and "huffman.c" were written by Ray Che, building off of the included source files provided by Professor Darren C. Atkinson of the Computer Science and Engineering department. This project contains two parts: a sorting program and a compression program. The former simply takes in a series of numerical inputs and generates a binary search tree, then prints them out via an inorder traversal. The latter takes in two file inputs, constructs a huffman tree with the data from the character counts of the first file, and then compresses the data into the second file. This source code is only to be used as an example of Ray Che's programming ability as of the completion of the 2015-2016 academic year and shall not be used to assist other students attempting to complete the same project at Santa Clara University. Using this project in the latter manner is academic dishonesty and a violation of the student conduct code.   

-----------------------
Command Line Arguments
-----------------------
make treesort 
- Compiles code for the treesort program

./treesort
- Executes code for the treesort program

make huffman 
- Compiles code for huffman compression

./huffman FILE1 FILE2 
- Executes code for huffman compression
- FILE1 and FILE2 are placeholders for file inputs

gunzip -c FILE2
- Unzips output file for huffman program


