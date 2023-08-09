import os,sys
import codon_table as ct
import random2 as r
import matrix as mtx

class hidePrints:
    def __enter__(self):
        self._original_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')

    def __exit__(self, exc_type, exc_val, exc_tb):
        sys.stdout.close()
        sys.stdout = self._original_stdout

def dna(bases=[]):
        index=0
        DNA_base=['a','t','c','g']
        tRNA_base=['a','u','g','c']
        mrna=[]
        for x in range(len(bases)):
                index=bases[x]
                index=DNA_base.index(index)
                index=tRNA_base[index]
                mrna.append(index)
        while (len(mrna)%3)!=0:
                del mrna[-1]
        protein_num=[]
        protein_nam=[]
        updown=[]
        num,nam=0,''
        ups_downs=0
        k=0
        for n in range(int(len(mrna)/3)):
                codon=mrna[(3*n):(3*(n+1))]
                num,nam=ct.aminoacid(codon)
                protein_num.append(num)
                protein_nam.append(nam)
                if n==0:
                        ups_downs=r.randint(0,1)
                        if ups_downs==0:
                                k=0
                        else:
                                k=1
                elif nam=='pro' or nam=='gly':
                        pass
                else:
                        k+=1
                updown.append(k%2)
        for i,j in enumerate(updown):
                if j==0:
                        updown[i]='Down'
                else:
                        updown[i]='Up'
        return protein_num, updown, protein_nam

