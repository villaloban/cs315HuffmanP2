Student Info: Name: Anthony Villalobos Student ID: 008394627 Repo Link: https://github.com/villaloban/cs315Huffmanp2.git

Collaboration & Sources: The sources that I used in this project mainly involve looking at past labs for help on Binary Search Trees Implementation and the most recent lab that we did on min heap. This helped me internalize the priority queue and its functions. I also found that geeksforgeeks had very nice examples of huffman trees priority queues and binary search trees. I was stuck on my treenode hpp as I wasnt really sure how to change it for my words so I did ask AI how I would adjust my already existing Treenode hpp to be used for reading words

Implementation & Details: This project uses a scanner class to read from a file and tokenize the words making them form the basis of the frequency counting and Huffman coding. In this phase of the project we built a BST to handle the words and use functions such as insert, find, contains, size, height ect. We also build a Priority Queue so we could count the frequency of the words in the BST. This also is used to build the bst as we have the priotrty range from largest -> least and if there tied we take the two smallest and take the minimum and that gets created as the new node. We also add a custom TreeNde Hpp to deal with words insetad of ints as we usually would in a regular BST. 

The Functions used in this implementation include:
The algorithms that were used in this phase involve, BST, Priority Queue, 

Testing & Status: Input; In the testing whenever I tried to use diff with the files they werent found and I wasn't sure if that was a me error or becuase of the files themselves. However I tested them using my own solution and the results did seem to be working. For example I took the sentence, 

to be or not to be

and it produced the .tokens file: 
to
be
or
not
to
be

The .freq file:
be 2
to 2
not 1
or 1

and the output 
BST height: 4
BST unique words: 4
Total tokens: 6
Min frequency: 1
Max frequency: 2

