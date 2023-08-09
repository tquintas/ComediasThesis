def isOddPrime(n):
    if n<=2: return False
    for k in range(2,int(n**(1/2)+1)):
        if n%k==0:
            return False
    return True

class Zp:
        def __init__(self,p):
                assert isOddPrime(p)
                self.Prime=p
                self.range=list(range(p))
                self.mtx=[[(i*j)%p for i in self.range] for j in self.range]
        def __call__(self,n):
                return self.range[n%self.Prime]
        def __len__(self):
            return len(self.range)
        def plus(self,n,m):
                return (n+m)%self.Prime
        def mul(self,n,m):
                return self.mtx[n%self.Prime][m%self.Prime]
        def div(self,n,m):
                try:
                        result=self.mtx[m%self.Prime].index(n%self.Prime)
                        return result
                except ValueError:
                        raise ZeroDivisionError('Division by 0')
        def inv(self,n):
                if n%self.Prime==0: raise ZeroDivisionError('Not invertible!')
                for j,i in enumerate(self.mtx[n%self.Prime]):
                        if i==1:
                                return j
        def laplace(self,mtx):
                assert len(mtx)==len(mtx[0])
                if len(mtx)==2:
                    return self.plus(self.mul(mtx[0][0],mtx[1][1]),-self.mul(mtx[1][0],mtx[0][1]))
                elif len(mtx)==1:
                    return self(mtx[0][0])
                def mtx_minor(mtx,i,j):
                    return [row[:j]+row[j+1:] for row in (mtx[:i]+mtx[i+1:])]
                det=0
                for k in range(len(mtx)):
                    if mtx[0][k]==0: continue
                    det+=((-1)**k)*self.mul(mtx[0][k],self.laplace(mtx_minor(mtx,0,k)))
                return det%self.Prime
        def determinant(self,mtx):
                if len(mtx)<=6:
                    return self.laplace(mtx)
                cut=len(mtx)//2
                tries=0
                while tries<=len(mtx)+1:
                    A=[mtx[j][:cut] for j in range(cut)]
                    if cut==0:
                        cut=(cut-1)%len(mtx)
                        continue
                    if self.determinant(A)==0:
                        cut=(cut-1)%len(mtx)
                    else: break
                    tries+=1
                else:
                    return self.laplace(mtx)
                B=[mtx[j][cut:] for j in range(cut)]
                C=[mtx[j][:cut] for j in range(cut,len(mtx))]
                D=[mtx[j][cut:] for j in range(cut,len(mtx))]
                det=self.mul(self.determinant(A),self.determinant(self.sub_mtx(D,self.mul_mtx(C,self.mul_mtx(self.inv_mtx(A),B)))))
                return det
        def mul_mtx(self,mtx1,mtx2):
                if len(mtx1[0])!=len(mtx2): raise IndexError('Size error!')
                mtx3=[[sum(self.mul(mtx1[i][k],mtx2[k][j]) for k in range(len(mtx1[0])))%self.Prime for j in range(len(mtx2[0]))] for i in range(len(mtx1))]
                return mtx3
        def add_mtx(self,mtx1,mtx2):
            return [[self.plus(mtx1[i][j],mtx2[i][j]) for j in range(len(mtx1))] for i in range(len(mtx1))]
        def sub_mtx(self,mtx1,mtx2):
            return [[self.plus(mtx1[i][j],-mtx2[i][j]) for j in range(len(mtx1))] for i in range(len(mtx1))]
        def inv_mtx(self,mtx):
                assert self.determinant(mtx)!=0
                def print_aug_mtx(mtx1,mtx2):
                        for j in range(len(mtx1)):
                                print(*['{:2d}'.format(mtx1[j][i]) for i in range(len(mtx1))],'|',*['{:2d}'.format(mtx2[j][i]) for i in range(len(mtx2))])
                ide=[[1 if i==j else 0 for i in range(len(mtx))] for j in range(len(mtx))]
                pivot=0
                counter=0
                for i in range(len(mtx)):
                        pivot=mtx[i][i]
                        counter=0
                        while pivot%self.Prime==0:
                                counter+=1
                                mtx[i],mtx[i+counter]=mtx[i+counter],mtx[i]
                                ide[i],ide[i+counter]=ide[i+counter],ide[i]
                                pivot=mtx[i][i]
                        mtx[i]=[self.div(k,pivot) for k in mtx[i]]
                        ide[i]=[self.div(k,pivot) for k in ide[i]]
                        for l in range(len(mtx))[i+1:]:
                                while True:
                                        for k in range(len(mtx)):
                                                mtx[l][k]=self.plus(mtx[l][k],mtx[i][k])
                                                ide[l][k]=self.plus(ide[l][k],ide[i][k])
                                        if mtx[l][i]==0: break
                for i in range(len(mtx)-1,0,-1):
                        for l in range(len(mtx))[:i]:
                                while True:
                                        for k in range(len(mtx)):
                                                mtx[l][k]=self.plus(mtx[l][k],mtx[i][k])
                                                ide[l][k]=self.plus(ide[l][k],ide[i][k])
                                        if mtx[l][i]==0: break
                return ide