class sidechain:
        carbons=['c','h','ch','chh','chhh']
        def __init__(self,name):
                """Name the aminoacid"""
                self.name=name
                self.struct=[]
                self.rest_prob=0
                self.hs=0
                self.duration=0
                self.note_line=[]
        def add_struct(self,struct=[]):
                """Add the structure of the aminoacids"""
                self.struct=struct
                for x in self.struct:
                        self.hs+=x.count('h')
                if self.hs==0:
                        self.duration=2
                elif self.hs==1:
                        self.duration=4
                elif self.hs==3:
                        self.duration=8
                elif self.hs>=4 and self.hs<=7:
                        self.duration=16
                elif self.hs>=8:
                        self.duration=32
        def rest_probability(self,p=int):
                """Add the probability of rests (could be measured by the BLOSUM matrix)"""
                if type(p)!=int:
                        self.rest_prob=int(input('What is the rest probability for {}?'.format(self.name)))
                else:
                        self.rest_prob=p
        def durations(self):
                """Define the type and duration of the notes"""
                self.note_line=[]
                h=0
                loopy=0
                entry='{}'
                chord=''
                for l,k in enumerate(self.struct):
                        if k in sidechain.carbons:
                                h=k.count('h')
                                if h==0:
                                        self.note_line.append('r'+str(self.duration))
                                elif h==1:
                                        self.note_line.append(entry+str(self.duration))
                                elif h==2:
                                        self.note_line.append(entry+str(int(self.duration/2)))
                                elif h==3:
                                        self.note_line.append(entry+str(int(self.duration/2))+'.')
                        elif 's' in k:
                                self.note_line.append('fill')
                                self.note_line.append('{}4:64')
                        elif 'ho' in k:
                                self.note_line.append('fill')
                                if 'ring' not in self.struct[l-1]:
                                        self.note_line.append('\n\\pitchedTrill\n{}2\\startTrillSpan {} r4\\stopTrillSpan')
                                else:
                                        chord='{} '*(r.randint(0,1)+3)
                                        self.note_line.append('\\arpeggioArrow{} < '+chord+'>4\\arpeggio \\startTrillSpan {}4\\stopTrillSpan')
                        elif 'ring' in k:
                                try:
                                        if 'ho' not in self.struct[l+1]:
                                                self.note_line.append('fill')
                                                chord='{} '*(r.randint(0,1)+3)
                                                self.note_line.append('\\arpeggioArrow{} < '+chord+'>4\\arpeggio')
                                        else:
                                                continue
                                except IndexError:
                                        self.note_line.append('fill')
                                        chord='{} '*(r.randint(0,1)+3)
                                        self.note_line.append('\\arpeggioArrow{} < '+chord+'>4\\arpeggio')
                        elif 'cooh' in k:
                                self.note_line.append('fill')
                                chord='{} '*(r.randint(0,1)+3)
                                self.note_line.append('\\repeat tremolo 8 $ < '+chord+'>32 < '+chord+'> %')
                        elif 'n' in k and 'nn' not in k and 'amino' not in k:
                                self.note_line.append('\\grace $ \\stemNeutral {}[ {} {} {}] %')
                        elif 'nn' in k:
                                self.note_line.append('\\grace $ \\stemNeutral <{} {}>[ <{} {}> <{} {}> <{} {}>] %')
                                self.note_line.append('fill')
                        elif 'amino' in k:
                                self.note_line.append('fill')
                                self.note_line.append("\\clef treble \\ottava #2 < {}''''! {}''''! {}''''! >16 \\ottava #0 r8.")
                        elif 'loop' in k:
                                if 'ring' in self.struct[l-1]:
                                        self.note_line[-1]=self.note_line[-1][:3]+')'+self.note_line[-1][3:]
                                elif 'n' in self.struct[l-1]:
                                        self.note_line[-1]=self.note_line[-1][:-3]+')'+self.note_line[-1][-3:]
                                else:
                                        self.note_line[-1]=self.note_line[-1]+')'
                                loopy=int(k[-1])
                                self.note_line[loopy]=self.note_line[loopy]+'('
                else:
                        if 'fill' not in self.note_line:
                                self.note_line.append('fill')
                return self.note_line
        def tuplets(self):
                """Finnish a tuplet line with the correct number of notes and rests"""
                p=0
                h,h1=0,0
                rest='r'
                line2=''
                fill=''
                count,rests,total=0,0,0
                self.tuplet_line=[]
                self.tuplet_line=self.durations().copy()
                def concatenate(count):
                        line=''
                        if count==0:
                                pass
                        elif count==1:
                                line+=rest+str(self.duration)+' '
                        elif count==2:
                                line+=rest+str(int(self.duration/2))+' '
                        elif count==3:
                                line+=rest+str(int(self.duration/2))+'. '
                        elif count==4:
                                line+=rest+str(int(self.duration/4))+' '
                        elif count==5:
                                line+=rest+str(int(self.duration/4))+' '
                                line+=rest+str(self.duration)+' '
                        elif count==6:
                                line+=rest+str(int(self.duration/4))+'. '
                        elif count==7:
                                line+=rest+str(int(self.duration/4))+'.. '
                        elif count==8:
                                line+=rest+str(int(self.duration/8))+' '
                        elif count==9:
                                line+=rest+str(int(self.duration/4))+'. '
                                line+=rest+str(int(self.duration/2))+'. '
                        elif count==10:
                                line+=rest+str(int(self.duration/4))+'. '
                                line+=rest+str(int(self.duration/4))+' '
                        return line
                def rests_until_note():
                        """Insert random number of rests"""
                        line=''
                        count=0
                        while True:
                                if self.rest_prob!=1:
                                        try:
                                                p=(r.randint(1,self.rest_prob))%self.rest_prob
                                        except ZeroDivisionError:
                                                p=1
                                else:
                                        p=1
                                if p==0:
                                        count+=1
                                else:
                                        line=concatenate(count)
                                        line+='{}'
                                        return line, count
                for i,j in enumerate(self.struct):
                        if j in sidechain.carbons:
                                h=j.count('h')
                                if h==0:
                                        h=1
                                line2,count=rests_until_note()
                                rests+=count
                                h1+=h
                                self.tuplet_line[i]=line2.format(self.note_line[i])
                else:
                        try:
                                total=(self.hs-(h1+rests))%self.hs
                        except ZeroDivisionError:
                                total=(self.hs-(h1+rests))%1
                        fill=concatenate(total).removesuffix(' ')
                        self.tuplet_line[self.tuplet_line.index('fill')]=fill
                        if self.hs==0:
                                self.tuplet_line=['r2']
                        elif self.hs==3:
                                self.tuplet_line[self.note_line.index('fill')]=fill+' %'
                                self.tuplet_line.insert(0,'\\tupletSpan 4\n\\tuplet 3/2 $')
                        elif self.hs>=5 and self.hs<=7:
                                self.tuplet_line[self.note_line.index('fill')]=fill+' %'
                                self.tuplet_line.insert(0,'\\tupletSpan 4\n\\tuplet {}/4 $'.format(self.hs))
                        elif self.hs>=9:
                                self.tuplet_line[self.note_line.index('fill')]=fill+' %'
                                self.tuplet_line.insert(0,'\\tupletSpan 4\n\\tuplet {}/8 $'.format(self.hs))
                return self.tuplet_line
        def notes_need(self):
                """Return how many notes you need"""
                self.brackets=0
                for i in self.tuplet_line:
                        self.brackets+=i.count('{}')
                return self.brackets

