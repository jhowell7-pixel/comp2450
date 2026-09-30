1) A transcript of the demo above.

> search Goblin
  Goblin   HP 8   ATK 2   weakness: fire
> inventory
  1.  Rusty sword       (wt 4.0, val 5)
  2.  Healing potion    (wt 0.5, val 12)
  3.  Iron key          (wt 0.1, val 0)
  4.  Loaf of bread     (wt 0.1, val 1)
  5.  Cloak of shadows  (wt 1.5, val 80)
> inspect 99
  No such item. (index 98 out of bounds for size 5)
> log --oldest 5
  1.  began session as "Aric"
  2.  search Goblin — found in bestiary
  3.  inventory — listed 5 items
  4.  error: index 98 out of bounds for size 5
  (oldest first; chain length 4)
> clone hero
  -- original log (newest first) --
  1.  error: index 98 out of bounds for size 5
  2.  inventory — listed 5 items
  3.  search Goblin — found in bestiary
  4.  began session as "Aric"
  (newest first; chain length 4)
  -- cloned log (newest first) --
  1.  error: index 98 out of bounds for size 5
  2.  inventory — listed 5 items
  3.  search Goblin — found in bestiary
  4.  began session as "Aric"
  (newest first; chain length 4)
  (clone is being destroyed now)
  (clone destroyed; original event log still has 4 entries — try `log 3`)
> log 3
  1.  clone hero — copy lived and died
  2.  error: index 98 out of bounds for size 5
  3.  inventory — listed 5 items
  (newest first; chain length 5)
> selftest chain
  Phase 1 (single chain)
    allocations:  1000   deallocations:  1000   leaked:     0   OK
  Phase 2 (deep copy)
    original after copy died — forward walk:  1000   backward walk:  1000
    copy before death        — forward walk:  1000   backward walk:  1000
    allocations:  2000   deallocations:  2000   leaked:     0   OK
> quit
  The forge cools. Two chains dissolve, each by its own hand.


2) Break a prev pointer on purpose. In push_back, omit the line that sets new_node->prev = tail_;. 
Run log --oldest 5. Describe exactly what gets printed — and explain in one sentence which step of the 
backward walk reads the bad pointer. Restore the line.
> So the logs tries to print it, but since the pointer is not set correctly, it will most likely print errors. 
    The step of the backward walk that reads the bad pointer is when it tries to access the prev pointer of the last node in the chain.

3) Try the shallow copy. Replace your Chain(const Chain&) body with a literal field-by-field copy: head_ = other.head_; tail_ = other.tail_; size_ = other.size_;. 
 Run selftest chain. Paste the failure. Which exact line of which destructor was the second delete on the same node? Restore the deep copy.

4) Compare copy-and-swap with the explicit form. Implement operator= both ways on a branch. Paste both functions. 
 In two sentences: which one are you more confident you can write correctly under exam pressure, and why?

> I am more confident writing the copy-and-swap form because it is short, hard to get wrong, and provides strong 
 exception-safety by reusing the copy constructor and a single `swap`.

5) Why doesn’t a singly-linked list with a tail_ pointer give you O(1) pop_back? Answer in two sentences. 
 (Hint: after you delete the tail, what has to point to nullptr, and what would it take to find it?)

 > After deleting the tail node you must update the previous node’s `next` to `nullptr`; finding that 
 previous node requires walking from `head_` (or maintaining extra pointers), so `pop_back` is O(n) in a 
 singly-linked list with only a `tail_` pointer. Without a `prev` pointer you cannot update the predecessor in O(1).

6)One-paragraph reflection. You now have both halves of the Rule of Three implemented. State the rule in one sentence. 
Then: when would you reach for the Rule of Zero instead — and why does Chain<T> not qualify?

> The Rule of Three: if a class defines a destructor, copy constructor, or copy assignment operator, it likely needs all three 
because it manages non-trivial resources. 