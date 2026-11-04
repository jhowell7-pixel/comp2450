1) A transcript of the demo above (your own hero name).

2) The lean, by hand. On paper, insert 1, 2, 3, 4, 5, 6, 7 into an empty BST in that order and draw the stick. 
Write the balance factor at the root (1) and at the middle node (4), counting an empty side as −1. Then draw the balanced tree on
the same seven values (root 4). One sentence: same values, same rule — what is different, and why does it change how many nodes find has to look at?

3) A rotation, by hand. Insert 3, 5, 8 in that order: 3 at the top, 5 as its right child, 8 as 5’s right child. 
Do a left rotation at 3. Draw the result and write the in-order walk before and after. Confirm they match. One sentence: 
why does “in-order unchanged” mean the result is still a valid BST?

4) Which rotation? For each unbalanced root, name the rotation rebalanceAt would apply and why: 
(a) a left-heavy root (balance factor +2); 
(b) a right-heavy root (−2). 
Then the case one rotation can’t fix: insert 1, 3, 2 (so 2 is 3’s left child). 
Do one left rotation at 1 and draw what you get. Is it balanced now? 
One sentence: what does a real AVL tree do instead? (You do not have to code it.)

5) The comparison. 
Run benchmark balance. 
Paste the table. 
(Your microseconds will not match the page; the heights will.) 
In two sentences, in your own words: the plain BST and the std::set saw the identical sorted input — 
why did one become a stick and the other stay short?
What is std::set doing on every insert that your BST is not?

6) One-paragraph reflection. 
You stopped one step short of a self-balancing tree on purpose. 
Was that the right call? When, if ever, would you write the balancing yourself 
instead of using std::set/std::map? And: you’ve built five pointer structures and are 
about to start using one you didn’t write. What do you gain, and what do you give up?