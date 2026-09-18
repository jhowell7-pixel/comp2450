# Trial II — *The Critique*

*Warden of the Foundations · Midterm 1 · 15 %*

This trial **requires** you to use an LLM. You will paste the prompt and the reply, then critique what you got. Reading and judging AI output is part of the job now; we are practicing it on purpose.

---

## The prompt

Open Claude (or your LLM of choice) and paste **this exact prompt**:

> *Write a C++ function template that returns the largest element of a `std::vector<T>`. Handle the case where the vector is empty. Briefly explain your design choices.*

Tell us which tool you used and the date:

- **Tool:** Gemini
- **Date of the conversation:** 2026-09-17

---

## The LLM's reply

Paste the **full reply**, code and prose. Use a fenced code block for the code. Do not edit the reply — we want to see what you actually got.

```cpp
#include <vector>#include <algorithm>#include <optional>
template <typename T>std::optional<T> find_largest(const std::vector<T>& vec) {
    if (vec.empty()) {
        return std::nullopt;
    }
    
    auto max_it = std::max_element(vec.begin(), vec.end());
    return *max_it;
}
```

Here is a modern C++ function template to find the largest element in a std::vector, along with a clean way to handle empty vectors.



## Design Choices

* std::optional<T> for Empty Handling: Returning std::optional (introduced in C++17) is the cleanest way to handle an empty vector. It avoids the overhead of throwing exceptions for a predictable control flow and prevents the need to return a risky "magic value" (like -1 or 0) which might actually be a valid element in the vector.
* Pass by Const Reference: The vector is passed as const std::vector<T>&. This avoids copying the entire vector, ensuring the function is efficient ($O(1)$ space complexity) while guaranteeing that the original data is not modified.
* std::max_element: Instead of writing a manual for loop, the function uses the standard library algorithm. This is highly optimized, expressive, and works out of the box for any type T that implements the < operator.

If you want to expand this template, let me know if you would like to:

* Support custom comparison functions (e.g., sorting objects by a specific property)
* Avoid copying the element on return by returning an optional iterator or pointer instead of a value
* See an example of how to call and unpack this function in a main() block




---

## My critique  *( ≥ 150 words )*

Your critique must read like an engineer reviewing a colleague's pull request — specific, technical, and naming exactly what the LLM did. A vague critique ("looks fine to me, but it could be better") is *not* full credit even if the LLM's code was great.

Address each of these:

- **Compile.** Did you actually try to compile and run the code? On what types? What happened?
- **Empty case.** What does the empty-vector case actually do in this code? Is the LLM's choice reasonable? Is it different from what *you* would have chosen?
- **Requirements on `T`.** What does the code require of `T`? What happens if you instantiate it with a type that doesn't support `<` (e.g., a custom struct)?
- **Const-correctness.** Pass by value or by reference? Return by value or by reference? Would you change either?
- **`std::max_element`?** Did the LLM cheat by using the algorithm header, or did it write the loop? Which would *you* have shipped, and why?
- **One concrete improvement.** Name one specific change you would make before merging this into a real project. Not "make it better" — a concrete code change.

In regards to compiling, I attempted to run the code but it did not compile due to "Build Errors." 
So the empty case returns a nullopt which is something I haven't done before so I'd have probably changed that to throw an exception.
To be completely honest with this line of code, I do not understand it.
I'd say pass by reference because it is more efficient and I would return by value because it is a simple type.
I don't believe the LLM cheated but with the code it gave me, it is hard to understand.
I would change the return type to throw an exception instead of returning a nullopt.