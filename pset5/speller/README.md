# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

Long word that we will have to check from dictionary

## According to its man page, what does `getrusage` do?

Returns resource usage measures for the calling process, the children of the calling process, or the calling thread.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16 - 2 structs and 16 long types

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

This negates any dereferencing crashes or extra checks.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The loop points the cursor at each character until it points at an end of file character.
If the cursor's current character is alphabetical or an apostrophe proceeded by a letter then the character is added to "word" in the indexth position and the index is incremented by 1.
If the character falls under those criteria but the word is too long then the loop passes through the remainder of the word and resets the "index". Similarly numbers are ignored.
If a character is not alphabetical or a number or apostrophe then it must be the end of the word. An end of string character is added and the "words" counter is updated.
The word is then passed through the mispelling checks.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fscanf reads whole row, while we needed to get word by word with fgetc.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

We declared parameters const so accidentally we do not modify their source.
