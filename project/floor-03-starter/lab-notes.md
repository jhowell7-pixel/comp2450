    1. // The Transcript
=== THE FORGEMASTER'S VAULT ===

What is your name, adventurer? Jenna

Welcome back, Jenna.
Empty molds line the walls. The Forgemaster watches, silent.
This week you press one mold to hold every list the keep remembers.

(commands:
   search <name>                 ΓÇö look up by name in bestiary or inventory
   list                          ΓÇö list the bestiary
   inventory                     ΓÇö list your inventory
   inspect <n>                   ΓÇö show the nth item in your inventory
   sort inventory by <key> [asc|desc]
                                 ΓÇö key is name, weight, or value
   benchmark [N]                 ΓÇö race the search algorithms
   benchmark sort [N] [--sorted] [--bad-pivot]
                                 ΓÇö race the sorting algorithms
   help                          ΓÇö this screen
   quit                          ΓÇö leave the dungeon)

> inventory
   1.  Rusty sword       (wt 4.0, val 5)
   2.  Healing potion    (wt 0.5, val 12)
   3.  Iron key          (wt 0.1, val 0)
   4.  Loaf of bread     (wt 0.1, val 1)
   5.  Cloak of shadows  (wt 1.5, val 80)
> list
Bone Spider   HP 6   ATK 2   weakness: fire
Cave Troll   HP 28   ATK 7   weakness: fire
Cinder Bat   HP 4   ATK 1   weakness: water
Frostmaw   HP 22   ATK 6   weakness: fire
Goblin   HP 8   ATK 2   weakness: fire
Ironclaw Bear   HP 24   ATK 5   weakness: slashing
Lich   HP 35   ATK 6   weakness: holy
Marsh Lurker   HP 18   ATK 3   weakness: fire
Necrothrall   HP 16   ATK 4   weakness: light
Ratking   HP 9   ATK 2   weakness: fire
Shadow Hound   HP 12   ATK 4   weakness: light
Skeleton   HP 10   ATK 3   weakness: blunt
Stone Sentinel   HP 30   ATK 5   weakness: blunt
Wisp   HP 3   ATK 1   weakness: holy
Wraith   HP 14   ATK 4   weakness: holy
> search Goblin
Goblin   HP 8   ATK 2   weakness: fire
> search Iron key
  Iron key  (wt 0.1, val 0)
> inspect 3
  Iron key  (wt 0.1, val 0)
> inspect 99
No such item. (index 98 out of bounds for size 5)
> sort inventory by weight
   1.  Iron key          (wt 0.1, val 0)
   2.  Loaf of bread     (wt 0.1, val 1)
   3.  Healing potion    (wt 0.5, val 12)
   4.  Cloak of shadows  (wt 1.5, val 80)
   5.  Rusty sword       (wt 4.0, val 5)

    2. // Break it -- the template error.
The thread 17232 has exited with code 0 (0x0).

    3. // Break it -- the Swallowed Scream
When you call inspect 99 you don't get any response in the console
yet you can an exception thrown in the output. The empty handler is worse 
though because if you didn't get any response at all you wouldn't
be able to properly troubleshoot.

    4. // checked vs. unchecked
So I would keep 'at()' because a player typing 'inspect 99' could acess
outside the inventory. 'Operator[]' doesn't check the index, so the program
could read invalid memory instead of throwing. Testing a few inputs does not 
prove safety because bad inputs might still trigger undefined behavior. The change
is right only when the index is guaranteed to be valid. 

    5. // why std:: exception
Without inheriting from std::exception, the catch 
    block would not be able to catch the exception thrown by at(). 
    The catch block is designed to catch exceptions of type std::exception 
    and its derived classes. If the exception thrown does not inherit from std::exception,
    it will not be caught by the catch block, leading to unhandled exceptions and potential program crashes. 
    By inheriting from std::exception, we ensure that our custom exception can be caught and handled appropriately.
