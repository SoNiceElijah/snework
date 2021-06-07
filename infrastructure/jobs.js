
const path = require('path');
const MSession = require('./process');
const crypto = require('crypto');
const analysis = require('./analysis');
const { buildmask } = require('./params');

//////////////////////////////////////////////
///              JOBS SCRIPTS              ///
//////////////////////////////////////////////

async function gammadgdata()
{
    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    
    // offset 1 second, length 500 sec
    let session = new MSession(id, { offset : 4000, length : 4 * 1000 * 500 ,mask :  buildmask('+----+------')});

    for(let i = -2.0; i < 0.0; i += 0.2) session.add({ gammag : i, gammad : 0 });
    for(let i = 0.0; i < 5.0; i += 0.2) session.add({ gammag : 0, gammad : i });

    await session.run();
    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('spikeanalyser',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return id;
}

async function spikedatagamma(args)
{
    if(!args) return null;
    if(!args.length) return null;

    args[0] = parseFloat(args[0]);

    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    
    // offset 60 sec, length 20 sec
    let session = new MSession(id, { offset : 100 * 1000 * 60 , length : 4 * 1000 * 20 ,mask :  buildmask('+----+------')});
    session.add({ gammad : args[0] });
    await session.run();

    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('spikechart',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return id;
}

async function spikedatacmp()
{
    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    
    // offset 60 sec, length 20 sec
    let session = new MSession(id, { offset : 100 * 1000 * 60 , length : 4 * 1000 * 20 ,mask :  buildmask('+----+------')});
    session.add({ gammad : 0.0 });
    session.add({ gammad : 5.0 });
    await session.run();

    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('spikechart',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return id;
}

async function gammadgfreq(args)
{

    if(!args) return null;
    if(!args.length) return null;

    let fin = parseInt(args[0]);
    if(!fin) return null;

    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    
    // offset 1 second, length 200 sec
    let session = new MSession(id, { offset : 4000, length : 4 * 1000 * 200 ,mask :  buildmask('+----+------')});

    for(let i = -5.0; i < 0.0; i += 0.2) session.add({ fin : fin, gammag : i, gammad : 0 });
    for(let i = 0.0; i <= 5.0; i += 0.2) session.add({ fin : fin, gammag : 0, gammad : i });

    await session.run();
    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('freqanalysis',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return id;
}

async function fingtest()
{

    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    
    // offset 1 second, length 100 sec
    let session = new MSession(id, { offset : 4000, length : 4 * 1000 * 100 ,mask :  buildmask('+----+------')});

    for(let i = 180; i <= 220; i += 4) session.add({ fin : ((1 / i) * 1000), gammag : 0, gammad : 0 });
    for(let i = 180; i <= 220; i += 4) session.add({ fin : ((1 / i) * 1000), gammag : -2, gammad : 0 });
    for(let i = 180; i <= 220; i += 4) session.add({ fin : ((1 / i) * 1000), gammag : -5, gammad : 0 });

    await session.run();
    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('freqout',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return id;
}


async function findtest()
{

    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    
    // offset 1 second, length 300 sec
    let session = new MSession(id, { offset : 4000, length : 4 * 1000 * 300 ,mask :  buildmask('+----+------')});

    for(let i = 230; i <= 270; i += 1) session.add({ fin : ((1 / i) * 1000), gammag : 0, gammad : 0 });
    for(let i = 230; i <= 270; i += 1) session.add({ fin : ((1 / i) * 1000), gammag : 0, gammad : 2 });
    for(let i = 230; i <= 270; i += 1) session.add({ fin : ((1 / i) * 1000), gammag : 0, gammad : 5 });

    await session.run();
    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('freqout',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return id;
}


//////////////////////////////////////////////
///                HANDLER                 ///
//////////////////////////////////////////////

const storage = [];
storage.push(
    { name : 'gnd', handler : gammadgdata },
    { name : 'spikesgamma', handler : spikedatagamma },
    { name : 'spikecmp', handler : spikedatacmp },
    { name : 'gndf', handler : gammadgfreq },
    { name : 'gftest', handler : fingtest },
    { name : 'dftest', handler : findtest }
);

async function invoke(name, args)
{
    let h = storage.find(e => e.name === name);
    if(!h) return null;
    return await h.handler(args)
}

module.exports = invoke;
