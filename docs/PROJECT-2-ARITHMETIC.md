# PROJECT 2: ARITHMETIC

## Overview
Project 2 builds arithmetic circuits that perform addition and logical operations. Starting with basic adders, we construct the complete Arithmetic Logic Unit (ALU) that forms the computational core of the CPU.

---

## HalfAdder

### Truth Table
| a | b | sum | carry |
|---|---|-----|-------|
| 0 | 0 | 0   | 0     |
| 0 | 1 | 1   | 0     |
| 1 | 0 | 1   | 0     |
| 1 | 1 | 0   | 1     |

### Circuit
```
a ──┬─── XOR ──── sum
    │
b ──┼─── AND ──── carry
    └──────┘
```

**Why**: Sum is XOR (exclusive or), carry is AND of inputs.

### HDL Implementation
```hdl
CHIP HalfAdder {
    IN a, b;    // 1-bit inputs
    OUT sum,    // Right bit of a + b 
        carry;  // Left bit of a + b

    PARTS:
    Xor(a=a, b=b, out=sum);
    And(a=a, b=b, out=carry);
}
```

---

## FullAdder

### Truth Table
| a | b | c | sum | carry |
|---|---|---|-----|-------|
| 0 | 0 | 0 | 0   | 0     |
| 0 | 0 | 1 | 1   | 0     |
| 0 | 1 | 0 | 1   | 0     |
| 0 | 1 | 1 | 0   | 1     |
| 1 | 0 | 0 | 1   | 0     |
| 1 | 0 | 1 | 0   | 1     |
| 1 | 1 | 0 | 0   | 1     |
| 1 | 1 | 1 | 1   | 1     |

### Circuit
```
a ──┬─── HALFADDER ──┬── sum ──┬─── HALFADDER ──── sum
b ──┘        │       │        │        │
             └─ carry │        │        └─ carry2
c ───────────────────┘        │
                              │
carry ──┬─── OR ──────────────┴──────────────── carry
carry2 ─┘
```

**Why**: Two half-adders in series handle three inputs, OR combines carry outputs.

### HDL Implementation
```hdl
CHIP FullAdder {
    IN a, b, c;  // 1-bit inputs
    OUT sum,     // Right bit of a + b + c
        carry;   // Left bit of a + b + c

    PARTS:
    HalfAdder(a=a, b=b, sum=Sab, carry=Cab);
    HalfAdder(a=Sab, b=c, sum=sum, carry=ca);
    Or(a=Cab, b=ca, out=carry);
}
```

---

## Add16

### Truth Table
For each bit i: sum[i] = a[i] + b[i] + carry[i-1]

### Circuit
```
a[0] ──┬─── HALFADDER ──┬── sum[0]
b[0] ──┘        │       │
                └─ c0 ──┤
                        │
a[1] ──┬─── FULLADDER ──┼── sum[1]
b[1] ──┤        │       │
c0 ────┘        └─ c1 ──┤
                        │
...                     │
                        │
a[15] ─┬─── FULLADDER ──┴── sum[15]
b[15] ─┤        │
c14 ───┘        └─ carry (ignored)
```

**Why**: Cascaded adders propagate carry from LSB to MSB for 16-bit addition.

### HDL Implementation
```hdl
CHIP Add16 {
    IN a[16], b[16];
    OUT out[16];

    PARTS:
    HalfAdder(a=a[0], b=b[0], sum=out[0], carry=c1);
    FullAdder(a=a[1], b=b[1], c=c1, sum=out[1], carry=c2);
    FullAdder(a=a[2], b=b[2], c=c2, sum=out[2], carry=c3);
    FullAdder(a=a[3], b=b[3], c=c3, sum=out[3], carry=c4);
    FullAdder(a=a[4], b=b[4], c=c4, sum=out[4], carry=c5);
    FullAdder(a=a[5], b=b[5], c=c5, sum=out[5], carry=c6);
    FullAdder(a=a[6], b=b[6], c=c6, sum=out[6], carry=c7);
    FullAdder(a=a[7], b=b[7], c=c7, sum=out[7], carry=c8);
    FullAdder(a=a[8], b=b[8], c=c8, sum=out[8], carry=c9);
    FullAdder(a=a[9], b=b[9], c=c9, sum=out[9], carry=c10);
    FullAdder(a=a[10], b=b[10], c=c10, sum=out[10], carry=c11);
    FullAdder(a=a[11], b=b[11], c=c11, sum=out[11], carry=c12);
    FullAdder(a=a[12], b=b[12], c=c12, sum=out[12], carry=c13);
    FullAdder(a=a[13], b=b[13], c=c13, sum=out[13], carry=c14);
    FullAdder(a=a[14], b=b[14], c=c14, sum=out[14], carry=c15);
    FullAdder(a=a[15], b=b[15], c=c15, sum=out[15], carry=ignore);
}
```

