Commit floor-01/lab-notes.md to your project repo with:

	1. The full benchmark output (paste from your terminal).

=== THE SCRYING WELL ===

What is your name, adventurer? Jenna

Welcome back, Jenna.
The water is black. It shows what you name aloud.
(commands: search <name>, list, benchmark [N], quit)

> benchmark

-- Race the Bestiary (1000 iterations per cell) --
  N=     10  query=last    linear=     0.395 us  binary=   0.968 us  recursive=   0.200 us
  N=     10  query=absent  linear=     0.285 us  binary=   0.953 us  recursive=   0.212 us
  N=    100  query=last    linear=     3.335 us  binary=   5.669 us  recursive=   0.456 us
  N=    100  query=absent  linear=     2.569 us  binary=   5.074 us  recursive=   0.432 us
  N=   1000  query=last    linear=    41.194 us  binary=  46.918 us  recursive=   0.435 us
  N=   1000  query=absent  linear=    19.674 us  binary=  31.339 us  recursive=   0.479 us
  N=  10000  query=last    linear=   279.998 us  binary= 377.483 us  recursive=   1.041 us
  N=  10000  query=absent  linear=   310.362 us  binary= 416.027 us  recursive=   1.024 us
  N= 100000  query=last    linear=  2669.181 us  binary=4281.288 us  recursive=   1.172 us




	2. At what bestiary size does binary search start to clearly beat linear? Read your table; pick a row.
	
N=  10000  query=last    linear=   279.998 us  binary= 377.483 us  recursive=   1.041 us

	3. For N=10, which is faster, and why might that surprise a beginner?

Linear search is faster. This could suprise a beginner because they might expect binary search to always be faster than linear search, 
but for small datasets, the overhead of setting up the binary search can make it slower than a simple linear search.

	4. What happens if you call binarySearch on the unsorted bestiary? Try it: comment out the sortBestiary(bestiary); 
	   call in main.cpp, rebuild, search a few names. Restore sortBestiary when done. Write what you saw and why.
	
When the bestiary is unsorted, binary search gives incorrect results for some searches or fails to find names that are present. Binary search depends on the data 
being sorted because each comparison determines which half of the list to search next. Without sorting, those decisions do not reliably point toward the correct location. 
The sortBestiary(bestiary); call needs to stay in the program before using binarySearch.
	
	5. Iterative vs. recursive — do their per-call times differ in your benchmark? By how much? Why?

Yes. The recursive search is faster than the iterative search in every row of the benchmark. For example, at N=10,000 with the last query, 
iterative search takes 279.998 us while recursive search takes 1.041 us. The difference is 278.957 us per 1,000 iterations, or about 0.279 us per individual call.