aminostring=['met','ile','val','leu','phe','ala','thr','pro','ser','glu','asp','lys','asn','gln','his','tyr','gly','arg','trp','cys','stop']
                
M=sidechain('met')
M.add_struct(['chh','chh','chhh','s'])

I=sidechain('ile')
I.add_struct(['chhh','ch','chh','chhh'])

V=sidechain('val')
V.add_struct(['chhh','ch','chhh'])

L=sidechain('leu')
L.add_struct(['chh','ch','chhh','chhh'])

F=sidechain('phe')
F.add_struct(['chh','ringhhhhh'])

A=sidechain('ala')
A.add_struct(['chhh'])

T=sidechain('thr')
T.add_struct(['chhh','ch','ho'])

P=sidechain('pro')
P.add_struct(['chh','chh','chh','loop0'])

S=sidechain('ser')
S.add_struct(['chh','ho'])

E=sidechain('glu')
E.add_struct(['chh','chh','cooh'])

D=sidechain('asp')
D.add_struct(['chh','cooh'])

K=sidechain('lys')
K.add_struct(['chh','chh','chh','chh','nhh'])

N=sidechain('asn')
N.add_struct(['chh','aminohh'])

Q=sidechain('gln')
Q.add_struct(['chh','chh','aminohh'])

H=sidechain('his')
H.add_struct(['chh','c','ch','nh','ch','n','loop2'])

Y=sidechain('tyr')
Y.add_struct(['chh','ringhhhh','ho'])

G=sidechain('gly')
G.add_struct(['h'])

R=sidechain('arg')
R.add_struct(['chh','chh','chh','nh','cnnhhh'])

W=sidechain('trp')
W.add_struct(['chh','c','ch','nh','ringhhhh','loop2'])

C=sidechain('cys')
C.add_struct(['chh','hs'])

stop=sidechain('stop')
stop.add_struct([])
stop.rest_probability(1)

aminolist2=[M,I,V,L,F,A,T,P,S,E,D,K,N,Q,H,Y,G,R,W,C,stop]

def create_tuplet(n):
        """Return the aminoacid side chain tuplet line and its orientation"""
        score=[]
        mo=[]
        for i,j in n:
                x=aminolist2[i]
                mo=x.tuplets()
                if x==F or x==Y or x==W:
                        for l,k in enumerate(mo):
                                mo[l]=k.replace('Arrow{}','Arrow'+j)
                mo=' '.join(k for k in mo)+' \\breathe'
                score.append((mo,j,x.notes_need()))
        return score