---

## Inc16

### Truth Table
out = in + 1

### Circuit
```
in[0..15] ──┬─── ADD16 ──── out[0..15]
            │     │
            └─ 0000000000000001
```

**Why**: Adding constant 1 to 16-bit number using Add16 with hardwired 1.

### HDL Implementation
```hdl
CHIP Inc16 {
    IN in[16];
    OUT out[16];

    PARTS:
    Add16(a=in, b[0]=true, out=out);
}
```

---

## ALU

### Truth Table
| zx | nx | zy | ny | f | no | Function      |
|----|----|----|----|----|----| ------------- |
| 1  | 0  | 1  | 0  | 1  | 0  | 0             |
| 1  | 1  | 1  | 1  | 1  | 1  | 1             |
| 1  | 1  | 1  | 0  | 1  | 0  | -1            |
| 0  | 0  | 1  | 1  | 0  | 0  | x             |
| 1  | 1  | 0  | 0  | 0  | 0  | y             |
| 0  | 0  | 1  | 1  | 0  | 1  | !x            |
| 1  | 1  | 0  | 0  | 0  | 1  | !y            |
| 0  | 0  | 1  | 1  | 1  | 1  | -x            |
| 1  | 1  | 0  | 0  | 1  | 1  | -y            |
| 0  | 1  | 1  | 1  | 1  | 1  | x+1           |
| 1  | 1  | 0  | 1  | 1  | 1  | y+1           |
| 0  | 0  | 1  | 1  | 1  | 0  | x-1           |
| 1  | 1  | 0  | 0  | 1  | 0  | y-1           |
| 0  | 0  | 0  | 0  | 1  | 0  | x+y           |
| 0  | 1  | 0  | 0  | 1  | 1  | x-y           |
| 0  | 0  | 0  | 1  | 1  | 1  | y-x           |
| 0  | 0  | 0  | 0  | 0  | 0  | x&y           |
| 0  | 1  | 0  | 1  | 0  | 1  | x\|y          |

### Circuit
```
x ──┬─── MUX16 ──┬─── NOT16 ──┬─── MUX16 ──┬──────────┐
    │    │       │           │           │          │
    │    └─ zx   │           │           │          │
    │            │           └─── nx ────┘          │
    └─── 0       │                                  │
                 │                                  │
y ──┬─── MUX16 ──┴─── NOT16 ──┬─── MUX16 ──┬────────┼───┐
    │    │                    │           │        │   │
    │    └─ zy                │           │        │   │
    │                         └─── ny ────┘        │   │
    └─── 0                                         │   │
                                                   │   │
                              ┌─── ADD16 ──┬───────┤   │
                              │            │       │   │
                              └─── AND16 ──┴─ MUX16┴─ NOT16 ── out
                                             │    │      │
                                             └─ f │      └─ no
                                                  │
                                              OR16WAY ── zr
                                                  │
                                             out[15] ── ng
```

**Why**: Configurable arithmetic and logic unit implementing 18 different functions based on control bits.

