
\version "2.23.5"

#(set-global-staff-size 18)

\layout {
        #(set-default-paper-size "a4landscape")
        \context {
                \Voice
                \remove "Note_heads_engraver"
                \consists "Completion_heads_engraver"
                \remove "Rest_engraver"
                \consists "Completion_rest_engraver"
        }
}

pianoi = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  g'16. \clef bass \ottava #0  b32 f16 d16.  } \breathe
r8 \clef treble \ottava #1  fis''''!8  \clef treble \ottava #2 < c''''! ees''''! g''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  d''16 bes'!16 r32 fis'!16 \grace { \stemNeutral \clef bass \ottava #0  bes![ cis! f, \clef bass \ottava #-1 aes,,!] } \grace { \stemNeutral <f,, cis,,!>[ <g,, e,,> <c,, b,,> <f,, a,,>] } r16. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  ees''!8. a''16 \clef treble \ottava #1  fis'''!8. r4. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  g''''16. r16. d''''32 r8 r32 bes'''!16 r16 cis'''!16. r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { r16. \clef bass \ottava #0  bes,!16 r16 e32 g16. r16 a16. r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 cis,,!8. g,,16 r8 e,,8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { r8. \clef treble \ottava #1  aes'''!8( \clef treble \ottava #0  b''8 f''8) r8. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  g'8. b'16 r16 e''8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { r16 \clef treble \ottava #1  bes''''!16 fis''''!32 r32 f''''16. r32 aes'''!16. r8 r32 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef bass \ottava #-1 a,,,8. cis,,!16 g,,8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8. \clef treble \ottava #0  fis'!8. r16 \clef bass \ottava #0  a16 r8 cis!8. r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { r2 \clef treble \ottava #1  d'''4  } fis'''!4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  b16 aes!32 d16. f,16.  } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef bass \ottava #0  cis,!4  } 
\pitchedTrill
bes,!2\startTrillSpan fis! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #0  aes,!16 r32 e,32 \clef bass \ottava #-1 bes,,!16. cis,,!16. r8.. } \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef bass \ottava #0  g,4 r4 } \repeat tremolo 8 {  < bes,! d aes! >32 \clef treble \ottava #0  <  f' cis''! c''' > } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  bes!8( f'8 ees''!8)  } \breathe
r4 r16 \clef treble \ottava #1  d''''8 r16 \clef treble \ottava #2 < aes''''!  b''''! ees''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #0  ees!16 r32 a32 r32 c'16. d'16. r8. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  cis'!8 r4 } \clef bass \ottava #0  \clef bass \ottava #-1 \arpeggioArrowDown <  f bes,!  c, ees,,! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef treble \ottava #0  aes''!8 \clef treble \ottava #1  cis'''!8 r4 } \clef treble \ottava #2 < ees''''! fis''''! c''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #0  fis!8. c16  } 
\pitchedTrill
aes,!2\startTrillSpan f, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r4. \clef bass \ottava #-1 ees,,!4 r8 } 
\pitchedTrill
g,,2\startTrillSpan bes,,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  g'''8 r16 e'''16( \grace { \stemNeutral \clef treble \ottava #0  aes''![ cis''! ees'! \clef bass \ottava #0  fis!] } c16 \grace { \stemNeutral a,[ \clef bass \ottava #-1 bes,,! d,, f,,)] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  cis!8 r4 r16 } \clef treble \ottava #0  \arpeggioArrowUp < a  e' d'' b'' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef treble \ottava #0  bes'!16 r32 fis'!16 r16 \clef bass \ottava #0  bes!16 \grace { \stemNeutral d[ g, ees,! \clef bass \ottava #-1 a,,] } \grace { \stemNeutral <e,, c,,>[ <ees,,! a,,> <cis,,! e,,> <cis,,! f,,>] } r8.. } \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef bass \ottava #0  ees!8. r16 fis!16 r8. } 
\pitchedTrill
c'2\startTrillSpan aes'! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  bes!4 r8 } 
\pitchedTrill
cis!2\startTrillSpan g, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  aes''''!8. b''''16 r16 f''''8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef bass \ottava #0  d,16 r32 \clef bass \ottava #-1 f,,16 cis,,!16 r16. aes,,!16 \grace { \stemNeutral fis,,![ ees,,! a,, c,,] } r8.. } \breathe
\tupletSpan 4
\tuplet 5/4 { r4 \clef treble \ottava #0  aes''!8. \clef treble \ottava #1  d'''16 r8 } 
\pitchedTrill
b'''2\startTrillSpan g'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r8. \clef treble \ottava #0  fis'!8 r8 } \arpeggioArrowDown < c' a g >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef treble \ottava #1  fis'''!8( r16 d'''8 cis'''!8) r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  bes'!16. fis''!32 \clef treble \ottava #1  ees'''!16 r16 a'''16. r8. } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #0  cis!8 r16 r16 bes,!16( \grace { \stemNeutral fis,![ f, \clef bass \ottava #-1 aes,,! d,,] } r16 b,,16 \grace { \stemNeutral a,,[ e,, c,, ees,,!)] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #-1 g,,8( cis,,!8 r16 a,,8) r4 } \breathe
\bar "|."
}
}
pianoii = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  g16. r8 r32 bes,!32 e,16 cis,!16. r8 } \breathe
\clef treble \ottava #0  e'8 r8 \clef treble \ottava #2 < fis''''! b''''! ees''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  c16 aes,!16 r16 \clef bass \ottava #-1 b,,16 \grace { \stemNeutral ees,,![ a,, fis,,! c,,] } \grace { \stemNeutral <fis,,! d,,>[ <b,, f,,> <aes,,! bes,,,!> <cis,,! f,,>] } r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef bass \ottava #0  ees!8. r16 \clef treble \ottava #0  d'16 f'8. r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  g'16. cis'!32 r8 bes!16 aes!16. r8 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #1  bes'''!16 a''''32 r32 c'''''16. r32 fis''''!16. r8. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  d'''8. a''16 r16 f''8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 bes,,!8( r4. a,,8 r16 f,,8) r4 r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef bass \ottava #0  g,8. r8. e16 r16 bes!8. r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  b''16 e''32 fis'!16. a16.  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  aes'!8. r16 fis''!16 r8 ees'''!8. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  e''8. fis'!16 a8.  } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef bass \ottava #0  bes,!4  } aes!4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  fis,!16 r32 \clef bass \ottava #-1 c,32 a,,16. r32 bes,,,!16. r8.. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  a4 r8 } 
\pitchedTrill
ees'!2\startTrillSpan b' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  cis'''!16 bes''!32 e''16. r32 aes'!16. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  g''4 r8 } \repeat tremolo 8 { \clef treble \ottava #1  < bes''!  d''' aes'''! f'''' >32  < cis''''! c''''' ees''''! a'''' > } \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef treble \ottava #1  cis'''!8( r16 e'''8 aes'''!8) r16 } \breathe
\clef treble \ottava #0  fis'!8 r8 \clef treble \ottava #2 < d''''!  b''''! f''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { r16 \clef bass \ottava #0  aes,!16 b,32 r32 cis!16. r16. fis!16. r16. } \breathe
\tupletSpan 4
\tuplet 7/4 { r4 \clef bass \ottava #0  ees'!8 r16 } \arpeggioArrowDown < c' bes! f >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  bes,,!8 r16 g,8 r16 } \clef treble \ottava #2 < cis''''! e''''! ees''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  fis'''!8. r16 ees'''!16  } 
\clef treble \ottava #0 
\pitchedTrill
 b''2\startTrillSpan bes''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  ees,!4 r8 } 
