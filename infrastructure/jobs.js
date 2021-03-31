
const MSession = require('./process');
const crypto = require('crypto');
const analysis = require('./analysis');
const { buildmask } = require('./params');

async function testjob()
{
    let rand = crypto.randomBytes(16).toString('hex');
    let id = `snejobs_testjob_${rand}`;
    let session = new MSession(id, { mask :  buildmask('+----+------')});

    for(let i = -2.0; i < 0.0; i += 0.5) session.add({ gammag : i, gammad : 0 });
    for(let i = 0.0; i < 5.0; i += 0.5) session.add({ gammag : 0, gammad : i });

    let res = await session.run((j) => { console.log(j + '\n'); });
    let { metapath, workdir } = session.makemeta();

    await analysis.analyse('testanalysis',metapath,workdir);

    console.log('done\n');
    //console.log(res);
}

testjob();
