// COMP 2450 — Floor 1 starter
// bestiary/Search.cpp — YOU implement this file.
//
// Four functions to write. Read Search.h for their contracts.
//
// The big idea this week: the same question ("is X in the list?") has
// three implementations with three VERY different Big-O costs. You will
// write all three, race them in benchmark, and then argue — in a commit
// message — which one the rest of the game should use. The code is easy.
// The thinking is the point.
//
// Tips for the Unsorted Lich:
//   * binarySearch (and binarySearchRecursive) only work if the bestiary
//     is sorted by name.
//   * main.cpp already calls sortBestiary() right after loading,
//     so you can assume the precondition holds when these run.
//   * If you ever doubt, scan the vector and assert it is sorted.
//
// Submit when:  search Goblin returns the goblin's stats and search Ghost
//               reports "no such creature." Then run benchmark and capture
//               the output for your lab-notes.md.
#include "Search.h" 
#include <algorithm>
#include <cassert>


namespace dungeon {
    const Monster* linearSearch(const std::vector<Monster>& bestiary,
        const std::string& name) {
        for (const auto& m : bestiary) {
            if (m.name == name) {
                return &m;
            }
        }
        return nullptr;
    }
    const Monster* binarySearch(const std::vector<Monster>& bestiary,
        const std::string& name) {
        
        assert(std::is_sorted(bestiary.begin(), bestiary.end(), [](const Monster& a, const Monster& b) {
            return a.name < b.name;
        }));

        std::size_t low = 0;
        std::size_t high = bestiary.size();
        // time to loop!
        while (low < high) {
            // while there's still one element in our window when low == high the window is empty
            // 1. comput the middle
            std::size_t mid = low + (high - low) / 2;
            // if we have large size_t values...low + high could overflow before we divide
            // 2. look at the element at mid
            const std::string& here = bestiary[mid].name;
            // 3. decision time...
            if (here == name) return &bestiary[mid];
            if (here < name) low = mid + 1;
            else high = mid;
            // where did here and name come from? here is the name of the monster at mid, name is the name we are looking for
        }
        return nullptr;
    }
    namespace {
        const Monster* binSearchRec(
            const std::vector<Monster>& bestiary, const std::string& name, std::size_t low, std::size_t high) {
            // base case first!
            if (low >= high) return nullptr;
            // recursive case!
            std::size_t mid = low + (high - low) / 2;
            const std::string& here = bestiary[mid].name;
            if (here == name) return &bestiary[mid];
            else if (here < name) {
                return binSearchRec(bestiary, name, mid + 1, high);
            }
            else {
                return binSearchRec(bestiary, name, low, mid);
            }
        }
    }
    const Monster* binarySearchRecursive(const std::vector<Monster>& bestiary,
        const std::string& name) {
        return binSearchRec(bestiary, name, 0, bestiary.size());
        // TODO Floor 1 (Fri): same contract as binarySearch, but recursive.
        //   Recommended pattern: write a static helper in this file with extra
        //   (low, high) parameters, and have this public function call it with
        //   the initial range. Same precondition: bestiary must be sorted.
        //
        // Think before you type:
        //   - Every recursion needs a BASE CASE and a RECURSIVE CASE. What is
        //     the smallest range where you already know the answer without
        //     looking further? That is your base case.
        //   - Convince yourself, for each recursive call, that the new range
        //     is a STRICT SUBSET of the old one. If it isn't, you will recurse
        //     until the stack blows up. (Try it at N=100,000 if curious.)
        //   - Why static for the helper? It has nothing to do with OOP here.
        //     Look up "internal linkage" — it keeps the helper private to this
        //     .cpp, so two files can have helper(...) without a link error.
        //   - After it works: run benchmark. Does the recursive version cost
        //     more per call than the iterative one? A little? A lot? Why might
        //     that be? Write the answer in lab-notes.md.
    }
    const Monster* findMonster(const std::vector<Monster>& bestiary,
        const std::string& name) {
        // TODO Floor 1: pick ONE of the three searches above and delegate.
        //
        // Think before you type:
        //   - At the real bestiary's size (15 monsters), does it matter which
        //     you pick? Run benchmark at N=10 and look at the microseconds.
        //   - At N=100,000, does it matter? By how much?
        //   - This is a JUDGMENT, not a fact. Whatever you pick, write WHY in
        //     your commit message. That reasoning is the graded artifact.
        return binarySearchRecursive(bestiary, name);
    }
}