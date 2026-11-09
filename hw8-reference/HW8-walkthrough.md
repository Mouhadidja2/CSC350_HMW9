# HW8 walkthrough: PathLab reference solution

Read the three files in this order: `include/PathLab.hpp`, `src/PathLab.cpp`, `tests/PathLabTests.cpp`. The comments explain each choice.

## Five ideas to take away

1. **A `path` is a value, not a file.** `root / ".minigit"` only builds a name. Nothing is created until you call a function like `create_directories` or open a stream.
2. **Join with `/`, never with `+`.** `/` inserts the right separator for each platform. A part that starts with `/` replaces everything on its left.
3. **Header declares, `.cpp` defines.** The signature in both files must match exactly, and both are inside `namespace minigit`.
4. **`const T&` for inputs, `T&` for outputs.** Inputs are passed by const reference (no copy, no change). `errorMessage` and `text` are output parameters, so they are plain references.
5. **Test both the happy path and the failure path,** in a temporary folder you remove at the end.

## Common mistakes we saw

| Mistake | Why it is wrong | Fix |
| --- | --- | --- |
| `root.string() + "/.minigit"` | Hard-codes `/`; the test compares parts, so Windows output differs | `root / ".minigit"` |
| `metadataDirectory(root) / "/HEAD"` | A rooted right side replaces the left side: the result is `/HEAD` | `/ "HEAD"` |
| Typing `".minigit"` again in `headFile` | Two places to change later | Reuse `metadataDirectory(root)` |
| Reading with a `getline` loop | Drops every `\n`, so the text is not the same | `contents << input.rdbuf()` |
| Not calling `create_directories` | Writing to `new/nested/note.txt` fails | Create `parent_path()` first |
| Comparing paths as strings in tests | Fails on Windows (`\` vs `/`) | Compare `path` values |
| Leaving test files behind | The next run finds old files | `remove_all(tempRoot)` |
| Merging with red CI | Breaks `main` for the whole team | Fix CI first, or Revert |

## How this connects to next week

| HW8 function | Becomes |
| --- | --- |
| `metadataDirectory(root)` | `RepositoryPaths::metadataRoot()` (the root is stored in the class) |
| `headFile(root)` | `RepositoryPaths::headFile()` |
| `writeTextFile(...)` | `FileSystem::write(...)`, in binary mode, throwing on failure |
| `readTextFile(...)` | `FileSystem::read(...)`, in binary mode, throwing on failure |
