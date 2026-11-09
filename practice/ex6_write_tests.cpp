// Exercise 6: the function is correct; you write the tests.
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int passes = 0;
int failures = 0;
void check(bool condition, const std::string& message) {
    std::cout << (condition ? "  PASS  " : "  FAIL  ") << message << '\n';
    if (condition) ++passes; else ++failures;
}

// Given and correct: where a staged copy of a project file is stored.
fs::path stageFile(const fs::path& root, const std::string& name) {
    return root / ".minigit" / "stage" / name;
}

int main() {
    const fs::path root = "course/repo";

    // TODO: write at least three checks with check(condition, "message"):
    //   1. a top-level file, for example "notes.txt"
    //   2. a file in a sub-folder, for example "docs/notes.txt"
    //      (build the expected value with / , not with a string)
    //   3. that filename() of the result is the file's own name
    //
    // Example of the style (it is not one of your three):
    //   check(stageFile(root, "a.txt").parent_path() == root / ".minigit" / "stage",
    //         "staged files live in .minigit/stage");
    (void)root;

    if (passes < 3) {
        std::cout << "  FAIL  write at least three passing checks (you have " << passes << ")\n";
        ++failures;
    }
    return failures == 0 ? 0 : 1;
}
