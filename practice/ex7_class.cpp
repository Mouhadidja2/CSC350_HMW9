// Exercise 7: turn free functions into a class.
//
// In HW8 every function took the root as a parameter:
//     metadataDirectory(root)      headFile(root)
// A class can store the root ONCE, in a member variable, so the member
// functions need no parameter:
//     RepoLayout layout("course/repo");
//     layout.metadataDirectory()   layout.headFile()
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

int failures = 0;
void check(bool condition, const std::string& message) {
    std::cout << (condition ? "  PASS  " : "  FAIL  ") << message << '\n';
    if (!condition) ++failures;
}

// ---------------------------------------------------------------------
// The class DECLARATION (normally in a .hpp file). Given; do not change.
class RepoLayout {
public:
    explicit RepoLayout(const fs::path& root);   // store the root
    const fs::path& root() const;                // return the stored root
    fs::path metadataDirectory() const;          // root/.minigit
    fs::path headFile() const;                   // root/.minigit/HEAD

private:
    fs::path root_;                              // the stored root
};

// ---------------------------------------------------------------------
// The DEFINITIONS (normally in a .cpp file). Each starts with RepoLayout::
// TODO: replace each body.

// Hint: use a member initializer list:  : root_(root) { }
RepoLayout::RepoLayout(const fs::path& root) {
    (void)root;
}

// Hint: return the member variable.
const fs::path& RepoLayout::root() const {
    return root_;
}

// Hint: same as HW8, but use root_ instead of a parameter.
fs::path RepoLayout::metadataDirectory() const {
    return {};
}

// Hint: reuse metadataDirectory().
fs::path RepoLayout::headFile() const {
    return {};
}

// ---------------------------------------------------------------------
int main() {
    const RepoLayout layout("course/repo");   // a const object: only const member functions can be called
    check(layout.root() == "course/repo", "constructor stores the root");
    check(layout.metadataDirectory() == fs::path("course/repo") / ".minigit", "metadataDirectory uses root_");
    check(layout.headFile() == fs::path("course/repo") / ".minigit" / "HEAD", "headFile reuses metadataDirectory");

    const RepoLayout nested("course/team/repo");
    check(nested.headFile() == fs::path("course/team/repo") / ".minigit" / "HEAD",
          "each object keeps its own root");

    return failures == 0 ? 0 : 1;
}