### HDL Implementation
```hdl
CHIP ALU {
    IN  
        x[16], y[16],  // 16-bit inputs        
        zx, // zero the x input?
        nx, // negate the x input?
        zy, // zero the y input?
        ny, // negate the y input?
        f,  // compute (out = x + y) or (out = x & y)?
        no; // negate the out output?
    OUT 
        out[16], // 16-bit output
        zr,      // if (out == 0) equals 1, else 0
        ng;      // if (out < 0)  equals 1, else 0

    PARTS:
    // 1 - zx
    Mux16(a=x, b=false, sel=zx, out=newX);
    
    // 2 - nx
    Not16(in=newX, out=NotX);
    Mux16(a=newX, b=NotX, sel=nx, out=newX1);

    // 3 - zy
    Mux16(a=y, b=false, sel=zy, out=newY);
    
    // 4 - ny
    Not16(in=newY, out=NotY);
    Mux16(a=newY, b=NotY, sel=ny, out=newY1);
    
    // 5 - f
    Add16(a=newX1, b=newY1, out=xPluSy);
    And16(a=newX1, b=newY1, out=xAnDy);
    Mux16(a=xAnDy, b=xPluSy, sel=f, out=fResult);
    
    // 6 - no
    Not16(in=fResult, out=NotOut);
    Mux16(a=fResult, b=NotOut, sel=no, out=oo);

    // 7 - zr & ng
    Or16Way(in=oo, out=ooOr);
    Not(in=ooOr, out=zr);
    
    And16(a=true, b=oo, out[15]=ng, out[0..14]=drop);
    Or16(a=oo, b=false, out=out);
}
```

---

## Or16Way

### Truth Table
| in[15..0] | out |
|-----------|-----|
| 0000...0  | 0   |
| xxxx...1  | 1   |
| Any 1 bit | 1   |

### Circuit
```
in[0] ──┬─── OR ──┬─── OR ──┬─── OR ──...──┬─── OR ──── out
in[1] ──┘        │        │              │        │
in[2] ───────────┘        │              │        │
in[3] ────────────────────┘              │        │
...                                      │        │
in[15] ──────────────────────────────────┘        │
```

**Why**: Cascaded OR gates detect if any bit in 16-bit word is 1.

### HDL Implementation
```hdl
CHIP Or16Way {
    IN in[16];
    OUT out;

    PARTS:
    Or(a=in[0], b=in[1], out=a);
    Or(a=a, b=in[2], out=b);
    Or(a=b, b=in[3], out=c);
    Or(a=c, b=in[4], out=d);
    Or(a=d, b=in[5], out=e);
    Or(a=e, b=in[6], out=f);
    Or(a=f, b=in[7], out=g);
    Or(a=g, b=in[8], out=h);
    Or(a=h, b=in[9], out=i);
    Or(a=i, b=in[10], out=j);
    Or(a=j, b=in[11], out=k);
    Or(a=k, b=in[12], out=l);
    Or(a=l, b=in[13], out=m);
    Or(a=m, b=in[14], out=n);
    Or(a=n, b=in[15], out=out);
}
```

---

## ALU Functions Summary

The ALU can compute 18 different functions based on control bit combinations:

### Constant Functions
- **0**: Always outputs zero
- **1**: Always outputs one  
- **-1**: Always outputs negative one (all 1s in two's complement)

### Input Functions
- **x**: Outputs x unchanged
- **y**: Outputs y unchanged
- **!x**: Bitwise NOT of x
- **!y**: Bitwise NOT of y

### Arithmetic Functions
- **-x**: Two's complement negation of x
- **-y**: Two's complement negation of y
- **x+1**: Increment x
- **y+1**: Increment y
- **x-1**: Decrement x
- **y-1**: Decrement y
- **x+y**: Addition
- **x-y**: Subtraction
- **y-x**: Reverse subtraction

### Logic Functions
- **x&y**: Bitwise AND
- **x|y**: Bitwise OR

### Status Flags
- **zr**: Zero flag (1 if output is zero)
- **ng**: Negative flag (1 if output is negative)

---

## Summary

Project 2 creates the arithmetic foundation for computation:

1. **Building Up**: Half-adder → Full-adder → 16-bit adder
2. **Flexibility**: ALU handles both arithmetic and logical operations
3. **Efficiency**: Single unit performs 18 different functions
4. **Integration**: Status flags support conditional operations

The ALU becomes the computational heart of the CPU, enabling all mathematical and logical operations needed for program execution.
