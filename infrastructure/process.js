
const { spawn } = require('child_process');
const crypto = require('crypto');
const path = require('path');
const fs = require('fs');
const APPNAME = 'sneapp';
const APPPATH = path.resolve(__dirname,'..','build','bin', APPNAME);
const DBPATH = path.resolve(__dirname,'..','snedata');

const params = require('./params');

const DEFOPTIONS = {
    
    logpath : path.resolve(DBPATH,'logs','app.log'),

    mask : 0x0FFF,
    step : 0.01,
    offset : 0,
    line : 25,
    length : 40000

};

class MProcess {

    constructor(output,input,ctx,consts) 
    {
        this.input = input;
        this.output = output;
        this.ctx = ctx;
        this.consts = consts;
    }

    start()
    {
        params.writeconsts(this.input,this.consts);
        return new Promise((res,rej) => {
            
            this.proc = spawn(APPPATH, [ this.output, this.input, this.ctx.mask, this.ctx.step, 
                                            this.ctx.offset, this.ctx.line, this.ctx.length ]);

            
            this.proc.stdout.on('data', (data) => { fs.appendFileSync(this.ctx.logpath,data); });
            this.proc.on('close', (code) => { res(code); });
            this.proc.on('error', (err) => { rej(err); });
        
        });
    }

    getoutput() { return { file : this.output, options : this.ctx, params : this.consts }; }

}

class MSession {

    constructor(id,options) 
    {
        this.id = id;
        this.processes = [];
        if(!options) options = {};
        this.options = Object.assign({},DEFOPTIONS,options);

        this.datapath = path.resolve(DBPATH,id);    
        this.logpath = path.resolve(this.datapath,'logs');
        this.constspath = path.resolve(this.datapath,'consts');
        this.resultpath = path.resolve(this.datapath,'results');
        this.analysispath = path.resolve(this.datapath,'analysis');

        if(!fs.existsSync(this.datapath)) fs.mkdirSync(this.datapath);
        if(!fs.existsSync(this.logpath)) fs.mkdirSync(this.logpath);
        if(!fs.existsSync(this.constspath)) fs.mkdirSync(this.constspath);
        if(!fs.existsSync(this.resultpath)) fs.mkdirSync(this.resultpath);
        if(!fs.existsSync(this.analysispath)) fs.mkdirSync(this.analysispath);

        this.finished = 0;
    }

    add(consts,options)
    {

        if(!consts) consts = {};
        let c = Object.assign({},params.getconstsdef(),consts);
        if(!options) options = {};
        let o = Object.assign({},this.options,options);

        let pid = crypto.randomBytes(16).toString('hex');
        
        const constsname = `consts_${this.id}_${pid}.bin`;
        const outputname = `res_${this.id}_${pid}.csv`;
        const logname = `log_${this.id}_${pid}.log`;

        const constspath = path.resolve(this.constspath,constsname);
        const outputpath = path.resolve(this.resultpath,outputname);
        o.logpath = path.resolve(this.logpath,logname);

        o.id = this.id;
        o.pid = pid;

        let proc = new MProcess(
            outputpath,
            constspath,
            o,
            c
        );

        this.processes.push(proc);

    }

    run(progress)
    {
        let processes = this.processes;
        let working = this.processes.length;
        return new Promise((res,rej) => {
            for(let p of processes)
            {
                p.start()
                    .then(() => 
                    { 
                        --working;
                        if(progress && typeof progress === 'function') progress(working);
                        if(!working) res(processes.map(x => x.getoutput()));
                    })
                    .catch(() => { console.log('WOW! Error!'); })
            }
        });
    }

    makemeta()
    {
        const metaname = `meta.json`;
        const metapath = path.resolve(this.analysispath,metaname);
        fs.writeFileSync(metapath, JSON.stringify(this.processes.map(x => x.getoutput())));
        return { metapath, workdir : this.analysispath };
    }

}

module.exports = MSession;