\pitchedTrill
fis,!2\startTrillSpan f r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  g8 r16 bes,!16( \grace { \stemNeutral \clef bass \ottava #-1 c,[ f,, a,, fis,,!] } r16 d,,16 \grace { \stemNeutral aes,,![ b,, ees,,! e,,)] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r4 \clef bass \ottava #-1 cis,,!8 r16 } \clef bass \ottava #0  \arpeggioArrowUp < bes,,! b,,  ees,! fis,! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  aes'''!16 r32 \clef treble \ottava #0  c'''16 r16 f''16 \grace { \stemNeutral cis''![ g' d' \clef bass \ottava #0  bes!] } \grace { \stemNeutral  <e aes,!>[ \clef bass \ottava #-1 < b,, ees,,!>  <aes,,! bes,,,!>  <g,, ees,,!>] } r32 } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  cis''!8. r16 bes''!16 r4 } 
\clef treble \ottava #1 
\pitchedTrill
 e'''2\startTrillSpan g''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  a4 r8 } 
\pitchedTrill
bes,!2\startTrillSpan g, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  ees''''!8. c'''''16 fis''''!8. r4. } \breathe
\tupletSpan 4
\tuplet 5/4 { r16. \clef treble \ottava #1  fis'''!16 r32 \clef treble \ottava #0  a''16 r32 aes''!16 e''16 \grace { \stemNeutral cis''![ g' \clef bass \ottava #0  b d] } r8.. } \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef bass \ottava #-1 cis,,!8. f,,16 r4 } 
\clef bass \ottava #0 
\pitchedTrill
 d,2\startTrillSpan bes,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #-1 a,,8 r4 } \arpeggioArrowDown < fis,,! bes,,,! ees,,! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #1  c'''''8( fis''''!8 r16 ees''''!8) r8. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  e''''16. c'''''32 a''''16 ees''''!16.  } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  bes'!8 r16 g'16( \grace { \stemNeutral f'[ \clef bass \ottava #0  c' aes! b,] } ees,!16 \grace { \stemNeutral \clef bass \ottava #-1 a,,[ fis,,! d,, cis,,!)] } r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  g''8( b'8 r8 d'8) r4 } \breathe
\bar "|."
}
}

\score {
        \new StaffGroup <<

                \new Staff \with { instrumentName= "Piano I" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \pianoi
                        }
                \new Staff \with { instrumentName= "Piano II" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \pianoii
                        }
        >>
        \midi { }
}
