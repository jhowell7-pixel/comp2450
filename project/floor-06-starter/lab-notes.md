1. A transcript of the demo above (with your own hero name).

-- 
=== THE HALL OF ECHOES ===

What is your name, adventurer? Jenna

Welcome, Jenna.
Cantor Resh stands at the lectern at the centre of the hall, eyes half-closed.
He repeats whatever you say last. Speak carefully; the hall remembers in stacks.

(commands:
   search <name>                 ΓÇö look up by name in bestiary, inventory, OR event log
   list                          ΓÇö list the bestiary
   inventory                     ΓÇö list your inventory
   inspect <n>                   ΓÇö show the nth item in your inventory
   take <name>                   ΓÇö add a small item by that name to your inventory
   sort inventory by <key> [asc|desc]
                                 ΓÇö key is name, weight, or value
   undo                          ΓÇö reverse the most recent mutating command
   lint <text>                   ΓÇö check that brackets/parens/braces in <text> balance
   log [n]                       ΓÇö show the last n events, newest first
   log --oldest [n]              ΓÇö show the first n events, oldest first
   clone hero                    ΓÇö deep-copy the hero, print both logs, let the copy die
   selftest chain                ΓÇö Chain<T> leak + deep-copy harness
   selftest iterator             ΓÇö Chain<T>::iterator harness
   selftest stack                ΓÇö Stack<T> push/pop/top/LIFO harness
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   benchmark log [N]             ΓÇö race Chain::push_front vs vector insert(begin)
   battle warden                 ΓÇö face the Warden of the Foundations
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> selftest stack
  empty Stack<int>: size==0 && empty(): OK
  push(7): size==1 && top()==7: OK
  push 1,2,3: size==3 && top()==3 (LIFO): OK
  after pop(): size==2 && top()==2: OK
  drain to empty: size==0 && empty(): OK
  all phases OK
> lint ({a} (b) [c])
  balanced
> lint ({)}
  not balanced
> lint hello (world
  not balanced
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> take Lantern
  Taken: Lantern  (wt 0.1, val 1)
> sort inventory by weight
   1.  Iron key          (wt 0.1, val 0)
   2.  Loaf of bread     (wt 0.1, val 1)
   3.  Lantern           (wt 0.1, val 1)
   4.  Healing potion    (wt 0.5, val 12)
   5.  Cloak of shadows  (wt 1.5, val 80)
   6.  Rusty sword       (wt 4.0, val 5)
> undo
Undid: sort inventory by weight
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
   6.  Lantern           (wt 0.1, val 1)
> undo
Undid: take Lantern
> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> undo
Nothing to undo.
> quit
The cantor falls silent. The last echo decays. The hall is quiet.
--

2. The ADT-vs-DS one-pager. In two short paragraphs: define abstract data type and data structure in your own words, 
then state which one Stack is and which one Chain is. End with one sentence on why Stack<T> as an adapter over Chain<T> reinforces the distinction.

-- 
An abstract data type (ADT) is a logical blueprint. It only shows what the data does, not how it works. 
A data structure is the actual physical layout. It controls how the data is stored in memory.
A Stack is an abstract data type. A Chain is a data structure.
--

3. The cheap swap. In hero/Stack.h, swap the storage underneath your stack from Chain<T> to std::vector<T>. 
Six small edits, all in that one file: #include "Chain.h" → #include <vector>; Chain<T> chain_; → std::vector<T> chain_;; 
push_front → push_back; pop_front → pop_back; and head()->data → back() in both top() overloads. Leave size() and empty() alone. 
Build, run selftest stack, and paste the output. Then run benchmark log 1000 (the Floor 4 prepend bench — give it the 1000; without a 
number it runs a sweep that takes many minutes in a Debug build). Paste that too. Does the benchmark change? Why or why not? (Hint: open 
hero/ChainBench.cpp and look for the word Stack.) Restore Stack.h when you’re done.

-- 
No, changing Stack.h to use std::vector does not affect ChainBench.cpp. ChainBench explicitly times Chain::push_front vs std::vector::insert(begin). 
Replacing Stack's underlying container with std::vector only affects Stack users; ChainBench measures container front-insert performance directly and
will show the same large difference regardless of Stack.h.
--

4. An empty stack call. Paste this block at the very top of main() in main.cpp, right after int main() {:

{   // LAB 6 ITEM 4 -- temporary
    Stack<int> s;
    std::cout << "about to call top() on an empty stack...\n";
    std::cout << "top() = " << s.top() << "\n";
    std::cout << "survived\n";
}
Build and run. Paste what you see — the console text, the exit code Visual Studio prints, or the debugger’s message. 
Then guard it: replace the top() line with if (!s.empty()) std::cout << "top() = " << s.top() << "\n"; else std::cout << "stack is empty\n"; and 
run again. In one sentence: what does the stack ADT not promise (a queue, a list, and a map don’t promise it either), and what should callers always do? 
Delete the block when you’re done.

--
>------ Build started: Project: CMakeLists, Configuration: Debug ------
  [1/2] Building CXX object CMakeFiles\the_descent.dir\main.cpp.obj
  FAILED: [code=2] CMakeFiles/the_descent.dir/main.cpp.obj 
  C:\PROGRA~1\MICROS~4\18\COMMUN~1\VC\Tools\MSVC\1451~1.362\bin\Hostx64\x64\cl.exe  /nologo /TP   /DWIN32 /D_WINDOWS /GR /EHsc /Zi /Ob0 /Od /RTC1 -std:c++17 -MDd /W4 /showIncludes /FoCMakeFiles\the_descent.dir\main.cpp.obj /FdCMakeFiles\the_descent.dir\ /FS -c C:\Users\jenna\OneDrive\Documents\GitHub\comp2450aa\project\floor-06-starter\main.cpp
C:\Users\jenna\OneDrive\Documents\GitHub\comp2450aa\project\floor-06-starter\main.cpp(63): error C2447: '{': missing function header (old-style formal list?)
  ninja: build stopped: subcommand failed.

  It does not promise a queue.
--


5. One recursive function, one stack. Here is Floor 1’s recursive binary search (from bestiary/Search.cpp), rewritten to search a std::vector<int>. 
Paste it into main.cpp above int main(), along with a Range struct:

int binSearchRec(const std::vector<int>& v, int target, int lo, int hi) {
    if (lo >= hi) return -1;
    int mid = lo + (hi - lo) / 2;
    if (v[mid] == target) return mid;
    if (v[mid] <  target) return binSearchRec(v, target, mid + 1, hi);
    return                       binSearchRec(v, target, lo,      mid);
}

struct Range { int lo, hi; };
Now write int binSearchStack(const std::vector<int>& v, int target) right below it — the same algorithm, with no recursion, 
using a Stack<Range>. The shape: push the starting range {0, (int)v.size()}; then, while the stack isn’t empty, read the top(), pop() it, 
and do what one recursive call would have done — except where the recursive version calls itself, you push the new range instead. 
Test both at the top of main():

{   // LAB 6 ITEM 5 -- temporary
    std::vector<int> v = {2, 5, 8, 13, 21, 34, 55};
    for (int t : {2, 13, 55, 4, 99}) {
        std::cout << t << ": recursive=" << binSearchRec(v, t, 0, (int)v.size())
                  << "  stack=" << binSearchStack(v, t) << "\n";
    }
}
Paste your binSearchStack and the output (both columns should match). In two sentences: 
what does the explicit-stack version show that the recursive one hides? (Bonus: what is the most Ranges your stack ever holds at once, and why?) 
Delete the temporary code when you’re done.

-- 
 The explicit-stack version makes the ranges and their lifetimes visible.
--

6. One-paragraph reflection. You wrote four one-line methods this week (top() came written). What did you spend the rest of class time on, 
and why was that the right ratio? Compare to Floor 4, when you wrote a destructor, a copy ctor, an operator=, and a Rule-of-Three discussion in 
roughly the same amount of class time.

-- 
I spent most of class just listening and taking notes to further learn about the new things this week.
--