// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

namespace Carbon {

// Expand any escape sequences in the given string literal.
static auto ExpandEscapeSequencesAndRemoveIndent(
    LexerDiagnosticEmitter& emitter, llvm::StringRef contents, int hash_level,
    llvm::StringRef indent) -> std::string {
  std::string result;
  result.reserve(contents.size());

  llvm::SmallString<16> escape("\\");
  escape.resize(1 + hash_level, '#');

  // Process each line of the string literal.
  while (true) {
    // Every non-empty line (that contains anything other than horizontal
    // whitespace) is required to start with the string's indent. For error
    // recovery, remove all leading whitespace if the indent doesn't match.
    if (!contents.consume_front(indent)) {
      const char* line_start = contents.begin();
      contents = contents.drop_while(IsHorizontalWhitespace);
      if (!contents.startswith("\n")) {
        CARBON_DIAGNOSTIC(
            MismatchedIndentInString, Error,
            "Indentation does not match that of the closing `'''` in "
            "multi-line string literal.");
        emitter.Emit(line_start, MismatchedIndentInString);
      }
    }

    // Process the contents of the line.
    while (true) {
      auto end_of_regular_text = contents.find_if([](char c) {
        return c == '\n' || c == '\\' ||
               (IsHorizontalWhitespace(c) && c != ' ');
      });
      result += contents.substr(0, end_of_regular_text);
      contents = contents.substr(end_of_regular_text);

      if (contents.empty()) {
        return result;
      }

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

      if (IsHorizontalWhitespace(contents.front())) {
        // Horizontal whitespace other than ` ` is valid only at the end of a
        // line.
        CARBON_CHECK(contents.front() != ' ')
            << "should not have stopped at a plain space";
        auto after_space = contents.find_if_not(IsHorizontalWhitespace);
        if (after_space == llvm::StringRef::npos ||
            contents[after_space] != '\n') {
          // TODO: Include the source range of the whitespace up to
          // `contents.begin() + after_space` in the diagnostic.
          CARBON_DIAGNOSTIC(
              InvalidHorizontalWhitespaceInString, Error,
              "Whitespace other than plain space must be expressed with an "
              "escape sequence in a string literal.");
          emitter.Emit(contents.begin(), InvalidHorizontalWhitespaceInString);
          // Include the whitespace in the string contents for error recovery.
          result += contents.substr(0, after_space);
        }
        contents = contents.substr(after_space);
        continue;
      }

      if (!contents.consume_front(escape)) {
        // This is not an escape sequence, just a raw `\`.
        result += contents.front();
        contents = contents.drop_front(1);
        continue;
      }

      if (contents.consume_front("\n")) {
        // An escaped newline ends the line without producing any content and
        // without trimming trailing whitespace.
        break;
      }

      // Handle this escape sequence.
      ExpandAndConsumeEscapeSequence(emitter, contents, result);
    }
  }
}

}  // namespace Carbon
