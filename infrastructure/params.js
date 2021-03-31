
const fs = require('fs');

const CONSTANTS = {

    ax : 0.1,
    ag : 0.01,
    ai : 0.1,
    ad : 0.01,

    k0 : 2.0,
    kg : 0.1,
    kx : 0.01,
    kd : 0.1,

    thg : 0.7,
    thx : 0.7,
    thd : 0.7,

    gammag : 0.0,
    gammad : 1.0,

    gna : 120,
    gk : 36,
    gl : 0.3,

    ENa : 50,
    Ek : -77,
    El : -54.4,

    Ith : 5.7,

    fin : 3,
    b0 : 5.7,
    C : 1

}

function writeconsts(path, obj)
{
    let buff = Buffer.alloc(23 * 8);

    buff.writeDoubleLE(obj.ax,      0x0);
    buff.writeDoubleLE(obj.ag,      0x8);    
    buff.writeDoubleLE(obj.ai,      0x10);    
    buff.writeDoubleLE(obj.ad,      0x18);    
    buff.writeDoubleLE(obj.k0,      0x20);    
    buff.writeDoubleLE(obj.kg,      0x28);    
    buff.writeDoubleLE(obj.kx,      0x30);    
    buff.writeDoubleLE(obj.kd,      0x38);    
    buff.writeDoubleLE(obj.thg,     0x40);   
    buff.writeDoubleLE(obj.thx,     0x48);  
    buff.writeDoubleLE(obj.thd,     0x50);   
    buff.writeDoubleLE(obj.gammag,  0x58);
    buff.writeDoubleLE(obj.gammad,  0x60);
    buff.writeDoubleLE(obj.gna,     0x68);   
    buff.writeDoubleLE(obj.gk,      0x70);    
    buff.writeDoubleLE(obj.gl,      0x78);    
    buff.writeDoubleLE(obj.ENa,     0x80);   
    buff.writeDoubleLE(obj.Ek,      0x88);    
    buff.writeDoubleLE(obj.El,      0x90);    
    buff.writeDoubleLE(obj.Ith,     0x98);   
    buff.writeDoubleLE(obj.fin,     0xA0);   
    buff.writeDoubleLE(obj.b0,      0xA8);    
    buff.writeDoubleLE(obj.C,       0xB0);

    fs.writeFileSync(path, buff, { encoding : 'binary' });
}

function getconstsdef()
{
    return { ...CONSTANTS };
}

function buildmask(mask)
{
    let res = 0;
    for(let s of mask) 
    { 
        res = res << 1
        if(s === '+') res = res | 1;
    }
    return res;
}

module.exports = { getconstsdef, writeconsts, buildmask };
