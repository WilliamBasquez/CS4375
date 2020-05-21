William Basquez
CS 4375
MW 3:00PM - 4:20PM
Lab 1 - Context Swapping

Results after running program 10 times, each time iterating 100 'cycles'
Run time #	Average swap time (in ms)
   1			0.0000373000
   2			0.0000345000
   3			0.0000358000
   4			0.0000346000
   5			0.0000334000
   6			0.0000313000
   7			0.0000307000
   8			0.0000354000
   9			0.0000307000
   10			0.0000327000


The results from this simple 10 trials are:
Avg context swap time: 0.0000336399 ms
variance: 5.16933E-12 ms

Results after running program 10 times, each time iterating 200 'cycles'
Run time #	Average swap time (in ms)
   1			0.0000327000
   2			0.0000320000
   3			0.0000324000
   4			0.0000336000
   5			0.0000334000
   6			0.0000334000
   7			0.0000316000
   8			0.0000314000
   9			0.0000323000
   10			0.0000343000

avg. context swap time: 0.0003271
variance: 1.05067E-12 ms

In these two experiments, the variance is really low, meaning that the actual time it takes to swap processes is not that far from what I calculated, and in relation with both average times, the variance is 4.30594E-8, which is still really really accurate from the actual time.
