	The full benchmark sort output (paste from your terminal).
-- Race the Sorts (random input) --
  N=     10  mergeSort=   0.044 ms  quicksort=    0.031 ms  std::sort=   0.019 ms
  N=    100  mergeSort=   0.718 ms  quicksort=    0.467 ms  std::sort=   0.388 ms
  N=   1000  mergeSort=  13.298 ms  quicksort=    6.896 ms  std::sort=   5.775 ms
  N=  10000  mergeSort= 118.093 ms  quicksort=   75.859 ms  std::sort=  57.205 ms
  N= 100000  mergeSort=1316.380 ms  quicksort=  860.622 ms  std::sort= 742.412 ms


	At what inventory size does std::sort clearly pull ahead of your hand-rolled sorts? Read your table; pick a row.
-
-N=   1000  mergeSort=  13.298 ms  quicksort=    6.896 ms  std::sort=   5.775 ms
- 
			
	Run the benchmark with a pre-sorted input (the harness has a --sorted flag). Which sort gets faster? Which gets slower? Why?
-
-Both std::sort and quick sort get faster. Merge sort also gets slightly faster compared to the random-input results
-

	Quicksort with a first-element pivot on a sorted input. The harness has a --bad-pivot flag. Run these six commands and build a small table of the quicksort column:

		benchmark sort --sorted  2500      benchmark sort --sorted --bad-pivot  2500
		benchmark sort --sorted  5000      benchmark sort --sorted --bad-pivot  5000
		benchmark sort --sorted 10000      benchmark sort --sorted --bad-pivot 10000

-quicksort=   14.573 ms			quicksort*=  95.074 ms
-quicksort=   18.378 ms			quicksort*= 412.359 ms
-quicksort=   48.028 ms			quicksort*=1499.099 ms

	Each time you double N, roughly what happens to the middle-pivot time? To the first-element time? Name the growth rate of each. 
	Then, in one sentence: why is already-sorted input the worst possible case for a first-element pivot — and why is that so alarming?
-
-When N is doubled the time increases by about 2 times. Already-sorted is worst case because it causes a first-element pivot to repeat.
-

	One-paragraph reflection. If you could only ship one of the three sorts in production, which would you ship? 
	Defend your choice in terms of worst case, average case, and what the data is likely to look like.
-
-I'd personally ship std::sort because it has the fastest performance in every benchmark shown. It uses quite an 
efficient algorithm and avoids major worst-case problems.
-
