# PROJECT 1 - BOOLEAN LOGIC

Build all fundamental logic gates from NAND up.

---

## NAND Gate (Primitive)

### Truth Table
| a | b | out |
|---|---|-----|
| 0 | 0 | 1   |
| 0 | 1 | 1   |
| 1 | 0 | 1   |
| 1 | 1 | 0   |

### Why
Functionally complete - can build any logic from it.

---

## NOT Gate

### Truth Table
| in | out |
|----|-----|
| 0  | 1   |
| 1  | 0   |

### Circuit
```
in ───┬───┐
      │   │  ┌──────┐
      └───┴──┤ NAND ├─── out
             └──────┘
```

### Why
Invert signals.

### HDL
```hdl
CHIP Not {
    IN in;
    OUT out;
    PARTS:
    Nand(a=in, b=in, out=out);
}
```

---

## AND Gate

### Truth Table
| a | b | out |
|---|---|-----|
| 0 | 0 | 0   |
| 0 | 1 | 0   |
| 1 | 0 | 0   |
| 1 | 1 | 1   |

### Circuit
```
     ┌──────┐    ┌─────┐
a ───┤      ├────┤     ├─── out
b ───┤ NAND │    │ NOT │
     └──────┘    └─────┘
```

### Why
Both conditions must be true.

### HDL
```hdl
CHIP And {
    IN a, b;
    OUT out;
    PARTS:
    Nand(a=a, b=b, out=nandOut);
    Not(in=nandOut, out=out);
}
```

---

## OR Gate

### Truth Table
| a | b | out |
|---|---|-----|
| 0 | 0 | 0   |
| 0 | 1 | 1   |
| 1 | 0 | 1   |
| 1 | 1 | 1   |

### Circuit
```
     ┌─────┐
a ───┤ NOT ├───┐
     └─────┘   │  ┌──────┐
               ├──┤      ├─── out
     ┌─────┐   │  │ NAND │
b ───┤ NOT ├───┘  └──────┘
     └─────┘
```

### Why
At least one condition must be true.

### HDL
```hdl
CHIP Or {
    IN a, b;
    OUT out;
    PARTS:
    Not(in=a, out=notA);
    Not(in=b, out=notB);
    Nand(a=notA, b=notB, out=out);
}
```

---

## XOR Gate

### Truth Table
| a | b | out |
|---|---|-----|
| 0 | 0 | 0   |
| 0 | 1 | 1   |
| 1 | 0 | 1   |
| 1 | 1 | 0   |

### Circuit
```
       ┌──────┐
   ┌───┤ NAND ├────┐
   │   └──────┘    │
a ─┼───────────────┼─┐
   │                │ │  ┌──────┐
   │  ┌──────┐      └─┤  │      │
   └──┤ NAND │        ├──┤ NAND ├─── out
      └──────┘      ┌─┤  │      │
   ┌────────────────┘ │  └──────┘
b ─┼───────────────┼──┘
   │  ┌──────┐     │
   └──┤ NAND │─────┘
      └──────┘
```

### Why
Outputs 1 when inputs differ. Used in addition.

### HDL
```hdl
CHIP Xor {
    IN a, b;
    OUT out;
    PARTS:
    Nand(a=a, b=b, out=nand1);
    Nand(a=a, b=nand1, out=nand2);
    Nand(a=b, b=nand1, out=nand3);
    Nand(a=nand2, b=nand3, out=out);
}
```

---

## NOT16

### What
Inverts all 16 bits.

### Circuit
```
in[0]  ─┤ NOT ├─ out[0]
in[1]  ─┤ NOT ├─ out[1]
  ...      ...      ...
in[15] ─┤ NOT ├─ out[15]
```

### HDL
```hdl
CHIP Not16 {
    IN in[16];
    OUT out[16];
    PARTS:
    Not(in=in[0], out=out[0]);
    Not(in=in[1], out=out[1]);
    Not(in=in[2], out=out[2]);
    Not(in=in[3], out=out[3]);
    Not(in=in[4], out=out[4]);
    Not(in=in[5], out=out[5]);
    Not(in=in[6], out=out[6]);
    Not(in=in[7], out=out[7]);
    Not(in=in[8], out=out[8]);
    Not(in=in[9], out=out[9]);
    Not(in=in[10], out=out[10]);
    Not(in=in[11], out=out[11]);
    Not(in=in[12], out=out[12]);
    Not(in=in[13], out=out[13]);
    Not(in=in[14], out=out[14]);
    Not(in=in[15], out=out[15]);
}
```

