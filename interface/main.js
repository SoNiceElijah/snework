
const vkBot = require('node-vk-bot-api')
const express = require('express');
const settings = require('./config.json');


const invokejob = require('../infrastructure/jobs');

const path = require('path');
const DBPATH = path.resolve(__dirname,'..','snedata');

const app = express();
app.use(express.static(DBPATH));
app.get('/', (req,res) => { res.send('online'); })
app.listen(settings.port, () => { console.log('static online') });

let bot = new vkBot({ token : settings.vktoken });
bot.command("make", async (ctx) => {
    let tokens = ctx.message.text.split(' ');
    let jobname = tokens[1];
    args = [];
    if(tokens.length > 2) args = tokens.slice(2); 
    let a = await invokejob(jobname,args);
    if(!a) return ctx.reply('wrong job name');
    let url = `http://138.68.107.42:${settings.port}/${a}/analysis/${a}.html`;
    return ctx.reply(`Job done!\n ${url}`);
})

bot.startPolling(() => { console.log('bot online') });
