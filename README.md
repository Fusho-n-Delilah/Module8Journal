# Module 8 Journal
What was the problem you were solving in the projects for this course?
- The problems we were solving in the course was learning about various data structures and sorting algorithms, how to implement them, and choosing data structures for the problem we were trying to solve. For example in project 2 we had to read in data from a CSV file containing course information, sort that information, and print an ordered list. I chose a Binary Search Tree to accomplish this task. 

How did you approach the problem? Consider why data structures are important to understand.
- With Project 2 I approached the problem by first looking at what the main functionality/problem to be solved was. In this case it was listing the courses in alphanumerical order while keeping the runtime as efficient as possible. Although one could store everything in a list, and sort the list when needed... Even a quicksort would be slower than an inorder BST traversal. Thus, by knowing the data structures, I was able to choose the appropriate one for the job.

How did you overcome any roadblocks you encountered while going through the activities or project?
- I overcame roadblocks by going back and reading the relevant sections. Occasionally I would look at code examples from other sources to see if there was modern c++ algorithms that I should implement. Having familiarity with these data structures from a high level language such as Java, it was easier to destructure the logic needed to be implemented

How has your work on this project expanded your approach to designing software and developing programs?
- I work professionally as a Software Developer. It has allowed me to consider other datastructures in my work. Sometimes to get in the flow state it is often easiest to start with a dynamic list like a vector or arraylist. Especially considering most frameworks can quickly create JSON payloads from said structure. However, if this data needs to be sorted. It may be easier to store it in a binary search tree, and then populate a list from an inorder traversal. It's also made me consider immutable sets and other data structures more in my day to day depending on what problem I'm solving.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
- The way we wrote programs in this course was much cleaner than I typically see. Every function served one purpose. I've definitely been writing more helper functions, commenting code more, and breaking code out as needed to reduce code complexity.