---

## AND16

### What
Bitwise AND on 16-bit buses.

### Circuit
```
a[0] ─┐
      ├─┤ AND ├─ out[0]
b[0] ─┘
a[1] ─┐
      ├─┤ AND ├─ out[1]
b[1] ─┘
 ...     ...       ...
a[15]─┐
      ├─┤ AND ├─ out[15]
b[15]─┘
```

### HDL
```hdl
CHIP And16 {
    IN a[16], b[16];
    OUT out[16];
    PARTS:
    And(a=a[0], b=b[0], out=out[0]);
    And(a=a[1], b=b[1], out=out[1]);
    And(a=a[2], b=b[2], out=out[2]);
    And(a=a[3], b=b[3], out=out[3]);
    And(a=a[4], b=b[4], out=out[4]);
    And(a=a[5], b=b[5], out=out[5]);
    And(a=a[6], b=b[6], out=out[6]);
    And(a=a[7], b=b[7], out=out[7]);
    And(a=a[8], b=b[8], out=out[8]);
    And(a=a[9], b=b[9], out=out[9]);
    And(a=a[10], b=b[10], out=out[10]);
    And(a=a[11], b=b[11], out=out[11]);
    And(a=a[12], b=b[12], out=out[12]);
    And(a=a[13], b=b[13], out=out[13]);
    And(a=a[14], b=b[14], out=out[14]);
    And(a=a[15], b=b[15], out=out[15]);
}
```

---

## OR16

### What
Bitwise OR on 16-bit buses.

### Circuit
```
a[0] ─┐
      ├─┤ OR ├─ out[0]
b[0] ─┘
a[1] ─┐
      ├─┤ OR ├─ out[1]
b[1] ─┘
 ...    ...      ...
a[15]─┐
      ├─┤ OR ├─ out[15]
b[15]─┘
```

### HDL
```hdl
CHIP Or16 {
    IN a[16], b[16];
    OUT out[16];
    PARTS:
    Or(a=a[0], b=b[0], out=out[0]);
    Or(a=a[1], b=b[1], out=out[1]);
    Or(a=a[2], b=b[2], out=out[2]);
    Or(a=a[3], b=b[3], out=out[3]);
    Or(a=a[4], b=b[4], out=out[4]);
    Or(a=a[5], b=b[5], out=out[5]);
    Or(a=a[6], b=b[6], out=out[6]);
    Or(a=a[7], b=b[7], out=out[7]);
    Or(a=a[8], b=b[8], out=out[8]);
    Or(a=a[9], b=b[9], out=out[9]);
    Or(a=a[10], b=b[10], out=out[10]);
    Or(a=a[11], b=b[11], out=out[11]);
    Or(a=a[12], b=b[12], out=out[12]);
    Or(a=a[13], b=b[13], out=out[13]);
    Or(a=a[14], b=b[14], out=out[14]);
    Or(a=a[15], b=b[15], out=out[15]);
}
```

---

## OR8WAY

### Truth Table
Outputs 1 if ANY input is 1.

| in[0-7] | out |
|---------|-----|
| 00000000| 0   |
| any 1   | 1   |

### Circuit
```
in[0]─┐
      ├─┤ OR ├─┐
in[1]─┘        │
               ├─┤ OR ├─┐
in[2]─┐        │        │
      ├─┤ OR ├─┘        │
in[3]─┘                 ├─┤ OR ├─── out
                        │
in[4]─┐                 │
      ├─┤ OR ├─┐        │
in[5]─┘        │        │
               ├─┤ OR ├─┘
in[6]─┐        │
      ├─┤ OR ├─┘
in[7]─┘
```

### Why
Check if any bit is set.

