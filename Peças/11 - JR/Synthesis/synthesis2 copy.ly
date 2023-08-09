
\version "2.22.0"

#(set-global-staff-size 16)

\layout {
        #(set-default-paper-size "a3landscape")
        \context {
                \Voice
                \remove "Note_heads_engraver"
                \consists "Completion_heads_engraver"
                \remove "Rest_engraver"
                \consists "Completion_rest_engraver"
        }
}

eletronici = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 g,,16. r32 bes,,,!32 a,,16 f,,16. r4 } \breathe
\clef bass \ottava #0  ees!8 r8 \clef treble \ottava #2 < f''''! bes''''! d''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  g,16 r16 e,16 r32 \clef bass \ottava #-1 bes,,!16 \grace { \stemNeutral cis,,![ g,, cis,,! e,,] } \grace { \stemNeutral <bes,,,! g,,>[ <aes,,! f,,> <b,, d,,> <cis,,! e,,>] } r32 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  bes,,!8. e,16 cis!8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  aes,!16. r16 \clef bass \ottava #-1 c,32 fis,,!16 r32 ees,,!16. r8. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  bes'''!16 r32 g''''32 cis''''!16. e''''16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  g'''8. r16 d'''16 \clef treble \ottava #0  bes''!8. r4. } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #0  bes,!8( cis,!8 r8 c,8) r8. } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 fis,,!8. a,,16 \clef bass \ottava #0  ees,!8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  cis''''!16 a'''32 r32 e'''16. d'''16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 bes,,,!8. cis,,!16 r8. c,8. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  d'8. fis!16 a,8.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  g,4 r8 } e4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  cis''!16 r32 fis'!32 r16 bes!16. g16. r8. } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #1  aes'''!4  } 
\pitchedTrill
ees''''!2\startTrillSpan cis''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  cis''!16 f'32 \clef bass \ottava #0  fis!16. ees!16.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  aes'''!4 r8 } \repeat tremolo 8 { < f'''' ees''''! bes''''! fis''''! >32 < a'''' cis''''! g'''' e'''' > } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 ees,,!8( r16 b,,8 r16 \clef bass \ottava #0  f,8) r4 } \breathe
\clef treble \ottava #0  cis'''!8 r8 \clef treble \ottava #2 < c''''! aes''''! f''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #0  ees!16 a32 \clef treble \ottava #0  fis'!16. d''16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 g,,8 r4 r16 } \arpeggioArrowDown < c,, e,, cis,,! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  b'''8 r16 ees''''!8 r16 } \clef treble \ottava #2 < c''''! aes''''! d''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  d'8. b16 r16 } 
\pitchedTrill
f2\startTrillSpan a, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  bes!4 r8 } 
\pitchedTrill
e'2\startTrillSpan g' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  fis''''!8 r8 r16 d''''16( \grace { \stemNeutral b'''[ f''' \clef treble \ottava #0  a'' c''] } aes'!16 \grace { \stemNeutral ees'![ cis'! \clef bass \ottava #0  bes! e)] } r8. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  ees!8 r4 } \arpeggioArrowUp < g c' d' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  bes!16 r16 cis!16 g,16 \grace { \stemNeutral e,[ d, \clef bass \ottava #-1 aes,,! c,,] } \grace { \stemNeutral <d,, f,,>[ <b,, g,,> <cis,,! e,,> <bes,,,! g,,>] } r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  aes'''!8. r16 f''''16  } 
\pitchedTrill
a''''2\startTrillSpan d'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 cis,!4 r8 } 
\pitchedTrill
g,,2\startTrillSpan bes,,,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  fis'''!8. ees''''!16 r4 e''''8. r8 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  g,16 \clef bass \ottava #-1 cis,!16 f,,16 aes,,!16 \grace { \stemNeutral e,,[ b,, a,, fis,,!] } r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  aes''''!8. b''''16  } 
\pitchedTrill
ees''''!2\startTrillSpan a'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  d8 r4 r16 } \clef bass \ottava #-1 \arpeggioArrowDown < fis,!  g,, e,, bes,,,! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 fis,,!8( ees,,!8 a,,8)  } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  ees'!16. cis''!32 r16 aes''!16 e'''16. r8.. } \breathe
\tupletSpan 4
\tuplet 5/4 { r4 r16 \clef bass \ottava #0  bes!8 r16 d16( \grace { \stemNeutral ees,![ \clef bass \ottava #-1 c, fis,,! a,,] } b,,16 \grace { \stemNeutral e,,[ aes,,! f,, cis,,!)] }  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  fis''!8( d''8 b'8)  } \breathe
\bar "|."
}
}
eletronicii = { \absolute {
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  g16. ees'!32 a'16 c''16. r4 } \breathe
r16 \clef bass \ottava #-1 bes,,,!8 r16 \clef treble \ottava #2 < a''''! f''''! d''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef bass \ottava #0  g,16 ees!16 c'16 \grace { \stemNeutral \clef treble \ottava #0  e'[ g' bes'! d''] } \grace { \stemNeutral \clef treble \ottava #1  <b''  g'''>[  <fis''''! d''''>  <b'''' f''''>  <fis''''! bes''''!>] } r16. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  bes''''!16 g''''16 r16 cis''''!16 \grace { \stemNeutral e'''[ \clef treble \ottava #0  fis''! c'' a'] } \grace { \stemNeutral  <g' e'>[ \clef bass \ottava #0  < bes! cis!>  <g, e,> \clef bass \ottava #-1 < bes,,! cis,,!>] } r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #0  c'8( r16 a8 f8) r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 a,,,16. cis,,!32 r32 bes,,!16 r16 \clef bass \ottava #0  fis,!16. r8. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  g''''8. e''''16 r8 f'''8. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  f''''16 b''''16 r16. d''''16 \grace { \stemNeutral aes''''![ b'''' aes''''! fis''''!] } \grace { \stemNeutral <ees''''! a''''>[ <cis''''! ees''''!> <fis''''! c'''''> <aes''''! d''''>] } r32 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  d8. ees,!16 \clef bass \ottava #-1 g,,8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  aes!16. d'32 b'16 r32 g''16. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef bass \ottava #-1 bes,,,!8( r2 c,,8 ees,,!8) r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 cis,!4 r8 } 
\pitchedTrill
e,,2\startTrillSpan bes,,,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  g'''8. r16 fis''''!16 r8 a''''8. r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 cis,!16 g,,32 ees,,!16. c,,16.  } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  e'''16 r32 cis''''!16 a''''16 \grace { \stemNeutral c'''''[ e'''' aes''''! d''''] } \grace { \stemNeutral <bes''''! g''''>[ <cis''''! g''''> <ees''''! c'''''> <fis''''! a''''>] } r16. } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #-1 fis,,!8( aes,,!8 r16 b,,8) r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef treble \ottava #1  bes'''!16 g'''16 e'''16 \grace { \stemNeutral \clef treble \ottava #0  g''[ a' \clef bass \ottava #0  c' e] } \grace { \stemNeutral  <d b,>[ \clef bass \ottava #-1 <f,  cis,!>  <bes,,! d,,>  <aes,,! b,,>] } r16. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  f'''8 r16 r16 a'''16( \grace { \stemNeutral d''''[ e'''' g'''' cis''''!] } bes''''!16 \grace { \stemNeutral b''''[ ees''''! fis''''! c''''')] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 d,,8 b,,8 f,,8.  } aes,,!4:64 \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  cis''!16 ees''!16 aes''!16 c'''16 \grace { \stemNeutral \clef treble \ottava #1  a'''[ f'''' b'''' d''''] }  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  g'''8 cis'''!8 \clef treble \ottava #0  bes''!8.  } b'4:64 \breathe
\bar "|."
}
}
eletroniciii = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  g16. r32 e'32 aes'!16 cis''!16. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #-1 ees,,!16 a,,16 f,,16 \grace { \stemNeutral b,,[ aes,,! c,, a,,] } \grace { \stemNeutral <c,, fis,,!>[ <ees,,! fis,,!> <d,, a,,> <c,, fis,,!>] } r8 } \breathe
\clef treble \ottava #0  c''8 r8 \clef treble \ottava #2 < fis''''! ees''''! e''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  e'''16 r16 \clef treble \ottava #0  aes''!16 cis''!16 \grace { \stemNeutral a'[ ees'! \clef bass \ottava #0  bes! fis!] } \grace { \stemNeutral  <c e,>[ \clef bass \ottava #-1 < g,, b,,>  <e,, fis,,!>  <ees,,! b,,>] }  } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  g'''8. e''''16 r16 c'''''8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  bes!8. d16 ees,!8. r4. } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  d'8 aes'!8 f''8.  } fis''!4:64 \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #-1 bes,,!8 r4 } \arpeggioArrowDown < g,, b,, e,, fis,,! >4\arpeggio \startTrillSpan a,,4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  g'8 r4 r16 } \clef treble \ottava #1  \arpeggioArrowUp < ees''! c'''  fis'''! bes'''! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  fis!16 ees!32 a,16. r32 c,16. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  d''''8. f''''16 r16 } 
\pitchedTrill
a''''2\startTrillSpan bes''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  bes''''!8. c''''16  } 
\pitchedTrill
f'''2\startTrillSpan a'' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #0  f''8 r8. } \clef treble \ottava #1  \arpeggioArrowUp < fis''! bes''!  cis'''! g''' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  fis''''!8. bes'''!16 cis'''!8.  } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #-1 bes,,!16 \clef bass \ottava #0  g,16 e16 \grace { \stemNeutral g[ \clef treble \ottava #0  cis'! e' fis'!] } \grace { \stemNeutral  <c'' a''>[ \clef treble \ottava #1  < g''' f''''>  <d'''' aes''''!>  <bes''''! cis''''!>] } r8 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #-1 cis,,!8. f,,16 aes,,!8. r4. } \breathe
\clef bass \ottava #0  g,8 r8 \clef treble \ottava #2 < a''''! d''''! fis''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  cis'''!4 r8 } \repeat tremolo 8 { \clef treble \ottava #0  <  bes''! d'' g' >32 \clef bass \ottava #0  <  a c fis,! > } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  ees'''!16 b'''16 ees''''!16 \grace { \stemNeutral g''''[ c''''' aes''''! d''''] } \grace { \stemNeutral <a'''' f''''>[ <aes''''! d''''> <fis''''! a''''> <fis''''! bes''''!>] } r8 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  aes''''!8. r16 e''''16  } 
\pitchedTrill
bes'''!2\startTrillSpan cis'''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  a,8. b,16 e8.  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  ees'!8 r16 cis'!8 bes!8. r4. } e4:64 \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef bass \ottava #0  c,8. f,16 r4 } 
\pitchedTrill
g,2\startTrillSpan bes,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef treble \ottava #1  aes''''!4. r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  g'''4 r8 } 
\pitchedTrill
ees''''!2\startTrillSpan a'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  bes''!8 f''8 r8 } \clef treble \ottava #2 < cis''''! e''''! aes''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  a''''8 r4 } \arpeggioArrowUp < bes''''! d'''' f'''' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  fis'''!16 \clef treble \ottava #0  aes''!16 ees''!16 \grace { \stemNeutral cis''![ bes'! ees'! \clef bass \ottava #0  f] } \grace { \stemNeutral \clef bass \ottava #-1 <aes,!  bes,,!>[  <ees,,! cis,,!>  <aes,,! e,,>  <b,, a,,>] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #1  d''''4  } \repeat tremolo 8 { < aes''''! b'''' bes''''! fis''''! >32 < ees''''! a'''' cis''''! e'''' > } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  aes'!16 f'32 \clef bass \ottava #0  fis!16. bes,!16.  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 c,,8. r16 aes,,!16 \clef bass \ottava #0  f,8. r4. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  aes''!4 r8 } \repeat tremolo 8 { \clef bass \ottava #0  < b' f' cis'!  bes! >32 \clef bass \ottava #-1 < d g,  a,, c,, > } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  bes''!8. \clef treble \ottava #1  fis'''!16 ees''''!8.  } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  d''''8 r16 r16 r16 ees'''!16( \grace { \stemNeutral \clef treble \ottava #0  g''[ bes'! e' \clef bass \ottava #0  c'] } a16 \grace { \stemNeutral cis![ fis,! \clef bass \ottava #-1 aes,,! b,,)] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef treble \ottava #0  f''8 aes''!8 r16 } \clef treble \ottava #2 < c''''!  cis''''! bes''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  b''8 r4 r16 } \arpeggioArrowDown < ees''! a' fis'! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  g'''8 r16 cis''''!16( \grace { \stemNeutral e''''[ fis''''! b'''' ees''''!] } c'''''16 \grace { \stemNeutral aes''''![ d'''' f'''' a'''')] }  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 ees,,!8( fis,,!8 \clef bass \ottava #0  d,8)  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  a,8 r4 r16 } \clef bass \ottava #-1 \arpeggioArrowDown < g, e,  bes,,! cis,,! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  c'''''8 r16 r8 d''''16( \grace { \stemNeutral f''''[ b'''' aes''''! a''''] } r16 cis''''!16 \grace { \stemNeutral e''''[ bes''''! fis''''! ees''''!)] } r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  ees'''!8( r16 fis'''!8 r8 bes'''!8) r8. } \breathe
\bar "|."
}
}
eletroniciv = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  g16. bes!32 e'16 r32 cis''!16. r4 } \breathe
r16 \clef treble \ottava #0  bes'!8 r16 \clef treble \ottava #2 < aes''''! f''''! b''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #-1 a,,,16 fis,,!16 \clef bass \ottava #0  d,16 \grace { \stemNeutral f,[ b, ees! c'] } \grace { \stemNeutral \clef treble \ottava #0  < fis'! ees''!>[ \clef treble \ottava #1  < cis'''! e'''>  <c'''' g''''>  <a'''' c'''''>] } r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef treble \ottava #1  fis''''!16 r16 c''''16 fis'''!16 \grace { \stemNeutral \clef treble \ottava #0  c'''[ ees''! a' fis'!] } \grace { \stemNeutral \clef bass \ottava #0  <ees'!  a>[  <c ees,!> \clef bass \ottava #-1 < a,, f,,>  <d,, aes,,!>] } r32 } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef treble \ottava #1  g''''8( r16 ees''''!8 r16 c''''8) r8. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  aes!16. r16 f'32 fis'!16 bes'!16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 fis,,!8. c,,16 r16 ees,,!8. r4. } \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef bass \ottava #0  ees,!16 g,16 cis!16 \grace { \stemNeutral a[ \clef treble \ottava #0  fis'! c'' aes''!] } \grace { \stemNeutral \clef treble \ottava #1  <b''  ees'''!>[  <e''' aes'''!>  <d'''' b''''>  <bes''''! fis''''!>] } r16. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  g,8. r4 cis,!16 bes,,!8. r8 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  cis''!16. e''32 fis''!16 b''16. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  ees''!8( fis''!8 bes''!8)  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  ees''''!4 r8 } 
\pitchedTrill
fis'''!2\startTrillSpan d''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #1  b'''8. d''''16 cis''''!8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  f'''16 \clef treble \ottava #0  a''32 c''16. fis'!16.  } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  d,16 b,16 f16 \grace { \stemNeutral aes![ c' \clef treble \ottava #0  fis'! a'] } \grace { \stemNeutral \clef treble \ottava #1  <f''  d'''>[  <fis'''! ees''''!>  <a'''' c'''''>  <aes''''! b''''>] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  ees''''!8( b''''8 r16 bes''''!8) r4 r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  g''''16 r32 e''''16 r16 g'''16 \grace { \stemNeutral \clef treble \ottava #0  bes''![ c'' a' g'] } \grace { \stemNeutral  <f' d'>[ \clef bass \ottava #0  < aes! bes,!> \clef bass \ottava #-1 < cis,! g,,>  <cis,,! e,,>] } r32 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  b'''8 r16 r16 f''''16( \grace { \stemNeutral cis''''![ bes''''! d'''' g''''] } r8 a''''16 \grace { \stemNeutral c'''''[ fis''''! ees''''! e'''')] } r8 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  cis!8 f,8 \clef bass \ottava #-1 bes,,!8.  } c,,4:64 \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  aes!16 r32 \clef treble \ottava #0  f'16 b'16 ees''!16 \grace { \stemNeutral fis''![ \clef treble \ottava #1  d''' a''' g''''] } r32 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  ees,!8 \clef bass \ottava #-1 a,,8 r16 c,,8. r4. } e,,4:64 \breathe
\bar "|."
}
}
eletronicv = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  g16. cis!32 r32 e,16 \clef bass \ottava #-1 fis,,!16. r4 } \breathe
r16 \clef treble \ottava #0  fis''!8 r16 \clef treble \ottava #2 <  e''''! cis''''! g''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  g'16 cis'!16 r16 \clef bass \ottava #0  f16 \grace { \stemNeutral b,[ g, ees,! \clef bass \ottava #-1 a,,] } \grace { \stemNeutral <cis,,! g,,>[ <e,, bes,,,!> <d,, f,,> <aes,,! d,,>] } r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #0  a4  } 
\pitchedTrill
f'2\startTrillSpan e'' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef treble \ottava #0  d'8( b'8 f''8) r4 r16 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  c'''4 r8 } 
\pitchedTrill
fis''!2\startTrillSpan a' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #1  g'''16 ees''''!32 r32 c'''''16. fis''''!16. r8.. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  d''16 r32 f'32 \clef bass \ottava #0  a16. r16. bes,!16. r8 r32 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 c,,16 r32 a,,32 \clef bass \ottava #0  ees,!16. fis,!16. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #0  aes,!16 r32 \clef bass \ottava #-1 b,,16 d,,16 \grace { \stemNeutral b,,[ f,, d,, bes,,,!] } \grace { \stemNeutral <e,, g,,>[ <fis,,! bes,,,!> <cis,,! g,,> <aes,,! f,,>] } r32 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  d'''8 r4 r16 } \arpeggioArrowUp < f''' e'''' c''''' a'''' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  ees'''!16 \clef treble \ottava #0  a''16 r16. c''16 \grace { \stemNeutral fis'![ \clef bass \ottava #0  a fis! g,] } \grace { \stemNeutral \clef bass \ottava #-1 <e,  bes,,!>[  <cis,,! c,,>  <ees,,! a,,>  <fis,,! c,,>] } r32 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  g'''4 r8 } 
\pitchedTrill
e''''2\startTrillSpan c''''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  bes,!8. g,16 r8 \clef bass \ottava #-1 b,,8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  cis'!16. g'32 e''16 r16 f''16. r8.. } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #-1 f,,16 b,,32 ees,,!16. r16. fis,,!16. r8 r32 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  aes''!16 r16 \clef treble \ottava #1  f'''32 b'''16. ees''''!16. r8. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  fis,!4 r8 } 
\clef bass \ottava #-1
\pitchedTrill
 c,2\startTrillSpan ees,,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { r16 \clef treble \ottava #0  aes''!16 \clef treble \ottava #1  e'''32 r32 b'''16. a''''16. r8. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  bes''''!8 r16 r16 e''''16( \grace { \stemNeutral g'''[ \clef treble \ottava #0  b'' c'' a'] } ees'!16 \grace { \stemNeutral \clef bass \ottava #0  fis![ aes,! \clef bass \ottava #-1 cis,! f,,)] } r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #-1 g,,16 bes,,!16 r32 \clef bass \ottava #0  d,16 \grace { \stemNeutral b,[ g \clef treble \ottava #0  ees'! c''] } \grace { \stemNeutral  <e'' g''>[ \clef treble \ottava #1  < cis'''! e'''>  <aes'''! a'''>  <ees''''! c'''''>] } r16. } \breathe
\clef bass \ottava #-1 ees,,!8 r8 \clef treble \ottava #2 < cis''''! aes''''! e''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  bes''''!8 fis''''!8 r16 c'''''8. r4. } ees''''!4:64 \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #1  aes''''!8 r8. } \clef treble \ottava #0  \arpeggioArrowDown < b''' f''' cis'''!  bes''! >4\arpeggio \startTrillSpan d''4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  f'''8 cis''''!8 r8 } \clef treble \ottava #2 < bes''''! d''''! g''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  bes''!4.  } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #0  ees''!4  } 
\pitchedTrill
aes''!2\startTrillSpan bes''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  aes!8 r16 r16 f16( \grace { \stemNeutral fis,![ \clef bass \ottava #-1 bes,,! cis,,! g,,] } ees,,!16 \grace { \stemNeutral c,,[ e,, a,, b,,)] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #0  bes''!8. r16 \clef treble \ottava #1  e'''16 r16 g'''8. r8. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  cis!16 r16 aes,!16 \clef bass \ottava #-1 b,,16 \grace { \stemNeutral e,,[ aes,,! f,, cis,,!] } \grace { \stemNeutral <a,, e,,>[ <d,, fis,,!> <a,, ees,,!> <f,, bes,,,!>] } r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef bass \ottava #0  g16 bes!16 \clef treble \ottava #0  d'16 \grace { \stemNeutral b'[ g'' \clef treble \ottava #1  ees'''! c''''] } \grace { \stemNeutral <e'''' g''''>[ <cis''''! e''''> <aes''''! a''''> <ees''''! c'''''>] } r16. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  cis''''!8. f'''16 r16 } 
\clef treble \ottava #0 
\pitchedTrill
 b''2\startTrillSpan aes''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 bes,,,!8. r8 aes,,!16 \clef bass \ottava #0  ees,!8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  fis''''!8 r16 a'''16( \grace { \stemNeutral ees'''![ \clef treble \ottava #0  b'' aes''! c''] } f'16 \grace { \stemNeutral \clef bass \ottava #0  g[ bes,! e, \clef bass \ottava #-1 cis,!)] }  } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #-1 b,,8. aes,,!16  } 
\pitchedTrill
a,,2\startTrillSpan cis,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  ees''!16 f'16 \clef bass \ottava #0  aes!16 \grace { \stemNeutral fis![ cis! bes,! e,] } \grace { \stemNeutral \clef bass \ottava #-1 < a,, b,,>[  <d,, aes,,!>  <b,, ees,,!>  <c,, bes,,,!>] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 c,,8( r16 fis,,!8 a,,8) r4 r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  fis,!8. b,16 ees!8. r4. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  ees''''!16 r16 aes'''!16 \clef treble \ottava #0  bes''!16 r32 cis''!16 \grace { \stemNeutral g'[ e' \clef bass \ottava #0  f a,] } r8. r16. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  cis'!8( e8 bes,!8)  } \breathe
\bar "|."
}
}

\score {
        \new StaffGroup <<

                \new Staff \with { instrumentName= "Eletronic I" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \eletronici
                        }
                \new Staff \with { instrumentName= "Eletronic II" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \eletronicii
                        }
                \new Staff \with { instrumentName= "Eletronic III" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \eletroniciii
                        }
                \new Staff \with { instrumentName= "Eletronic IV" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \eletroniciv
                        }
                \new Staff \with { instrumentName= "Eletronic V" } {
                        \time 4/4
                        \set completionUnit = #(ly:make-moment 1/4)
                        \eletronicv
                        }
        >>
}
