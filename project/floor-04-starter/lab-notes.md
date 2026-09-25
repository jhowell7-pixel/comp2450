1. A transcript of the demo above. Paste it from your terminal.

=== THE CHAIN VAULT ===

What is your name, adventurer? Jenna

Welcome, Jenna.
The Warden's gate stands open behind you. Mavren waits at the chain.
Type `log` at any time to see what the chain remembers.

(commands:
   search <name>                 ΓÇö look up by name in bestiary or inventory
   list                          ΓÇö list the bestiary
   inventory                     ΓÇö list your inventory
   inspect <n>                   ΓÇö show the nth item in your inventory
   sort inventory by <key> [asc|desc]
                                 ΓÇö key is name, weight, or value
   log [n]                       ΓÇö show the last n events, newest first
   selftest chain                ΓÇö run the Chain<T> leak-check harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> search Goblin
Goblin   HP 8   ATK 2   weakness: fire
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> sort inventory by value desc
   1.  Cloak of shadows  (wt 1.5, val 80)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Rusty sword       (wt 4.0, val 5)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Iron key          (wt 0.1, val 0)
> inspect 99
No such item. (index 98 out of bounds for size 5)
> log 8
  1. error: index 98 out of bounds for size 5
  2. sort inventory by value desc
  3. inventory ΓÇö listed 5 items
  4. search Goblin ΓÇö found in bestiary
  5. began session as "Jenna"
 (newest first; chain length 5)
> benchmark log 100000
  N= 100000   Chain::push_front =   203.51 ms   Bag::insert(begin) = 958531.36 ms
> selftest chain
  Chain<int> allocations:  1000   deallocations:  1000   leaked:     0   OK
> quit
The forge cools. The chain dissolves link by link.


2. Comment out your destructor body so it does nothing. Run selftest chain again. 
Paste the output. How many nodes leaked? Restore the destructor and confirm the count returns to zero.

> selftest chain
  Chain<int> allocations:  1000   deallocations:     0   leaked:  1000   LEAK ΓÇö implement ~Chain() / clear()

  Over 1000 nodes leaked. 

3. Try to copy a chain. Add this two-liner to main.cpp somewhere harmless and try to compile it: Chain<int> a; a.push_front(1); Chain<int> b = a;. 
Paste the compiler error. Which line of Chain.h is the compiler pointing at? In one sentence, explain why the compiler refuses — 
what would go wrong at end-of-program if it had let you?

  error C2280: 'dungeon::Chain<int>::Chain(const dungeon::Chain<int> &)': attempting to reference a deleted function

  The compiler points to the class declaration (Class Chain) where the data members are declared. 


4. Time push_front against insert(begin()). Paste your benchmark log 100000 output. 
Both inserts do “the same thing” — put the new element at the front. Why does the vector version cost ~1000× more for 
N = 100,000? Answer in terms of what std::vector::insert(begin()) is physically doing to memory.

> benchmark log 100000
  N= 100000   Chain::push_front =   203.51 ms   Bag::insert(begin) = 958531.36 ms

  The vector version is about 1000× slower because insert(begin()) has to shift every existing element one position to the right 
  in memory before adding the new element. Doing this 100,000 times causes a huge amount of copying. push_front in the chain only 
  changes a few pointers, so it is much faster.

5. One-paragraph reflection. Mavren keeps the bestiary in a Bag<Monster> but the event log in a 
Chain<std::string>. Defend her choice for each container — what access pattern does each face, and 
what would go wrong if you swapped them?

Mavren uses a Bag<Monster> for the bestiary because she needs fast access to monsters by position. She uses 
a Chainstd::string for the event log because events are often added to the front or back. Swapping them would 
make the bestiary slower to access and make adding new events to the log more expensive.