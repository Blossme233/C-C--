In the quadratic probing main function(testing function). 
1.If it is keeping printing data. It is detecting collisions and printing the integer that is being checked or whose slot is being found. You can remove the print statement if you want to.
This is a rough idea how it works.

Lets say we have this array with 5 elements
0 0 0 0 0
Our data set is
6 7 3 8 5
Now what will happen is
6 will get placed and then maybe 7 will get placed and then 3. So probably that's how our array will look:
6 0 3 8 7
Now, 5 needs to be placed somewhere. In chaining or linear probing there are not big jumps but here it is. 5 will keep on jumping until it finds the free space 0. These are just 5 digits. Imagine how it will perform when there are millions of them.

2. If it stucks somewhere, it is just operating the dataset. Quadratic probing is extremely slow specially on a large data set. It can go on for minutes if the collisions are not resolved. In this case where the data set is so huge, it will keep on checking for a free slot and most of the times it will not be empty. The traversing will continue until a free slot is found. This is the con of quadratic probing. It is quite slow.