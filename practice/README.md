# Practice: paths, files, classes and exceptions

Eight short exercises that prepare you for `RepositoryPaths` and `FileSystem`. Do them in order. Exercises 1 to 4 are on paper (or in a comment); exercises 5 to 8 are small programs in this folder.

Build and run the programs from this folder:

```
cmake -S . -B build
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Each program prints `PASS` or `FAIL` for every check. Until you finish an exercise, its program fails. That is expected.

---

## Exercise 1. Predict the output (5 min)

Write down what each line prints, then check with a small program. Assume Linux.

```cpp
using std::filesystem::path;
std::cout << (path("repo") / ".minigit" / "HEAD").generic_string();     // a
std::cout << (path("repo") / "/HEAD").generic_string();                 // b
std::cout << path("docs/notes.txt").filename().string();                // c
std::cout << path("docs/notes.txt").parent_path().string();             // d
std::cout << path("notes.txt").parent_path().empty();                   // e  (prints 1 or 0)
std::cout << path("notes.txt").extension().string();                    // f
```

## Exercise 2. Find the bug: lost newlines (5 min)

This function is supposed to return the file's exact text. A file containing `"a\nb\n"` comes back as `"ab"`. Why? Fix it.

```cpp
std::string readAll(const std::filesystem::path& file) {
    std::ifstream input(file);
    std::string line, text;
    while (std::getline(input, line)) {
        text += line;
    }
    return text;
}
```

## Exercise 3. Find the bugs: two path mistakes (5 min)

Both tests below fail on Windows, and the second one fails everywhere. Find both bugs.

```cpp
std::filesystem::path metadataDirectory(const std::filesystem::path& root) {
    return root.string() + "/.minigit";
}
std::filesystem::path headFile(const std::filesystem::path& root) {
    return metadataDirectory(root) / "/HEAD";
}
```

## Exercise 4. Fill in the blanks (5 min)

Complete the missing lines so the function creates missing folders, writes the text, and reports failure.

```cpp
bool save(const std::filesystem::path& file, const std::string& text) {
    if (______________________) {                       // (1) only if there is a parent folder
        std::filesystem::______________(file.parent_path());   // (2) make all missing folders
    }
    std::ofstream output(file);
    if (______) {                                       // (3) did opening fail?
        return false;
    }
    output << text;
    return ______________;                              // (4) true only if writing worked
}
```

---

## Exercise 5. Add a new path function (10 min) — `ex5_index_file.cpp`

`metadataDirectory` is given. Write `indexFile(root)`, which returns `root/.minigit/index.txt`, by reusing `metadataDirectory`. Then add one more check of your own for the root `"course/team/repo"`.

## Exercise 6. Write the tests (10 min) — `ex6_write_tests.cpp`

`stageFile(root, name)` is already written and correct. Write at least three checks: a top-level file, a file in a sub-folder, and that `filename()` is kept. The program fails until it has at least three passing checks.

## Exercise 7. From functions to a class (15 min) — `ex7_class.cpp`

The class `RepoLayout` is declared for you. Write the definitions of its constructor and three member functions below the class (the `RepoLayout::...` part). This is exactly how `RepositoryPaths` works.

## Exercise 8. From bool + message to an exception (15 min) — `ex8_exceptions.cpp`

Write `readOrThrow(file)`: it returns the whole file, or throws `std::runtime_error` with the file name when the file cannot be opened. Then finish `main`'s `try`/`catch` so a missing file prints a friendly message instead of crashing. This is exactly how `FileSystem::read` works.
