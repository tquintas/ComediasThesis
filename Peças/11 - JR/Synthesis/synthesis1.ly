
\version "2.23.5"

#(set-global-staff-size 16)

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

eletronici = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  g'''16. b'''32 c''''16 a''''16.  } \breathe
\clef bass \ottava #-1 a,,8 r8 \clef treble \ottava #2 < f''''! e''''! g''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  g''16 \clef treble \ottava #1  cis'''!16 g'''16 \grace { \stemNeutral cis''''![ f'''' b'''' g''''] } \grace { \stemNeutral <ees''''! a''''>[ <c''''' e''''> <bes''''! g''''> <e'''' bes''''!>] } r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  f'8. r8 \clef bass \ottava #0  a16 fis!8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { r16 \clef bass \ottava #-1 d,,16. f,,32 cis,!16 \clef bass \ottava #0  aes,!16. r8.. } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  ees''!16 b'32 fis'!16. r8 r32 e'16. r16. } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  g8. r8 cis'!16 r16 f'8. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  bes'!8( fis''!8 ees'''!8)  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  cis''''!8. fis'''!16 \clef treble \ottava #0  bes''!8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #-1 f,,16 cis,!32 r32 \clef bass \ottava #0  bes,!16. e16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  d8. cis!16 r16 a,8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  c''''8. a''''16 ees''''!8.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  g,4 r8 } bes,,!4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  d'''16 f'''32 g'''16. c''''16.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 cis,!4 r8 } 
\pitchedTrill
ees,,!2\startTrillSpan aes,,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  aes''''!16 bes''''!32 ees''''!16. r16 g''''16. r8.. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  ees''''!4 r8 } \repeat tremolo 8 {  < a''' fis'''! d''' cis'''! >32 \clef treble \ottava #0  <  e'' bes'! g' f' > } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  aes'''!8( r16 \clef treble \ottava #0  b''8 r8 f''8) r8. } \breathe
\clef bass \ottava #-1 bes,,,!8 r8 \clef treble \ottava #2 < d''''! ees''''! c''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 cis,!16 ees,,!32 aes,,!16. r32 c,,16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  g''8 r4 } \clef treble \ottava #1  \arpeggioArrowUp <  e''' bes'''! cis''''! ees''''! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 cis,,!8 r8. f,,8 r4 r16 } \clef treble \ottava #2 < aes''''! d''''! bes''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  e''''8. c'''''16 r16 } 
\pitchedTrill
a''''2\startTrillSpan cis''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  fis!4 r8 } 
\pitchedTrill
ees!2\startTrillSpan a, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  bes'''!8 r8. r16 cis''''!16( \grace { \stemNeutral g''''[ e'''' f'''' a''''] } r16 c'''''16 \grace { \stemNeutral fis''''![ d'''' b'''' ees''''!)] } r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  ees''!8 r4 } \clef bass \ottava #0  \arpeggioArrowDown < e'  aes! b, >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #-1 aes,,!16 b,,16 \clef bass \ottava #0  d,16 \grace { \stemNeutral b,[ c a \clef treble \ottava #0  f'] } \grace { \stemNeutral  <e'' g''>[ \clef treble \ottava #1  < cis'''! f'''>  <aes'''! e''''>  <bes''''! g''''>] } r8 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  fis,!8. \clef bass \ottava #-1 a,,16 r16 } 
\pitchedTrill
aes,,!2\startTrillSpan e,, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef treble \ottava #1  aes'''!4 r4 } 
\pitchedTrill
e''''2\startTrillSpan cis''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  bes''!8. cis''!16 r16 g'8. r4. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #-1 g,,16 r32 bes,,!16 \clef bass \ottava #0  e,16 cis!16 \grace { \stemNeutral b[ \clef treble \ottava #0  fis'! d'' f''] } r32 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  ees,!8. r16 \clef bass \ottava #-1 f,,16  } 
\pitchedTrill
bes,,,!2\startTrillSpan d,, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  bes!8 r4 } \arpeggioArrowUp < ees'! g' e'' c''' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef treble \ottava #1  aes'''!8( f''''8 r16 a''''8) r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  f''''16. r32 cis''''!32 bes'''!16 r8.. e'''16. r32 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #-1 b,,8 r16 cis,,!16( \grace { \stemNeutral e,,[ bes,,! \clef bass \ottava #0  g, aes,!] } r8. c16 \grace { \stemNeutral ees![ a \clef treble \ottava #0  f' d'')] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #0  d8( b8 r16 \clef treble \ottava #0  g'8) r4 } \breathe
\bar "|."
}
}
eletronicii = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 g,,16. bes,,,!32 e,,16 c,,16.  } \breathe
\clef bass \ottava #-1 f,,8 r8 \clef treble \ottava #2 < fis''''!  ees''''! a''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  d'16 \clef bass \ottava #0  f16 d16 \grace { \stemNeutral b,[ \clef bass \ottava #-1 c, ees,,! g,,] } \grace { \stemNeutral <fis,,! a,,>[ <ees,,! b,,> <aes,,! d,,> <aes,,! f,,>] } r8 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  aes'''!8. f''''16 fis''''!8. r4. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  g''16. r32 b'32 r32 aes'!16 e'16. r8.. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  bes'''!16 cis''''!32 ees''''!16. aes''''!16.  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  cis''!8. f'16 r8. bes!8. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  a''''8( ees''''!8 c''''8)  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  g''8. \clef treble \ottava #1  cis'''!16 a'''8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { r16 \clef bass \ottava #0  d,16 \clef bass \ottava #-1 f,,32 e,,16. c,,16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  cis''!8. ees''!16 aes''!8. r4. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #-1 a,,8. d,,16 fis,,!8. r4. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  ees'!4 r8 } fis'!4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  aes,!16 e,32 r32 \clef bass \ottava #-1 g,,16. r32 b,,16. r8.. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  bes''''!4 r8 } 
\pitchedTrill
e''''2\startTrillSpan g'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #1  cis''''!16 g'''32 r32 e'''16. r16 \clef treble \ottava #0  c'''16. r8 r32 } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #0  g'4  } \repeat tremolo 8 { \clef treble \ottava #1  < bes'! a''  f''' d'''' >32  < aes''''! c''''' ees''''! b'''' > } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  cis'!8( f'8 fis'!8)  } \breathe
\clef treble \ottava #0  aes''!8 r8 \clef treble \ottava #2 < c''''! f''''! g''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  fis,!16 ees!32 r32 a16. c'16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8. \clef treble \ottava #0  b'8 r8 } \clef bass \ottava #0  \arpeggioArrowDown < e'  aes! f >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  fis''''!8 e''''8 r8 } \clef treble \ottava #2 < cis''''! g''''! bes''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  d'''8. r8 bes''!16 r4 } 
\pitchedTrill
a''2\startTrillSpan c'' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  c'''''4 r8 } 
\pitchedTrill
fis''''!2\startTrillSpan ees''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #-1 g,,8 r16 r16 aes,,!16( \grace { \stemNeutral f,,[ b,, d,, e,,] } r8. a,,16 \grace { \stemNeutral cis,,![ bes,,,! fis,,! c,,)] }  } \breathe
\tupletSpan 4
\tuplet 7/4 { r8. \clef treble \ottava #0  ees'!8 r8 } \clef treble \ottava #1  \arpeggioArrowUp < a' fis''!  e''' b''' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef treble \ottava #1  bes''''!16 cis''''!16 e'''16 \grace { \stemNeutral cis'''![ \clef treble \ottava #0  g'' e'' d''] } \grace { \stemNeutral \clef bass \ottava #0  <aes'!  b>[  <bes! c> \clef bass \ottava #-1 <ees,!  a,,>  <bes,,,! g,,>] } r16. } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  aes''!8. c'''16  } 
\clef treble \ottava #1 
\pitchedTrill
 ees'''!2\startTrillSpan a''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 fis,,!4 r8 } 
\pitchedTrill
a,,2\startTrillSpan aes,,! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef bass \ottava #0  bes,,!8. c,16 ees,!8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  d,16 \clef bass \ottava #-1 e,,16 r32 a,,16 cis,,!16 \grace { \stemNeutral bes,,,![ fis,,! c,, ees,,!] } r32 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  fis''!8. b''16 r16 } 
\pitchedTrill
cis'''!2\startTrillSpan e''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  bes'!8 r4 r16 } \clef bass \ottava #0  \arpeggioArrowDown < cis'!  g e d >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  cis'''!8( a''8 fis''!8)  } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #0  ees!16. g32 \clef treble \ottava #0  cis'!16 bes'!16. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #-1 bes,,!8 r16 e,,16( \grace { \stemNeutral c,,[ a,, cis,,! fis,,!] } r16 aes,,!16 \grace { \stemNeutral b,,[ f,, d,, ees,,!)] } r8. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  g''8( b'8 f'8)  } \breathe
\bar "|."
}
}
eletroniciii = { \absolute {
\tupletSpan 4
\tuplet 9/8 { r16 \clef treble \ottava #0  g''16. bes'!32 e'16 cis'!16. r8.. } \breathe
r16 \clef bass \ottava #-1 aes,,!8 r16 \clef treble \ottava #2 <  f''''! b''''! d''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  g'''16 r16 \clef treble \ottava #0  b''16 r16 aes''!16 \grace { \stemNeutral e''[ g' \clef bass \ottava #0  bes! fis!] } \grace { \stemNeutral  <ees! g,>[ \clef bass \ottava #-1 < c, e,,>  <cis,,! a,,>  <e,, c,,>] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  bes''''!8. e''''16 r8 g''''8. r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #-1 fis,,!16. r32 f,,32 r16 aes,,!16 d,,16. r8. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  ees''!16 g''32 \clef treble \ottava #1  e'''16. c''''16.  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  g'8. ees'!16 a8.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  b'8( fis'!8 e'8)  } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  aes'!8. f''16 r16 b''8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #-1 aes,,!16 r32 b,,32 bes,,,!16. fis,,!16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  cis''!8. bes''!16 e'''8. r4. } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef bass \ottava #-1 ees,,!8. r16 fis,,!16 r16 bes,,,!8. r8. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  g'''4 r8 } cis''''!4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  bes''!16 r32 cis''!32 r16. ees'!16. r32 aes!16. r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  d''4 r8 } 
\pitchedTrill
f''2\startTrillSpan g'' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  bes'''!16 cis'''!32 \clef treble \ottava #0  f''16. fis'!16.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  fis!4 r8 } \repeat tremolo 8 { \clef treble \ottava #0  <  d' cis''! e'' bes''! >32 \clef treble \ottava #1  <  g''' f'''' c''''' aes''''! > } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  cis''!8( r16 f''8 fis''!8) r4 r16 } \breathe
r16 \clef bass \ottava #-1 bes,,!8 r16 \clef treble \ottava #2 < g''''! f''''! c''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  d''16 e''32 r16 a''16. cis'''!16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #0  g''8 r8. } \clef bass \ottava #0  \arpeggioArrowDown < a' d'  fis! ees! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  c'''''8 e''''8 r8 } \clef treble \ottava #2 < g''''! cis''''! a''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  e''''8. g'''16 r16 } 
\pitchedTrill
fis'''!2\startTrillSpan d''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  cis'''!4 r8 } 
\pitchedTrill
aes'''!2\startTrillSpan e'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #1  a''''8 r16 cis''''!16( \grace { \stemNeutral fis'''![ \clef treble \ottava #0  aes''! b' f'] } d'16 \grace { \stemNeutral \clef bass \ottava #0  ees![ g, \clef bass \ottava #-1 bes,,! e,,)] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  ees,!8 r4 } \arpeggioArrowUp < g, bes,! e >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  bes'!16 r32 d'16 r32 \clef bass \ottava #0  f16 \grace { \stemNeutral cis![ g, e, \clef bass \ottava #-1 c,] } \grace { \stemNeutral <fis,,! bes,,,!>[ <cis,,! f,,> <aes,,! d,,> <b,, g,,>] } r16 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  fis'''!8. r16 ees''''!16  } 
\pitchedTrill
b''''2\startTrillSpan f'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef treble \ottava #0  a'4 r4 } 
\pitchedTrill
f'2\startTrillSpan aes! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  cis,!8. bes,!16 e8.  } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  g'16 r32 cis'!16 \clef bass \ottava #0  bes!16 r32 aes!16 \grace { \stemNeutral ees![ b, d, \clef bass \ottava #-1 fis,,!] }  } \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #-1 cis,,!8. r8 a,,16 r8. } 
\pitchedTrill
c,2\startTrillSpan e, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  f''8 r4 r16 } \clef bass \ottava #0  \arpeggioArrowDown < c'' aes'!  b ees! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef bass \ottava #0  aes,!8( r8 fis,!8 ees,!8) r8 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  bes'''!16. aes''''!32 ees''''!16 b''''16.  } \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef treble \ottava #0  b''8 r16 aes''!16( \grace { \stemNeutral e''[ ees''! fis'! \clef bass \ottava #0  c'] } r16 a16 \grace { \stemNeutral g[ d bes,! \clef bass \ottava #-1 cis,!)] } r8 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  a''''8( r16 b'''8 r16 d'''8) r4 } \breathe
\bar "|."
}
}
eletroniciv = { \absolute {
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #-1 g,,16. r32 cis,!32 \clef bass \ottava #0  e,16 ees!16. r8.. } \breathe
\clef bass \ottava #-1 d,,8 r8 \clef treble \ottava #2 < aes''''! f''''! cis''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  cis'!16 g'16 bes'!16 \grace { \stemNeutral e''[ aes''! \clef treble \ottava #1  f''' a'''] } \grace { \stemNeutral <f'''' b''''>[ <d'''' bes''''!> <cis''''! f''''> <d'''' aes''''!>] } r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  fis''''!8. a'''16 cis'''!8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  g'''16. c''''32 r16 e''''16 r16 cis''''!16. r8 r32 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  aes'''!16 g'''32 r16 ees'''!16. \clef treble \ottava #0  c'''16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #0  d''8. r16 aes''!16 b''8. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  c'''''8( r16 fis''''!8 ees''''!8) r4 r16 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #0  g8. a,16 d,8.  } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef bass \ottava #0  ees,!16 a,32 cis!16. e16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  bes''''!8. r8 e''''16 cis''''!8. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  aes'!8. e''16 b''8. r4. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  f'4 r8 } e'4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  a,16 c32 r16. d16. r16. g16. r16. } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #0  d''4 r8 } 
\pitchedTrill
aes'!2\startTrillSpan b r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  ees'''!16 e'''32 aes'''!16. r32 b'''16. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  g,4 r8 } \repeat tremolo 8 { \clef bass \ottava #-1 < e,  bes,,! cis,,! ees,,! >32  < aes,,! c,, a,, f,, > } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  bes'''!8( r16 e'''8 \clef treble \ottava #0  c'''8) r4 r16 } \breathe
r16 \clef treble \ottava #1  cis''''!8 r16 \clef treble \ottava #2 < bes''''! e''''! aes''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #1  fis''''!16 a'''32 ees'''!16. \clef treble \ottava #0  c'''16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #1  aes''''!8 r4 r16 } \arpeggioArrowUp < e'''' bes''''! cis''''! f'''' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef bass \ottava #0  fis!8 r16 bes,!8 r4 r16 } \clef treble \ottava #2 < g''''! ees''''! a''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef treble \ottava #0  e''8. bes''!16  } 
\clef treble \ottava #1 
\pitchedTrill
 cis'''!2\startTrillSpan c'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef treble \ottava #1  b'''4 r4 } 
