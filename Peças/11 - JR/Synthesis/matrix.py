import random2
import sys
import os
from zprime import Zp, isOddPrime
import melody
from melody import amplitude
import math

def help():
    print("""
Module: matrix.py
Author: Tiago Quintas
Description:

Musical Matrix Maker module.

Insert the number of notes corresponding to your prime serie and the note names.

The names should follow the Dutch naming convention, due to LilyPond compatibility.

The possible funtions are:

	__class__() --> Set up a new matrix.
	__class__.Pn() --> Return all the nth primes.
	__class__.Rn() --> Return all the nth retrogrades.
	__class__.In() --> Return all the nth inversions.
	__class__.RIn() --> Return all the nth retrograde-inversions.
	__class__.sectbg() --> Return a section of the matrix, starting on a specific note.
	__class__.sectend() --> Return a section of the matrix, ending on a specific note.
	__class__.sectspiralout() --> Return a spiraling section of the matrix, starting on a specific note.
	__class__.sectspiralin() --> Return a spiraling section of the matrix, ending on a specific note.
	__class__.set_matrix_to_notes() --> Change the matrix to display only note names.
	__class__.set_matrix_to_numbers() --> Change the matrix to display only note values.

""")


class hidePrints:
    def __enter__(self):
        self._original_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')

    def __exit__(self, exc_type, exc_val, exc_tb):
        sys.stdout.close()
        sys.stdout = self._original_stdout


