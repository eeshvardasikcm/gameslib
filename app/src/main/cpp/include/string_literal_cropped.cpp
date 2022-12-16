// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

namespace Carbon {

    // Expand any escape sequences in the given string literal.
    static auto ExpandEscapeSequencesAndRemoveIndentCropped(
        llvm::StringRef contents) -> std::string {
      std::string result;
      result.reserve(contents.size());

          if (contents.consume_front("\n")) {
            // Trailing whitespace before a newline doesn't contribute to the string
            // literal value.
            while (!result.empty() && result.back() != '\n' &&
                   IsSpace(result.back())) {
              result.pop_back();
            }
            result += '\n';
            // Move onto to the next line.
            break;
          }

          if (contents.consume_front("\n")) {
            // An escaped newline ends the line without producing any content and
            // without trimming trailing whitespace.
            break;
          }
      }
}

}  // namespace Carbon
