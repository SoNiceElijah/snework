
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
    let jobname = ctx.message.text.split(' ')[1];
    let a = await invokejob(jobname);
    if(!a) return ctx.reply('wrong job name');
    return ctx.reply(`Job done! ${a}`);
})

bot.startPolling(() => { console.log('bot online') });