class matrix:
    dic={'monody':'', 'only_names':True}
    def __new__(cls,name='', melody=[], matrix=[], only_names=True, microtonality=False, octave_division=12):
        """Set up a new matrix."""
        if name == '' or type(name) != str:
            obj = object.__new__(cls)
            return obj
        else:
            globals()[name]= object.__new__(cls)
            return globals()[name]
    
    def __init__(self,name='', melody=[], matrix=[], only_names=True, microtonality=False, octave_division=12):
        amplitude_range = 'c b'
        if not only_names:
            microtonality = False
            octave_division = 12
            amplitude_range = 'complete'
        if microtonality:
            only_names = False
        self.amplitude_range = amplitude_range
        self.micro = microtonality
        self.only_names = only_names
        self.octave_division = octave_division
        if melody == [] or type(melody) != list:
            self.matrix = matrix
        else:
            self.serie = melody
            self.matrix = self.compute_matrix()

    def compute_matrix(self):
        if self.micro:
            interv = [self.serie[i]-self.serie[0] for i in range(len(self.serie))]
            iprime = [(self.serie[0]-i)%self.octave_division for i in interv]
            mat = [[(i+j)%self.octave_division for j in interv] for i in iprime]
            return mat
        mel = melody.melody(monody=' '.join([str(i) for i in self.serie]), note_range=self.amplitude_range, only_names=self.only_names)
        prime, iprime = mel.note_to_number(), (~mel).note_to_number()
        thr_up = lambda n: (n-88)//12 + 1
        thr_down = lambda n: n//12 + 1
        interv = [prime[i]-prime[0] for i in range(len(prime))]
        if self.only_names:
            mat = [[(i+j)%12 for j in interv] for i in iprime]
        else:
            mat = [[i+j for j in interv] for i in iprime]
            mat = [[i if 0<=i<=87 else i-(12*thr_up(i)) if i>87 else i+(12*thr_down(i)) for i in j] for j in mat]
        return mat

    def __str__(self):
        """Return a nicer representation of the matrix."""
        message = ''
        if len(self)==1:
            space = '2'
        else:
            space = str(max(*max(*[[len(str(i)) for i in j] for j in self])))
        for m in self.matrix:
            for k in m:
                message += ('{:>'+space+'} ').format(k)
            message += '\n'
        return message

    def __call__(self, i, j):
        """Return the value of the ith row and jth column.""" 
        return self.matrix[i][j]

    def __getitem__(self, i, shift=0):
        """Return a principal matrix minor."""
        l=list(range(len(self)))[i]
        new = shift>>self
        if type(l)==int: matr=[[new(l,l)]]
        else: matr = [[new(j,k) for k in l] for j in l]
        new = matrix(matrix=matr)
        new = shift<<new
        return new

    def __setitem__(self, i, other, shift=0):
        """Redefine a principal matrix minor."""
        l=list(range(len(self)))[i]
        if type(other)==__class__:
            if other.__class__.__name__=='matrix': other=list(other)
        self = shift>>self
        if type(l)==int: self.matrix[l][l]=other
        else:
            for j in l:
                for s in l:
                    self.matrix[j][s] = other[j][s]
        self = shift<<self

    def __delitem__(self, i, shift=0):
        """Delete the ith row and ith column."""
        l=list(range(len(self)))[i]
        m=list(range(len(self)))
        for i in l:
            del m[i]
        self = shift>>self
        matr=[[self(g,h) for h in m] for g in m]
        self.matrix=matr
        self = shift<<self

    def __len__(self):
        """Return the size of the matrix."""
        return len(self.matrix)

    def __add__(self,other):
        """Add each entry of a matrix to the correspondent one of another."""
        assert type(other)==type(self)
        assert len(self)==len(other)
        with hidePrints():
            self.set_matrix_to_numbers()
            other.set_matrix_to_numbers()
        soma = [[(self(i,j)+other(i,j))%12 for j in range(len(self))] for i in range(len(self))]
        new = matrix(matrix=soma,only_names=self.only_names)
        return new

    def __sub__(self,other):
        """Subtract each entry of a matrix to the correspondent one of another."""
        assert type(other)==type(self)
        assert len(self)==len(other)
        with hidePrints():
            self.set_matrix_to_numbers()
            other.set_matrix_to_numbers()
        soma = [[(self(i,j)-other(i,j))%12 for j in range(len(self))] for i in range(len(self))]
        new = matrix(matrix=soma)
        return new

    def __matmul__(self, other, prime=13):
        """Return standard matrix multiplication over a Zp finite field."""
        field = Zp(prime)
        with hidePrints():
            self.set_matrix_to_numbers()
            ide1=[[self(i,j) for j in range(len(self))] for i in range(len(self))]
            if type(other)==melody.melody:
                Other = other.note_to_number()
                ide2 = [[i] for i in Other]
            else:
                other.set_matrix_to_numbers()
                ide2=[[other(i,j) for j in range(len(other))] for i in range(len(other))]
        Inv = field.mul_mtx(ide1,ide2)
        Inv = [[i%12 for i in Inv[j]] for j in range(len(Inv))]
        if type(other) == melody.melody:
            self.dic['monody'] = ' '.join([str(i[0]) for i in Inv])
            new = melody.melody(**self.dic)
        else: new = matrix(matrix=Inv)
        print('Multiplied over Z_%d' % prime)
        return new

    def __imatmul__(self, other, prime=13):
        return self.__matmul__(other, prime)

    def __rmatmul__(self, other, prime=13):
        """Return standard matrix multiplication over a Zp finite field."""
        field = Zp(prime)
        with hidePrints():
            self.set_matrix_to_numbers()
            ide1=[[self(i,j) for j in range(len(self))] for i in range(len(self))]
            if type(other) == melody.melody:
                Other = other.note_to_number()
                ide2 = [Other]
            else:
                ide2 = [other]
        Inv = field.mul_mtx(ide2,ide1)
        Inv = [[i%12 for i in Inv[j]] for j in range(len(Inv))]
        if type(other) == melody.melody:
            self.dic['monody'] = ' '.join([str(i) for i in Inv[0]])
            new = melody.melody(**self.dic)
        else: new = matrix(matrix=Inv)
        print('Multiplied over Z_%d' % prime)
        return new

    def __mul__(self, other, prime=13):
        """Multiply over a Zp finite field each entry of a matrix to the correspondent one of another."""
        field = Zp(prime)
        with hidePrints():
            self.set_matrix_to_numbers()
            other.set_matrix_to_numbers()
        new = matrix(matrix=[[field.mul(self(i,j),other(i,j))%12 for j in range(len(self))] for i in range(len(self))])
        print('Multiplied over Z_%d' % prime)
        return new

    def __rmul__(self, other, prime=13):
        """Multiply each entry by a factor."""
        with hidePrints():
            self.set_matrix_to_numbers()
        new = matrix(matrix=[[(self(i,j)*other)%12 for j in range(len(self))] for i in range(len(self))])
        return new

    def __truediv__(self, other, prime=13):
        """Multiply by the inversion, both over a Zp finite field."""
        try:
            new = self.__matmul__(other.__invert__(prime),prime=prime)
            return new
        except TypeError:
            return

    def __rtruediv__(self, other, prime=13):
        """Multiply the matrix^-1 by a factor, over the Zp finite field."""
        try:
            new = other*self.__invert__(prime)
            return new
        except TypeError:
            return
    
    def __floordiv__(self,other,prime=13):
        return

    def __neg__(self):
        """Return -matrix-"""
        with hidePrints():
            self.set_matrix_to_numbers()
        soma = [[(-self(i,j))%12 for j in range(len(self))] for i in range(len(self))]
        new = matrix(matrix=soma)
        return new

    def __abs__(self,_thresh=1093,prime=13):
        """Return p, where p is the prime on which the matrix could be inverted over the Zp finite field."""
        while prime<=_thresh:
            try:
                if self.__int__(prime)==0:
                    prime+=1
                else: break
            except AssertionError:
                prime+=1
        else:
            return
        return prime

    def __invert__(self, prime=13, _iter=False):
        """Return standard matrix invertion of a matrix, over a Zp finite field."""
        if prime <= 13:
            _iter = True
        if not _iter:
            try:
                assert 1/self.__int__(prime)
            except AssertionError:
                print('Z_%d is not a field.' % prime)
                return
            except ZeroDivisionError:
                print('Matrix not invertible over the Z_%d field.' % prime)
                return
        else:
            if not self:
                print('Matrix not invertible up to Z_1093.')
                return
            prime = abs(self)
        field = Zp(prime)
        with hidePrints():
            self.set_matrix_to_numbers()
            ide=[[self(i,j) for j in range(len(self))] for i in range(len(self))]
        Inv = field.inv_mtx(ide)
        Inv = [[i%12 for i in Inv[j]] for j in range(len(Inv))]
        new = matrix(matrix=Inv)
        print('Inverted over Z_%d' % prime)
        return new

    def __reversed__(self):
        """Return the transpose of a matrix."""
        transp=[[self(i,j) for i in range(len(self))] for j in range(len(self))]
        new = matrix(matrix=transp)
        return new

    def __lshift__(self, v):
        """Shifh columns to the left."""
        with hidePrints():
            self.set_matrix_to_numbers()
            ide = matrix(matrix=[[1 if i==((j+v)%len(self)) else 0 for i in range(len(self))] for j in range(len(self))])
            new = matrix(matrix=list(self@ide))
        return new

    def __rlshift__(self, v):
        """Shifh rows up."""
        with hidePrints():
            self.set_matrix_to_numbers()
            ide = matrix(matrix=[[1 if i==((j+v)%len(self)) else 0 for i in range(len(self))] for j in range(len(self))])
            new = matrix(matrix=list(ide@self))
        return new

    def __rshift__(self, v):
        """Shifh columns to the right."""
        with hidePrints():
            self.set_matrix_to_numbers()
            ide = matrix(matrix=[[1 if i==((j+v)%len(self)) else 0 for j in range(len(self))] for i in range(len(self))])
            new = matrix(matrix=list(self@ide))
        return new

    def __rrshift__(self, v):
        """Shifh rows down."""
        with hidePrints():
            self.set_matrix_to_numbers()
            ide = matrix(matrix=[[1 if i==((j+v)%len(self)) else 0 for j in range(len(self))] for i in range(len(self))])
            new = matrix(matrix=list(ide@self))
        return new

    def __mod__(self, l):
        """Restrain a matrix to the given notes."""
        assert type(l)==list or type(l)==melody.melody
        if type(l)==melody.melody:
            l=l.note_to_number()
        elif type(l[0])==str: l=melody.melody(monody=' '.join(l), only_names=True).note_to_number()
        with hidePrints():
            self.set_matrix_to_numbers()
        matr = [[l[self(i,j)%len(l)] for j in range(len(self))] for i in range(len(self))]
        new = matrix(matrix=matr)
        return new

    def __bool__(self):
        """Check if the matrix is invertible."""
        if abs(self)==None: return False
        else: return True

    def __eq__(self,other):
        """Check if two matrices are equal."""
        if type(other)!=type(self): return False
        return all(self(i,j)==other(i,j) for i in range(len(self)) for j in range(len(self)))

    def __ne__(self,other):
        """Check if two matrices are different."""
        if type(other)!=type(self): return True
        return any(self(i,j)!=other(i,j) for i in range(len(self)) for j in range(len(self)))

    def __iter__(self):
        """Iterate over each row."""
        lines=(self.matrix[i] for i in range(len(self)))
        return lines

    def __repr__(self):
        """Represent the size of the matrix"""
        return '{}x{} note matrix'.format(len(self),len(list(self)[0]))

    def __int__(self,prime=13):
        """Return the determinant of a matrix."""
        field=Zp(prime)
        return field.determinant(self.matrix)

    def __float__(self,prime=13):
        """Return the determinant of a matrix."""
        field=Zp(prime)
        return float(field.determinant(self.matrix))

    def __pow__(self,other,modulo=13):
        """Return a matrix conjugation or raise a matrix to the pth power."""
        if other.__class__.__name__=='matrix':
            return other.__invert__(modulo).__matmul__(self,modulo).__matmul__(other,modulo)
        ide=[[1 if i==j else 0 for i in range(len(self))] for j in range(len(self))]
        with hidePrints():
            self.set_matrix_to_numbers()
        ide=matrix(matrix=ide)
        for i in range(abs(other)):
            if i!=abs(other)-1:
                with hidePrints():
                    ide = ide.__imatmul__(self, modulo)
            else:
                ide = ide.__imatmul__(self, modulo)
        if other<0: ide=~ide
        return ide

    def __rpow__(self,other,modulo=13):
        """Raise a real number to a power of a matrix."""
        assert type(other)==float or type(other)==int
        field=Zp(modulo)
        exp = matrix(matrix=[[0 for i in self.matrix[0]] for j in self])
        for i in range(len(field)):
            if i!=len(field)-1:
                with hidePrints():
                    exp += field.inv(field(math.factorial(i)))*((field(math.ceil(math.log(other)))*self)**i)
            else:
                exp += field.inv(field(math.factorial(i)))*((field(math.ceil(math.log(other)))*self)**i)
        return exp
        
    def abs_list(self,_thresh=1093,prime=3,inverted=False):
        """Return the list of all p values the function abs() can return."""
        l=[]
        p=[k for k in range(_thresh+1) if isOddPrime(k)]
        while True:
            prime = self.__abs__(_thresh,prime)
            if prime==None: break
            l.append(prime)
            prime+=1
        if inverted: l=[k for k in p if k not in l]
        return l

    def Pn(self, t, first_entry=0):
        """Return the nth prime."""
        first = 0
        for d in self.matrix[first_entry:]:
            first = d[0]
            if first == t:
                self.dic['monody']=' '.join([str(i) for i in d])
                new = melody.melody(**self.dic)
                return new
        else:
            print('No primes start with {}.'.format(t))
            return

    def Rn(self, t, first_entry=0):
        """Return the nth retrograde."""
        first = 0
        for e in self.matrix[first_entry:]:
            first = e[0]
            if first == t:
                e.reverse()
                self.dic['monody']=' '.join([str(i) for i in e])
                new = melody.melody(**self.dic)
                return new
        else:
            print('Found no retrogrades that end with {}.'.format(t))
            return

    def In(self, t, first_entry=0):
        """Return the nth inversion."""
        f = 0
        try:
            f = self.matrix[0].index(t,first_entry)
        except ValueError:
            print('No inversion found with {}.'.format(t))
            return
        i = []
        for u in range(len(self)):
            i.append(self(u,f))
        self.dic['monody']=' '.join([str(j) for j in i])
        new = melody.melody(**self.dic)
        return new

    def RIn(self, t, first_entry=0):
        """Return the nth retrograde-inversion."""
        h = 0
        try:
            h = self.matrix[0].index(t,first_entry)
        except ValueError:
            print('No retrograde-inversions end with {}.'.format(t))
            return
        ri = []
        for v in range(len(self)):
            ri.append(self(v,h))
        ri.reverse()
        self.dic['monody']=' '.join([str(i) for i in ri])
        new = melody.melody(**self.dic)
        return new

    def sectbg(self, t, n):
        """Return a section of the matrix, starting on a specific note."""
        row = []
        column = []
        sect = []
        row_index, column_index = 0, 0
        rand = 0
        rand2 = 0
        for k in self.matrix:
            if t in k:
                break
            if t not in k:
                continue
        else:
            print('Note {} not found in matrix.'.format(t))
            return
        if n < 1 or n > len(self):
            raise IndexError(n, 'is too big or below 0.')
        while True:
            rand = random2.randrange(0, len(self))
            rand2 = random2.randrange(0, 40) % 4
            row = self.matrix[rand]
            if t not in row:
                continue
            row_index = row.index(t)
            for j in range(len(self)):
                column.append(self(j,row_index))
            column_index = column.index(t)

            def dire(sect, row_index, column_index, rand2, n):
                step1, step2, step3, step4 = 0, 0, 0, 0
                size = len(self)
                for k in range(n):
                    # if step is a negative number, then it wraps around to raise a IndexError
                    step1 = (row_index+k) % size
                    step2 = (row_index-k) % size
                    step3 = (column_index+k) % size
                    step4 = (column_index-k) % size
                    if rand2 == 0:
                        try:
                            sect.append(row[step1])
                        except IndexError:
                            return
                    if rand2 == 1:
                        try:
                            sect.append(row[step2])
                        except IndexError:
                            return
                    if rand2 == 2:
                        try:
                            sect.append(column[step3])
                        except IndexError:
                            return
                    if rand2 == 3:
                        try:
                            sect.append(column[step4])
                        except IndexError:
                            return
                return sect
            if dire(sect, row_index, column_index, rand2, n) is None:
                sect = []
                continue
            else:
                break
        self.dic['monody']=' '.join(sect)
        new = melody.melody(**self.dic)
        return new

    def sectend(self, t, n):
        """Return a section of the matrix, ending on a specific note."""
        row = []
        column = []
        sect = []
        row_index, column_index = 0, 0
        rand = 0
        rand2 = 0
        for k in self.matrix:
            if t in k:
                break
            if t not in k:
                continue
        else:
            print('Note {} not found in matrix.'.format(t))
            return
        if n < 1 or n > len(self):
            raise IndexError(n, 'is too big or below 0.')
        while True:
            rand = random2.randrange(0, len(self))
            rand2 = random2.randrange(0, 40) % 4
            row = self.matrix[rand]
            if t not in row:
                continue
            row_index = row.index(t)
            for j in range(len(self)):
                column.append(self(j,row_index))
            column_index = column.index(t)

            def dire(sect, row_index, column_index, rand2, n):
                step1, step2, step3, step4 = 0, 0, 0, 0
                size = len(self)
                for k in range(n):
                    # if step is a negative number, then it wraps around to raise a IndexError
                    step1 = (row_index+k) % size
                    step2 = (row_index-k) % size
                    step3 = (column_index+k) % size
                    step4 = (column_index-k) % size
                    if rand2 == 0:
                        try:
                            sect.append(row[step1])
                        except IndexError:
                            return
                    if rand2 == 1:
                        try:
                            sect.append(row[step2])
                        except IndexError:
                            return
                    if rand2 == 2:
                        try:
                            sect.append(column[step3])
                        except IndexError:
                            return
                    if rand2 == 3:
                        try:
                            sect.append(column[step4])
                        except IndexError:
                            return
                sect.reverse()
                return sect
            if dire(sect, row_index, column_index, rand2, n) is None:
                sect = []
                continue
            else:
                break
        self.dic['monody']=' '.join(sect)
        new = melody.melody(**self.dic)
        return new

    def sectspiralout(self, t, n):
        """Return a spiraling section of the matrix, starting on a specific note."""
        sect = [t]
        size=len(self)
        for k in self.matrix:
            if t in k:
                break
            if t not in k:
                continue
        else:
            print('Note {} not found in matrix.'.format(t))
            return
        def seq(n):
            seq1 = []
            seq = []
            index = 0
            rand2 = random2.randrange(0, 4)
            for k in range(1, n):
                seq1.append(k)
                seq1.append(k)
            for l in range(len(seq1)):
                rand2 = (rand2+1) % 4
                index = seq1[l]
                for m in range(index):
                    seq.append(rand2)
            seq = seq[0:n-1]
            return seq
        sequ = []
        r = []
        i, j = 0, 0
        while True:
            sequ = seq(n)
            rand = random2.randrange(0, len(self))
            r = self.matrix[rand]
            if t not in r:
                continue
            i = self.matrix.index(r)
            j = r.index(t)
            break
        def spirout(i, j, n, sequ, sect):
            step = 0
            for l in range(n-1):
                step = sequ[l]
                if step == 0:
                    j = (j+1) % size
                    sect.append(self(i,j))
                if step == 1:
                    i = (i-1) % size
                    sect.append(self(i,j))
                if step == 2:
                    j = (j-1) % size
                    sect.append(self(i,j))
                if step == 3:
                    i = (i+1) % size
                    sect.append(self(i,j))
            else:
                return sect
        sect = spirout(i, j, n, sequ, sect)
        self.dic['monody']=' '.join([str(i) for i in sect])
        new = melody.melody(**self.dic)
        return new

    def sectspiralin(self, t, n):
        """Return a spiraling section of the matrix, ending on a specific note."""
        sect = [t]
        for k in self.matrix:
            if t in k:
                break
            if t not in k:
                continue
        else:
            print('Note {} not found in matrix.'.format(t))
            return
        def seq(n):
            seq1 = []
            seq = []
            index = 0
            rand2 = random2.randrange(0, 4)
            for k in range(1, n):
                seq1.append(k)
                seq1.append(k)
            for l in range(len(seq1)):
                rand2 = (rand2+1) % 4
                index = seq1[l]
                for m in range(index):
                    seq.append(rand2)
            seq = seq[0:n-1]
            return seq
        sequ = []
        r = []
        i, j = 0, 0
        while True:
            sequ = seq(n)
            rand = random2.randrange(0, len(self))
            r = self.matrix[rand]
            if t not in r:
                continue
            i = self.matrix.index(r)
            j = r.index(t)
            break
        def spirin(i, j, n, sequ, sect):
            step = 0
            for l in range(n-1):
                step = sequ[l]
                if step == 0:
                    j = (j+1) % n
                    sect.append(self(i,j))
                if step == 1:
                    i = (i-1) % n
                    sect.append(self(i,j))
                if step == 2:
                    j = (j-1) % n
                    sect.append(self(i,j))
                if step == 3:
                    i = (i+1) % n
                    sect.append(self(i,j))
            else:
                return sect
        sect = spirin(i, j, n, sequ, sect)
        sect.reverse()
        self.dic['monody']=' '.join([str(i) for i in sect])
        new = melody.melody(**self.dic)
        return new
        
    def set_matrix_to_notes(self):
        """Change the matrix to display only note names."""
        def note():
            notes = amplitude(self.amplitude_range)
            for k in self.matrix:
                for i in range(len(k)):
                    try:
                        k[i] = notes[k[i]]
                    except TypeError:
                        print('Matrix already displaying note names.')
                        return
            assert not self.micro
            self.prime = self.matrix[0]
            return self.matrix
        note()

    def set_matrix_to_numbers(self):
        """Change the matrix to display only note values."""
        def number():
            notes = amplitude(self.amplitude_range)
            for k in self.matrix:
                for i in range(len(k)):
                    try:
                        k[i] = notes.index(k[i])
                    except ValueError:
                        print('Matrix already displaying note values.')
                        return
            assert not self.micro
            self.prime = self.matrix[0]
            return self.matrix
        number()
        