\pitchedTrill
d'''2\startTrillSpan fis''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  g''''8 r16 fis''''!16( \grace { \stemNeutral d''''[ b'''' f'''' a''''] } c'''''16 \grace { \stemNeutral aes''''![ ees''''! cis''''! bes''''!)] }  } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef treble \ottava #0  bes''!8 r8. } \clef bass \ottava #0  \arpeggioArrowDown < cis''! g' e'  f >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  fis!16 c'16 \clef treble \ottava #0  e'16 \grace { \stemNeutral bes'![ cis''! a'' c'''] } \grace { \stemNeutral \clef treble \ottava #1  < a''' ees''''!>[  <g'''' e''''>  <aes''''! cis''''!>  <a'''' ees''''!>] } r8 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  cis''!8. r16 bes'!16  } 
\pitchedTrill
e'2\startTrillSpan aes! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  bes'''!4 r8 } 
\pitchedTrill
fis''''!2\startTrillSpan f'''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 aes,,!8. r16 f,,16 ees,,!8. r4. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  d'16 b'16 a''16 r16. \clef treble \ottava #1  e'''16 \grace { \stemNeutral c''''[ ees''''! g'''' cis''''!] } r8. r16. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  b''''8. f''''16 r16 } 
\pitchedTrill
aes'''!2\startTrillSpan bes''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r8. \clef treble \ottava #1  ees'''!8 r8 } \arpeggioArrowUp < c'''' fis''''! bes''''! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef treble \ottava #0  aes!8( r16 a8 r8. cis'!8) r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  bes!16. a32 c16 r16 fis,!16. r8.. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  cis!8 r16 bes!16( \grace { \stemNeutral \clef treble \ottava #0  d'[ g' a' c''] } fis''!16 \grace { \stemNeutral \clef treble \ottava #1  ees'''![ e''' aes'''! b''')] }  } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #-1 g,,8( \clef bass \ottava #0  ees,!8 r16 fis,!8) r4 } \breathe
\bar "|."
}
}
eletronicv = { \absolute {
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #1  g'''16. ees'''!32 \clef treble \ottava #0  a''16 r32 c''16. r4 } \breathe
\clef treble \ottava #1  cis''''!8 r8 \clef treble \ottava #2 < f''''! d''''! bes''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef treble \ottava #1  g''''16 f''''16 d''''16 \grace { \stemNeutral e'''[ \clef treble \ottava #0  g'' bes'! \clef bass \ottava #0  c'] } \grace { \stemNeutral  <a g>[  <d c>  <a, ees,!> \clef bass \ottava #-1 < aes,,! bes,,,!>] } r16. } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef bass \ottava #-1 cis,,!8. r8 fis,,!16 r8 bes,,!8. r8. } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  bes,!16. \clef bass \ottava #-1 b,,32 ees,,!16 r32 fis,,!16. r4 } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  bes!16 r32 d'32 r32 ees'!16. c''16. r8.. } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  g''8. b'16 aes'!8.  } \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #0  bes,!8( \clef bass \ottava #-1 cis,!8 g,,8)  } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  bes''!8. \clef treble \ottava #1  d'''16 r8 f'''8. r4 r16 } \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #0  cis''!16 ees'!32 \clef bass \ottava #0  fis!16. c16. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #0  aes''!8. r16 \clef treble \ottava #1  f'''16 r16 a'''8. r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { \clef treble \ottava #0  bes''!8. e''16 g'8.  } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #0  g'4  } ees''!4:64 \breathe
\tupletSpan 4
\tuplet 9/8 { r32 \clef treble \ottava #1  bes''''!16 a''''32 f''''16. r32 d''''16. r8.. } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #0  bes''!4  } 
\clef treble \ottava #1 
\pitchedTrill
 d'''2\startTrillSpan g''' r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  cis!16 f,32 r32 \clef bass \ottava #-1 fis,,!16. ees,,!16. r4 } \breathe
\tupletSpan 4
\tuplet 3/2 { r2 r8 \clef bass \ottava #0  ees!4 r4 } \repeat tremolo 8 { \clef treble \ottava #0  < b  aes'! c'' f'' >32 \clef treble \ottava #1  < g'' bes''!  e''' cis''''! > } \breathe
\tupletSpan 4
\tuplet 3/2 { r16 \clef bass \ottava #0  fis,!8( a,8 b,8) r4 r16 } \breathe
r16 \clef bass \ottava #-1 cis,!8 r16 \clef treble \ottava #2 < g''''! e''''! d''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 9/8 { \clef bass \ottava #0  a,16 e32 c'16. ees'!16.  } \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef treble \ottava #1  g'''8 r4 } \clef treble \ottava #0  \arpeggioArrowDown < fis'''!  a'' ees''! c'' >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { r4 \clef bass \ottava #-1 f,,8 bes,,!8 r4 } \clef treble \ottava #2 < c''''!  ees''''! a''''! >16 \ottava #0 r8. \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef treble \ottava #0  d'''8. b''16 r4 } 
\pitchedTrill
f''2\startTrillSpan aes'! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef treble \ottava #1  aes''''!4  } 
\pitchedTrill
e''''2\startTrillSpan cis''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 5/4 { r16 \clef bass \ottava #-1 bes,,,!8 r16 g,,16( \grace { \stemNeutral aes,,![ c,, ees,,! a,,] } f,,16 \grace { \stemNeutral d,,[ fis,,! b,, cis,,!)] } r4 } \breathe
\tupletSpan 4
\tuplet 7/4 { r8 \clef bass \ottava #0  bes,,!8 r8. } \arpeggioArrowUp < cis,! f, fis,! ees! >4\arpeggio \breathe
\tupletSpan 4
\tuplet 5/4 { r32 \clef treble \ottava #1  cis'''!16 \clef treble \ottava #0  g''16 e''16 \grace { \stemNeutral bes'![ cis'! \clef bass \ottava #0  e bes,!] } \grace { \stemNeutral \clef bass \ottava #-1 <g,  cis,!>[  <e,, bes,,,!>  <g,, ees,,!>  <c,, fis,,!>] } r16. } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef bass \ottava #0  ees,!8. r16 b,16  } 
\pitchedTrill
d2\startTrillSpan fis! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 3/2 { \clef bass \ottava #-1 a,,4 r8 } 
\pitchedTrill
fis,,!2\startTrillSpan e,, r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r8. \clef bass \ottava #0  fis,!8. bes,!16 cis!8. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { r8 \clef treble \ottava #0  g'16 cis'!16 r32 \clef bass \ottava #0  bes!16 r16 b,16 \grace { \stemNeutral ees,![ \clef bass \ottava #-1 fis,,! c,, aes,,!] } r8 r32 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #1  aes'''!8. r16 f''''16  } 
\pitchedTrill
ees''''!2\startTrillSpan bes''''! r4\stopTrillSpan \breathe
\tupletSpan 4
\tuplet 7/4 { r16 \clef bass \ottava #0  fis!8 r4 } \arpeggioArrowDown < a, aes,! e, >4\arpeggio \breathe
\tupletSpan 4
\tuplet 3/2 { \clef treble \ottava #1  bes'''!8( e'''8 \clef treble \ottava #0  aes''!8)  } \breathe
\tupletSpan 4
\tuplet 9/8 { \clef treble \ottava #0  d''16. r32 b''32 \clef treble \ottava #1  f'''16 a'''16. r4 } \breathe
\tupletSpan 4
\tuplet 5/4 { \clef treble \ottava #0  ees''!8 r16 a'16( \grace { \stemNeutral cis'![ \clef bass \ottava #0  e c g,] } f,16 \grace { \stemNeutral d,[ \clef bass \ottava #-1 aes,,! b,, bes,,,!)] }  } \breathe
\tupletSpan 4
\tuplet 3/2 { r8 \clef bass \ottava #0  a8( r16 g8 e8) r8. } \breathe
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
