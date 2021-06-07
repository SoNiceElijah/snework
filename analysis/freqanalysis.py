
import csv
import sys
import json

import plotly.graph_objects as go
from plotly.subplots import make_subplots

metafile = sys.argv[1]
outputdir = sys.argv[2]

f = open(metafile,)
meta = json.load(f)
f.close()

result = open(f"{outputdir}/{meta[0]['options']['id']}","w")

# point[0] = time
# point[1] = v

x1s = []
y1s = []

x2s = []
y2s = []

for m in meta:

    threshold = 10;
    spike = False
    under = True

    spikec = 0
    prevpoint = [0.0,0.0]
    lastt = 0

    data = open(m['file'])
    for line in data:
        point = line
        point = list(map(lambda x : float(x), point.split(',')))

        if(point[1] > threshold and under):
            spike = True
            under = False

        if(point[1] < prevpoint[1] and spike):
            
            spikec += 1           
            spike = False

        if(point[1] < threshold and not under):
            under = True

        prevpoint = point

    xcoord = m['params']['gammag'] if m['params']['gammag'] < 0 else m['params']['gammad']

    l = m['options']['step'] * m['options']['line'] * m['options']['length'] / 1000
    print(l)

    if  m['params']['gammag'] < 0:
        x1s.append(xcoord)
        y1s.append(spikec / l)
    else:
        x2s.append(xcoord)
        y2s.append(spikec / l)
    #write
    result.write(f"{xcoord}, {spikec / prevpoint[0]}\n")

    data.close()


fig = make_subplots(rows=1, cols=1)
fig.add_trace(go.Scatter(y=y1s,x=x1s,mode="markers", name="Yg"),row=1,col=1)
fig.add_trace(go.Scatter(y=y2s,x=x2s,mode="markers", name="Yd"),row=1,col=1)
fig.write_html(f"{outputdir}/{meta[0]['options']['id']}.html")

result.close()
    
