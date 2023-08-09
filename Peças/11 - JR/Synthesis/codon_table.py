met=['a','u','g']
ile=[['a','u','u'],['a','u','c'],['a','u','a']]
val=[['g','u','u'],['g','u','c'],['g','u','a'],['g','u','g']]
leu=[['c','u','u'],['c','u','c'],['c','u','a'],['c','u','g'],['u','u','a'],['u','u','g']]
phe=[['u','u','u'],['u','u','c']]
ala=[['g','c','u'],['g','c','c'],['g','c','a'],['g','c','g']]
thr=[['a','c','u'],['a','c','c'],['a','c','a'],['a','c','g']]
pro=[['c','c','u'],['c','c','c'],['c','c','a'],['c','c','g']]
ser=[['u','c','u'],['u','c','c'],['u','c','a'],['u','c','g'],['a','g','u'],['a','g','c']]
glu=[['g','a','a'],['g','a','g']]
asp=[['g','a','u'],['g','a','c']]
lys=[['a','a','a'],['a','a','g']]
asn=[['a','a','u'],['a','a','c']]
gln=[['c','a','a'],['c','a','g']]
his=[['c','a','u'],['c','a','c']]
tyr=[['u','a','u'],['u','a','c']]
gly=[['g','g','u'],['g','g','c'],['g','g','a'],['g','g','g']]
arg=[['c','g','u'],['c','g','c'],['c','g','a'],['c','g','g'],['a','g','a'],['a','g','g']]
trp=['u','g','g']
cys=[['u','g','u'],['u','g','c']]
stop=[['u','a','a'],['u','a','g'],['u','g','a']]
aminolist=[met,ile,val,leu,phe,ala,thr,pro,ser,glu,asp,lys,asn,gln,his,tyr,gly,arg,trp,cys,stop]
aminostring=['met','ile','val','leu','phe','ala','thr','pro','ser','glu','asp','lys','asn','gln','his','tyr','gly','arg','trp','cys','stop']

def aminoacid(codon=[]):
	amino=0
	name=''
	for i in aminolist:
		if codon in i:
			amino=aminolist.index(i)
			name=aminostring[amino]
			break
	return amino, name


		