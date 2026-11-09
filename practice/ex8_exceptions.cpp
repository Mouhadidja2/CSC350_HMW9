// Exercise 8: report errors with an exception instead of bool + message.
//
// HW8 style:   bool readTextFile(file, text, errorMessage);   // caller checks the bool
// New style:   std::string readOrThrow(file);                  // caller uses try / catch
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace fs = std::filesystem;

int failures = 0;
void check(bool condition, const std::string& message) {
    std::cout << (condition ? "  PASS  " : "  FAIL  ") << message << '\n';
    if (!condition) ++failures;
}

// TODO: return every character of the file.
// If the file cannot be opened, throw std::runtime_error with a message that
// contains the file name, for example:
//     throw std::runtime_error("Cannot open file: " + file.string());
// Hint: the reading part is the same as HW8's readTextFile.
std::string readOrThrow(const fs::path& file) {
    (void)file;
    return "";   // replace this line
}

// TODO: call readOrThrow(file) inside a try block and return its text.
// In the catch block, catch const std::runtime_error& error,
// print "Sorry: " followed by error.what(), and return "".
std::string readOrDefault(const fs::path& file) {
    (void)file;
    return "not written yet";   // replace this function body
}

int main() {
    const auto stamp = std::chrono::steady_clock::now().time_since_epoch().count();
    const fs::path temp = fs::temp_directory_path() / ("ex8-" + std::to_string(stamp));
    fs::create_directories(temp);
    {
        std::ofstream out(temp / "note.txt", std::ios::binary);
        out << "line1\nline2\n";
    }   // the file closes here

    check(readOrThrow(temp / "note.txt") == "line1\nline2\n", "readOrThrow returns the whole file");

    bool threw = false;
    std::string message;
    try {
        readOrThrow(temp / "missing.txt");
    } catch (const std::runtime_error& error) {
        threw = true;
        message = error.what();
    }
    check(threw, "readOrThrow throws std::runtime_error for a missing file");
    check(message.find("missing.txt") != std::string::npos, "the message names the file");

    check(readOrDefault(temp / "missing.txt").empty(), "readOrDefault catches the error and returns \"\"");
    check(readOrDefault(temp / "note.txt") == "line1\nline2\n", "readOrDefault returns the text when it works");

    fs::remove_all(temp);
    return failures == 0 ? 0 : 1;
}
