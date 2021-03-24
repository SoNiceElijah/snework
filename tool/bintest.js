
const fs = require('fs');

let ax = 0.1;
let ag = 0.01;
let ai = 0.1;
let ad = 0.01;

let k0 = 2.0;
let kg = 0.1;
let kx = 0.01;
let kd = 0.1;

let thg = 0.7;
let thx = 0.7;
let thd = 0.7;

let gammag = 0.0;
let gammad = 1.0;

let gna = 120;
let gk = 36;
let gl = 0.3;

let ENa = 50;
let Ek = -77;
let El = -54.4;

let Ith = 5.7;

let fin = 3;
let b0 = 5.7;
let C = 1;

let buff = Buffer.alloc(23 * 8);
buff.writeDoubleLE(ax,      0x0);
buff.writeDoubleLE(ag,      0x8);    
buff.writeDoubleLE(ai,      0x10);    
buff.writeDoubleLE(ad,      0x18);    
buff.writeDoubleLE(k0,      0x20);    
buff.writeDoubleLE(kg,      0x28);    
buff.writeDoubleLE(kx,      0x30);    
buff.writeDoubleLE(kd,      0x38);    
buff.writeDoubleLE(thg,     0x40);   
buff.writeDoubleLE(thx,     0x48);  
buff.writeDoubleLE(thd,     0x50);   
buff.writeDoubleLE(gammag,  0x58);
buff.writeDoubleLE(gammad,  0x60);
buff.writeDoubleLE(gna,     0x68);   
buff.writeDoubleLE(gk,      0x70);    
buff.writeDoubleLE(gl,      0x78);    
buff.writeDoubleLE(ENa,     0x80);   
buff.writeDoubleLE(Ek,      0x88);    
buff.writeDoubleLE(El,      0x90);    
buff.writeDoubleLE(Ith,     0x98);   
buff.writeDoubleLE(fin,     0xA0);   
buff.writeDoubleLE(b0,      0xA8);    
buff.writeDoubleLE(C,       0xB0);

fs.writeFileSync('consts.bin',buff, { encoding : 'binary' });