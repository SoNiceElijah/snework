
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
    let session = new MSession(id, { offset : 4000, length : 4 * 500 * 1000 ,mask :  buildmask('+----+------')});

    for(let i = -2.0; i < 0.0; i += 0.2) session.add({ gammag : i, gammad : 0 });
    for(let i = 0.0; i < 5.0; i += 0.2) session.add({ gammag : 0, gammad : i });

    await session.run();
    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('spikeanalyser',metapath,workdir);

    console.log(`JOB ${rand} is done\n`);
    //console.log(res);

    return path.resolve(workdir,id + '.html');
}


//////////////////////////////////////////////
///                HANDLER                 ///
//////////////////////////////////////////////

const storage = [];
storage.push({ name : 'gnd', handler : gammadgdata });

async function invoke(name, args)
{
    let h = storage.find(e => e.name === name);
    if(!h) return null;
    return await h.handler(args)
}

module.exports = invoke;
