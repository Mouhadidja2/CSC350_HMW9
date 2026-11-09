// HW8 reference solution: PathLabTests.cpp
//
// A test is just a program: it calls the functions, checks the results, and
// returns 0 if everything passed or 1 if anything failed. CTest runs it and
// reads that return value.

#include "PathLab.hpp"
#include <chrono>     // a time stamp, to make a unique temporary folder name
#include <iostream>

// Print a message when a check fails, and tell the caller whether it passed.
bool check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << '\n';
        return false;
    }
    return true;
}

int main() {
    // ---------------------------------------------- Issues 1 and 2: paths
    // Two roots: an ordinary one and a nested one. Testing two cases catches
    // code that only works by accident for one of them.
    const std::filesystem::path root = "course/repo";
    const std::filesystem::path nestedRoot = "course/team/repo";

    // Compare PATH values, not strings with '/' typed in. path compares part
    // by part, so these checks pass on Windows (which prints '\') as well.
    // These folders do not exist: path functions never touch the disk.
    if (!check(minigit::metadataDirectory(root) == root / ".minigit",
               "metadata directory for ordinary root")) return 1;
    if (!check(minigit::metadataDirectory(nestedRoot) == nestedRoot / ".minigit",
               "metadata directory for nested root")) return 1;
    if (!check(minigit::headFile(root) == root / ".minigit" / "HEAD",
               "HEAD path for ordinary root")) return 1;
    if (!check(minigit::headFile(nestedRoot) == nestedRoot / ".minigit" / "HEAD",
               "HEAD path for nested root")) return 1;

    // ---------------------------------------------- Issues 3 and 4: files
    // File tests need a real folder. Use a NEW one under the system's temp
    // folder, with a unique name, so tests never touch your project files
    // and two runs never collide.
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    const auto tempRoot = std::filesystem::temp_directory_path() /
                          ("pathlab-tests-" + std::to_string(stamp));

    // "new/nested" does not exist yet: this checks create_directories.
    const auto file = tempRoot / "new" / "nested" / "note.txt";
    std::string error;
    bool passed = true;   // keep going after a failure, so cleanup still runs

    if (!check(minigit::writeTextFile(file, "hello MiniGit", error),
               "write text in a new nested folder")) {
        std::cerr << error << '\n';
        passed = false;
    }

    // Round trip: what we read back must equal what we wrote.
    std::string text;
    if (!check(minigit::readTextFile(file, text, error),
               "read the file that was written")) {
        std::cerr << error << '\n';
        passed = false;
    }
    if (!check(text == "hello MiniGit", "read back the exact text")) {
        passed = false;
    }

    // The failure path matters too: a missing file must return false
    // AND explain why.
    const auto missingFile = tempRoot / "missing.txt";
    if (!check(!minigit::readTextFile(missingFile, text, error),
               "report a missing file")) {
        passed = false;
    }
    if (!check(!error.empty(), "provide an error message for a missing file")) {
        passed = false;
    }

    // Always clean up the temporary folder, pass or fail.
    std::filesystem::remove_all(tempRoot);
    if (!passed) return 1;

    std::cout << "All path and text file tests passed\n";
    return 0;
}