def note_range(x=['complete']):
        """Return the range of the instrument"""
        notes=['c','cis','d','ees','e','f','fis','g','aes','a','bes','b']
        global octaves
        octaves=[',,' , ',' , '' , "'" , "''" , "'''" , "''''"]
        oct_mark=''
        a,b=0,0
        noterange=['a,,,','bes,,,','b,,']
        for o in octaves:
                oct_mark='{}'+o
                for a in notes:
                        noterange.append(oct_mark.format(a))
        else:
                noterange.append("c'''''")
        if x==['complete']:
                pass
        else:
                a=noterange.index(x[0])
                b=noterange.index(x[1])+1
                noterange=noterange[a:b]
        noterange=[i+'!' if 'is' in i or 'es' in i else i for i in noterange]
        return noterange

def motion(m,d):
        """Return the ascending or descending line of notes"""
        notes=['c','cis','d','ees','e','f','fis','g','aes','a','bes','b']
        where=0
        shift=lambda x,y: [x[(i+y)%len(x)] for i in range(len(x))]
        indexes=lambda n,x: [i for i,j in enumerate(n) if x in j]
        p=0
        motion=[]
        choice=r.choice(indexes(amplitude,m[0]))
        clef=''
        if d=='Up':
                ampli=len(amplitude)-choice
                notes2=shift(notes,notes.index(m[0]))
                for i in m:
                        p+=notes2.index(i)
                        if p>ampli:
                                p-=12
                        motion.append(p)
                        notes2=shift(notes,notes.index(i))
        elif d=='Down':
                ampli=choice
                notes.reverse()
                notes2=shift(notes,notes.index(m[0]))
                for i in m:                             
                        p-=notes2.index(i)              
                        if p<-ampli:       
                                p+=12
                        motion.append(p)
                        notes2=shift(notes,notes.index(i))
        start=amplitude[choice]
        start_index=amplitude.index(start)
        motion=[a+start_index for a in motion]
        motion=[amplitude[i] for i in motion]
        return motion

def midclef(melody):
        def which_one(i):
                c=''
                if 64<=complete_amplitude.index(i)<=87:
                        c='\\clef treble \\ottava #1  '
                elif 0<=complete_amplitude.index(i)<=16:
                        c='\\clef bass \\ottava #-1 '
                elif 40<=complete_amplitude.index(i)<=63:
                        c='\\clef treble \\ottava #0  '
                elif 17<=complete_amplitude.index(i)<=39:
                        c='\\clef bass \\ottava #0  '
                return c
        melodycopy=melody.copy()
        for i,j in enumerate(melodycopy[1:]):
                if which_one(j)==which_one(melodycopy[i]):
                        continue
                else:
                        melody[i+1]=which_one(j)+melody[i+1]
        melody[0]=which_one(melody[0])+melody[0]
        return melody

def clef(melody):
        clef=''
        if all(64<=complete_amplitude.index(i)<=87 for i in melody):
                clef='\\clef treble \\ottava #1  '
        elif all(0<=complete_amplitude.index(i)<=16 for i in melody):
                clef='\\clef bass \\ottava #-1 '
        elif all(34<=complete_amplitude.index(i)<=67 for i in melody):
                clef='\\clef treble \\ottava #0  '
        elif all(12<=complete_amplitude.index(i)<=43 for i in melody):
                clef='\\clef bass \\ottava #0  '
        else:
                melody=midclef(melody)                        
        melody[0]=clef+melody[0]
        return melody

