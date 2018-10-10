Confirm that the notes are matching with tonality: ./notes 5 (switch 5 to any octave you interested in)

To synthesize your own wav file: ./synthesize test.wav

Notes format:
F#4@1/4 - F - note, # - major 4 - octave, 1/4 note length.
F4@1/4

Possible notes: C, D, E, F, G, A, B.
Possible accidentals: #, b
Possible note length: 1, 1/2, 3/8, 1/4, 1/8
Possible octaves: 1-7, 0 (A, B), 8 (C)

To synthesize wav from text format:
./synthesize jeopardy.wav < songs/jeopardy.txt

Execute wav file:
open filename.wav