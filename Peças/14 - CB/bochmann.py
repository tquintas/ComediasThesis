import os		
import sys
file_dir=os.path.dirname(__file__)
sys.path.append(file_dir)
print('Functions "bochmann", "nbochmann" and "oeis"')
allphrases=[]
def isPrime(n):
    if n<=1: return False
    for k in range(2,int(n**(1/2)+1)):
        if n%k==0:
            return False
    return True
def rangeP(n):
	l = [i for i in range(n) if isPrime(i)]
	return (j for j in l)
class hidePrints:
    def __enter__(self):
        self._original_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')

    def __exit__(self, exc_type, exc_val, exc_tb):
        sys.stdout.close()
        sys.stdout = self._original_stdout
def bochmann(transposition=0,mod=2,biggest_interv=11):
	notes=["C","C#","D","Eb","E","F","F#","G","Ab","A","Bb","B"]
	lucasseq=[]
	a,b,c,d=2,1,1,0
	lucasseq.append(c)
	y=1
	zeros=[]
	lucassum=0
	n_of_phrases=1
	repeated=0
	phrases=[]
	def glob():
		global allphrases
		allphrases=phrases
	while True:
		while True:
			c=a+b
			a=b
			b=c
			d=(c%(biggest_interv+1))*pow(-1,(y%mod))
			lucasseq.append(d)
			lucassum=sum(lucasseq[0:y])%12
			if lucassum==0:
				zeros.append(y)
			y+=1
			if len(zeros)>=n_of_phrases:
				break
		zeros=zeros[0:n_of_phrases]
		upper,lower=0,0
		seq=[]
		seq1=[]
		summ=0
		phrase=[]
		for x in range(len(zeros)):
			x+=1
			upper=x-1
			lower=x-2
			if lower<0:
				lower=0
			else:
				lower=zeros[lower]
			upper=zeros[upper]
			seq=lucasseq[lower:upper]
			for z in range(len(seq)):
				z+=1
				seq1=seq[0:z]
				summ=(sum(seq1)+transposition)%12
				phrase.append(notes[summ])
			phrases.append(phrase)
			repeated=phrases.count(phrase)
			if repeated>1:
				del phrases[x-1]
				glob()
				for j in phrases:
					print('Phrase',(phrases.index(j)+1),j,'\n')
				return
			phrase=[]
		n_of_phrases+=1
		phrases=[]
def nbochmann(n_of_notes=6,transposition=0,mod=2,biggest_interv=11):
	index=0
	while True:
		with hidePrints():
			bochmann(transposition,mod,biggest_interv)
		for i in allphrases:
			if len(i)==n_of_notes:
				index=allphrases.index(i)+1
				print('Phrase',index,i,'\n')
		else:
			if index==0:
				print('No Phrases with',n_of_notes,'notes')
			return
def oeis(r1,r2):
	for i in r1:
		l = []
		for j in r2:
			if j<=1: continue
			with hidePrints():
				bochmann(0,i,j)
			c = len(allphrases)
			s = sum((len(i) for i in allphrases))
			l.append((c,s))
		print(l)