def section(l):
        final=''
        sect=''
        cleff=''
        cleff2=''
        cleff3=[]
        melody=[]
        for i,j in enumerate(l):
                if j[2]==0:
                        final+='\\bar "|."'
                        break
                if j[2]>len(protein_matrix.matrix):
                        melody=protein_matrix.sectspiralout(main_series[i],j[2])
                else:
                        melody=protein_matrix.sectbg(main_series[i],j[2])
                melody=motion(melody,j[1])
                melody=clef(melody)
                if '#2' in j[0]:
                        for k in [-1,-2,-3]:
                                melody[k]=melody[k].replace("'","").replace(',','').replace('!','')
                sect=j[0].format(*melody)+'\n'
                if "\\pitchedTrill\n\\clef" in sect:
                        cleff=sect[(sect.index('Trill\n\\clef')+6):(sect.index('#',sect.index('Trill\n\\clef'))+3)]
                        sect=sect.replace("\\pitchedTrill\n"+cleff,cleff+'\n'+"\\pitchedTrill\n")
                if "Span \\clef" in sect:
                        cleff=sect[sect.index('Span \\clef'):sect.index('#',sect.index('Span \\clef'))+3]
                        sect=sect.replace(cleff,'Span')
                sect=sect.replace('\\tuplet 6/4','\\tuplet 3/2')
                sect=sect.replace('\\tuplet 10/8','\\tuplet 5/4')
                if '<' in sect and '>' in sect:
                        cleff=sect[sect.index('<'):sect.rindex('>')+1]
                        while 'ottava' in cleff:
                                if '> <' not in cleff and '>32 <' not in cleff:
                                        cleff2=cleff.replace(cleff[cleff.index('\\clef'):cleff.index('#')+3],'')
                                        if 'Arrow' in sect:
                                                sect=sect.replace('\\arpeggioArrow',cleff[cleff.index('\\clef'):cleff.index('#')+3]+' \\arpeggioArrow')
                                        sect=sect.replace(cleff,cleff2)
                                else:
                                        cleff3=cleff.split('>')
                                        for j,k in enumerate(cleff3):
                                                cleff2=''
                                                while 'ottava' in k:
                                                        cleff2=k[k.index('\\clef'):k.index('#')+3]
                                                        k=k.replace(cleff2,'')
                                                else:
                                                        cleff3[j]=k.replace('<',cleff2+' <')
                                        else:
                                                cleff2='>'.join(cleff3)
                                        sect=sect.replace(cleff,cleff2)
                                        break
                                cleff=sect[sect.index('<'):sect.rindex('>')+1]
                final+=sect
        final=final.replace("$","{").replace("%","}")
        return final

def new(prob=str,rest4all=int,seq=str,series=str,name=str,ampli=str):
        while True:
                p=0
                if (prob!='y' and prob!='n') or type(prob)!=str:
                        input1=input('Do you want to specify the rest probabilities? (y/n) ')
                else:
                        input1=prob
                if input1=='y':
                        for i in range(len(aminostring)-1):
                                p=int(input('Rest probability for {}? (1 in n) '.format(aminostring[i])))
                                aminolist2[i].rest_probability(p)
                        break
                elif input1=='n':
                        if type(rest4all)!=int or rest4all==int:
                                p=int(input('Rest probability for all aminoacids? (1 in n) '))
                        else:
                                p=rest4all
                        for i in range(len(aminolist2)-1):
                                aminolist2[i].rest_probability(p)
                        break
                else:
                        continue
        if seq==str or type(seq)!=str:
                seq=input('Enter the dna sequence.\n')
        seq=[letter for letter in seq]
        protein_num,updown,protein_nam=dna(seq)
        tupl=[(protein_num[i],updown[i]) for i in range(len(protein_num))]
        score=create_tuplet(tupl)
        if series==str or type(series)!=str:
                input_matrix=input("Insert series: ").split()
        else:
                input_matrix=series.split()
        global protein_matrix
        with hidePrints():
                protein_matrix=mtx.new('prot',input_matrix)
                protein_matrix.set_matrix_to_notes()
        global main_series
        main_series=mtx.prot.sectspiralout(protein_matrix.prime[0],len(protein_num))
        global instr_name
        if name==str or type(name)!=str:
                instr_name=input('Name of the instrument: ').lower()
        else:
                instr_name=name
        if ampli==str or type(ampli)!=str:
                amp=input('Instrument amplitude: ').split(' ')
        else:
                amp=ampli.split(' ')
        global amplitude
        amplitude = note_range(amp)
        global complete_amplitude
        complete_amplitude=note_range()
        music=section(score)
        return music
