
const path = require('path');
const { spawn } = require('child_process');

const ANALYSISPATH = path.resolve(__dirname,'..','analysis');

function analyse(name, metapath,workdir) 
{
    name += '.py';
    const analyser = path.resolve(ANALYSISPATH,name);
    return new Promise((res,rej) => {
        let a = spawn(`python3`,[analyser, metapath, workdir]);
        a.on('close', () => { res(); });
        a.on('error', (err) => { rej(err); });
    });

}

module.exports = { analyse }
