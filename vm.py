#!/usr/bin/env python

mem = []

pc = 0
regx = 0
regy = 0
regz = 0

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

def eq():
    pass
def lt():
    pass
def gt():
    pass
def jle():
    pass
def jge():
    pass

opcodes = [none, ldx, ldy, ldz, rtx, rty, rtz, add, sub, mul, div, mov, jmp, \
               eq, lt, gt, jle, jge, die, prt]

mem = [0, 0, 1, 2, 2, 4, 19, 18]

def execute():
    pc = 0
    print(pc)
    opcodes[mem[pc]]()

    if pc < len(mem):
        pc += 1
        execute()
    else:
        exit(0)

execute()