### HDL
```hdl
CHIP Or8Way {
    IN in[8];
    OUT out;
    PARTS:
    Or(a=in[0], b=in[1], out=or01);
    Or(a=in[2], b=in[3], out=or23);
    Or(a=in[4], b=in[5], out=or45);
    Or(a=in[6], b=in[7], out=or67);
    Or(a=or01, b=or23, out=or0123);
    Or(a=or45, b=or67, out=or4567);
    Or(a=or0123, b=or4567, out=out);
}
```

---

## MUX (Multiplexor)

### Truth Table
Select which input passes through: if sel=0 then a, else b.

| sel | out |
|-----|-----|
| 0   | a   |
| 1   | b   |

### Circuit
```
       ┌─────┐
sel ───┤ NOT ├───┐
       └─────┘   │
                 │  ┌─────┐
a ───────────────┴──┤     ├───┐
                    │ AND │   │
                    └─────┘   │  ┌────┐
                              ├──┤    ├─── out
                    ┌─────┐   │  │ OR │
b ──────────────┬───┤     ├───┘  └────┘
                │   │ AND │
sel ────────────┘   └─────┘
```

### Why
Choose between two inputs based on selector.

### HDL
```hdl
CHIP Mux {
    IN a, b, sel;
    OUT out;
    PARTS:
    Not(in=sel, out=notSel);
    And(a=a, b=notSel, out=aAndNotSel);
    And(a=b, b=sel, out=bAndSel);
    Or(a=aAndNotSel, b=bAndSel, out=out);
}
```

---

## DMUX (Demultiplexor)

### Truth Table
Route input to one of two outputs based on selector.

| sel | a   | b   |
|-----|-----|-----|
| 0   | in  | 0   |
| 1   | 0   | in  |

### Circuit
```
       ┌─────┐
sel ───┤ NOT ├───┐
       └─────┘   │
                 │  ┌─────┐
in ──────────────┴──┤     ├─── a
                    │ AND │
                    └─────┘

in ──────────────┬──┤     ├─── b
                 │  │ AND │
sel ─────────────┘  └─────┘
```

### Why
Route one input to multiple destinations.

### HDL
```hdl
CHIP DMux {
    IN in, sel;
    OUT a, b;
    PARTS:
    Not(in=sel, out=notSel);
    And(a=in, b=notSel, out=a);
    And(a=in, b=sel, out=b);
}
```

---

## MUX16

### What
16-bit multiplexor - select between two 16-bit buses.

### Circuit
```
a[0-15] ───┐
           ├─┤ MUX ├─ out[0-15]
b[0-15] ───┘
sel ────────┘
```

### HDL
```hdl
CHIP Mux16 {
    IN a[16], b[16], sel;
    OUT out[16];
    PARTS:
    Mux(a=a[0], b=b[0], sel=sel, out=out[0]);
    Mux(a=a[1], b=b[1], sel=sel, out=out[1]);
    Mux(a=a[2], b=b[2], sel=sel, out=out[2]);
    Mux(a=a[3], b=b[3], sel=sel, out=out[3]);
    Mux(a=a[4], b=b[4], sel=sel, out=out[4]);
    Mux(a=a[5], b=b[5], sel=sel, out=out[5]);
    Mux(a=a[6], b=b[6], sel=sel, out=out[6]);
    Mux(a=a[7], b=b[7], sel=sel, out=out[7]);
    Mux(a=a[8], b=b[8], sel=sel, out=out[8]);
    Mux(a=a[9], b=b[9], sel=sel, out=out[9]);
    Mux(a=a[10], b=b[10], sel=sel, out=out[10]);
    Mux(a=a[11], b=b[11], sel=sel, out=out[11]);
    Mux(a=a[12], b=b[12], sel=sel, out=out[12]);
    Mux(a=a[13], b=b[13], sel=sel, out=out[13]);
    Mux(a=a[14], b=b[14], sel=sel, out=out[14]);
    Mux(a=a[15], b=b[15], sel=sel, out=out[15]);
}
```

---

## MUX4WAY16

### What
Select one of four 16-bit inputs using 2-bit selector.

### Truth Table
| sel[1] | sel[0] | out |
|--------|--------|-----|
| 0      | 0      | a   |
| 0      | 1      | b   |
| 1      | 0      | c   |
| 1      | 1      | d   |

