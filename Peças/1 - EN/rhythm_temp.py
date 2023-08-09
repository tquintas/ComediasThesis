import math as m

def poly(*num):
    subdiv = m.lcm(*num)
    tupl = [subdiv//i for i in num]
    pos = [1 if any(k % i == 0 for i in tupl) else 0 for k in range(subdiv)]
    mini = min(tupl)
    maxi = int(sum(num)/len(num))
    print(maxi)
    line = [l := [p := pos.index(1, k+1) - k if k % i == 0 and k < subdiv - mini else mini if k == subdiv - mini and i == mini else ' ' for k in range(subdiv)] for i in tupl]
    line2 = [p := pos.index(1, k+1) - k for k in range(subdiv) if any(k % i == 0 for i in tupl) and k < subdiv - mini] + [mini]
    for i in range(subdiv):
        if all(line[k][i:i+maxi] == [' ']*maxi for k in range(len(tupl))):
            for k in range(len(tupl)):
                line[k][i:i+maxi]=['']*maxi
    print(*['\n' + ''.join(str(a) for a in i) for i in line])
    return line2
