import hw

def none():
    pass

def ldx():
    pc += 1
    regx = mem[pc]

def ldy():
    pc += 1
    regy = mem[pc]

def ldz():
    pc += 1
    regz = mem[pc]

def rtx():
    pc += 1
    mem[mem[pc]] = rtx

def rty():
    pc += 1
    mem[mem[pc]] = rty

def rtz():
    pc += 1
    mem[mem[pc]] = regz

def add():
    regz = regx + regy

def sub():
    regz = regx - regy

def mul():
    regz = regx * regy

def div():
    regz = regx / regy

def mov():
    mem[regy] = regx

def jmp():
    pc = mem[pc + 1]

def die():
    exit(0)

def prt():
    pc += 1
    print(mem[mem[pc]])