### Circuit
```
a ─┐
   ├─┤ MUX ├─┐
b ─┘         │
sel[0] ──────┘  ├─┤ MUX ├─── out
c ─┐            │
   ├─┤ MUX ├───┘
d ─┘         
sel[0] ──────┘
sel[1] ──────────┘
```

### HDL
```hdl
CHIP Mux4Way16 {
    IN a[16], b[16], c[16], d[16], sel[2];
    OUT out[16];
    PARTS:
    Mux16(a=a, b=b, sel=sel[0], out=muxAB);
    Mux16(a=c, b=d, sel=sel[0], out=muxCD);
    Mux16(a=muxAB, b=muxCD, sel=sel[1], out=out);
}
```

---

## MUX8WAY16

### What
Select one of eight 16-bit inputs using 3-bit selector.

### Truth Table
| sel[2:0] | out |
|----------|-----|
| 000      | a   |
| 001      | b   |
| 010      | c   |
| 011      | d   |
| 100      | e   |
| 101      | f   |
| 110      | g   |
| 111      | h   |

### Circuit
```
a,b,c,d ──┤ MUX4WAY16 ├──┐
sel[0:1] ─────────────────┘  ├─┤ MUX16 ├─── out
e,f,g,h ──┤ MUX4WAY16 ├──────┘
sel[0:1] ─────────────────┘
sel[2] ──────────────────────┘
```

### HDL
```hdl
CHIP Mux8Way16 {
    IN a[16], b[16], c[16], d[16], e[16], f[16], g[16], h[16], sel[3];
    OUT out[16];
    PARTS:
    Mux4Way16(a=a, b=b, c=c, d=d, sel=sel[0..1], out=muxABCD);
    Mux4Way16(a=e, b=f, c=g, d=h, sel=sel[0..1], out=muxEFGH);
    Mux16(a=muxABCD, b=muxEFGH, sel=sel[2], out=out);
}
```

---

## DMUX4WAY

### What
Route input to one of four outputs using 2-bit selector.

### Truth Table
| sel[1] | sel[0] | output |
|--------|--------|--------|
| 0      | 0      | a      |
| 0      | 1      | b      |
| 1      | 0      | c      |
| 1      | 1      | d      |

### Circuit
```
in ──┤ DMUX ├──┐
sel[1] ───────┘ │
                ├──┤ DMUX ├─ a
                │  sel[0] ─┘
                │
                └──┤ DMUX ├─ b
                   sel[0] ─┘
```

### HDL
```hdl
CHIP DMux4Way {
    IN in, sel[2];
    OUT a, b, c, d;
    PARTS:
    DMux(in=in, sel=sel[1], a=dmuxAB, b=dmuxCD);
    DMux(in=dmuxAB, sel=sel[0], a=a, b=b);
    DMux(in=dmuxCD, sel=sel[0], a=c, b=d);
}
```

---

## DMUX8WAY

### What
Route input to one of eight outputs using 3-bit selector.

### Truth Table
| sel[2:0] | output |
|----------|--------|
| 000      | a      |
| 001      | b      |
| 010      | c      |
| 011      | d      |
| 100      | e      |
| 101      | f      |
| 110      | g      |
| 111      | h      |

### Circuit
```
in ──┤ DMUX ├──┤ DMUX4WAY ├─ a,b,c,d
sel[2] ───────┘ sel[0:1] ──┘
           └────┤ DMUX4WAY ├─ e,f,g,h
                sel[0:1] ──┘
```

### HDL
```hdl
CHIP DMux8Way {
    IN in, sel[3];
    OUT a, b, c, d, e, f, g, h;
    PARTS:
    DMux(in=in, sel=sel[2], a=dmuxABCD, b=dmuxEFGH);
    DMux4Way(in=dmuxABCD, sel=sel[0..1], a=a, b=b, c=c, d=d);
    DMux4Way(in=dmuxEFGH, sel=sel[0..1], a=e, b=f, c=g, d=h);
}
```

---

## Summary

**Built**: 15 gates from NAND  
**Key Insight**: NAND is functionally complete  
**Next**: Use these to build arithmetic circuits (Project 2)
