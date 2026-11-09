// HW8 reference solution: PathLab.hpp
//
// A header file only DECLARES functions: name, parameters, return type.
// The code that does the work lives in src/PathLab.cpp.
// Any .cpp file that #includes this header can call these functions.

#pragma once            // include this header only once per .cpp file
#include <filesystem>   // std::filesystem::path
#include <string>       // std::string

namespace minigit {     // groups our names so they cannot clash with others

// Issue 1. Return root/.minigit. Builds a path only; creates nothing.
//
// Why "const std::filesystem::path& root"?
//   const : the function promises not to change the caller's path
//   &     : pass a reference, so the path is not copied
std::filesystem::path metadataDirectory(const std::filesystem::path& root);

// Issue 2. Return root/.minigit/HEAD. Also builds a path only.
std::filesystem::path headFile(const std::filesystem::path& root);

// Issue 3. Create missing parent folders, then write text to file.
// Returns true on success. On failure returns false and puts a message
// in errorMessage.
//
// Why is errorMessage a NON-const reference (std::string&)?
//   Because the function writes INTO it: it is an "output parameter".
//   (Next week's FileSystem class throws an exception instead.)
bool writeTextFile(const std::filesystem::path& file,
                   const std::string& text,
                   std::string& errorMessage);

// Issue 4. Read the whole file into text.
// Returns true on success; on failure returns false and sets errorMessage.
// Here text is an output parameter too.
bool readTextFile(const std::filesystem::path& file,
                  std::string& text,
                  std::string& errorMessage);

} // namespace minigit
