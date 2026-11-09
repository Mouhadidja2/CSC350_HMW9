// HW8 reference solution: PathLab.cpp
//
// Each function here DEFINES (implements) a function declared in PathLab.hpp.
// The signatures must match the header exactly.

#include "PathLab.hpp"
#include <fstream>   // std::ofstream (write files), std::ifstream (read files)
#include <sstream>   // std::ostringstream (collect a whole file into a string)

namespace minigit {

// ---------------------------------------------------------------- Issue 1
std::filesystem::path metadataDirectory(const std::filesystem::path& root) {
    // operator/ joins two path parts with the correct separator:
    // "course/repo" / ".minigit"  ->  course/repo/.minigit   (Linux, macOS)
    //                             ->  course\repo\.minigit   (Windows)
    //
    // Common mistakes:
    //   root.string() + "/.minigit"   (hard-codes '/', breaks on Windows)
    //   root / "/.minigit"            (a leading '/' makes the right side
    //                                  "rooted", which REPLACES root: /.minigit)
    return root / ".minigit";
}

// ---------------------------------------------------------------- Issue 2
std::filesystem::path headFile(const std::filesystem::path& root) {
    // Reuse Issue 1 instead of typing ".minigit" again. If the folder name
    // ever changes, only metadataDirectory needs to change.
    return metadataDirectory(root) / "HEAD";
}

// ---------------------------------------------------------------- Issue 3
bool writeTextFile(const std::filesystem::path& file,
                   const std::string& text,
                   std::string& errorMessage) {
    // Start from a clean output parameter, so an old message never leaks
    // into a successful call.
    errorMessage.clear();

    // parent_path() of "tmp/new/nested/note.txt" is "tmp/new/nested".
    // A bare file name like "note.txt" has an EMPTY parent: nothing to create.
    const std::filesystem::path parent = file.parent_path();
    if (!parent.empty()) {
        // create_directories makes every missing folder in the chain,
        // like "mkdir -p". It does nothing if they already exist.
        //
        // The std::error_code version reports failure in 'error' instead of
        // throwing an exception, which fits our bool + message style.
        std::error_code error;
        std::filesystem::create_directories(parent, error);
        if (error) {
            errorMessage = error.message();
            return false;
        }
    }

    // Opening an ofstream creates the file, or empties an existing one.
    // "if (!output)" asks the stream: did opening fail?
    std::ofstream output(file);
    if (!output) {
        errorMessage = "Could not open file for writing: " + file.string();
        return false;
    }

    output << text;
    if (!output) {                 // did the write itself fail (disk full...)?
        errorMessage = "Could not write to file: " + file.string();
        return false;
    }

    // No close() needed: 'output' closes the file automatically when the
    // function ends (RAII: the object cleans up after itself).
    //
    // Note: this opens the file in TEXT mode. On Windows, text mode turns
    // "\n" into "\r\n" on disk. MiniGit must store exact bytes, so next
    // week's FileSystem class adds std::ios::binary.
    return true;
}

// ---------------------------------------------------------------- Issue 4
bool readTextFile(const std::filesystem::path& file,
                  std::string& text,
                  std::string& errorMessage) {
    errorMessage.clear();

    std::ifstream input(file);
    if (!input) {                  // missing file, no permission, ...
        errorMessage = "Could not open file for reading: " + file.string();
        return false;
    }

    // Read the WHOLE file in one step: copy the stream's buffer into a
    // string stream, then take its string.
    //
    // Why not a loop with std::getline? getline removes each '\n', so the
    // text you get back is not exactly the text that was written.
    std::ostringstream contents;
    contents << input.rdbuf();
    if (input.bad()) {
        errorMessage = "Could not read file: " + file.string();
        return false;
    }

    text = contents.str();         // only touch the output on success
    return true;
}

} // namespace minigit
