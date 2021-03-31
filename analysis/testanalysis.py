
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

result = open(f"{outputdir}/{meta[0]['options']['pid']}","w")

# point[0] = time
# point[1] = v

xs = []
ys = []

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
            dt = point[0] - lastt
            dt /= 1000 # 
            lastt = point[0]
            xcoord = m['params']['gammag'] if m['params']['gammag'] < 0 else m['params']['gammad']
            #print
            xs.append(xcoord)
            ys.append(dt)
            #write
            result.write(f"{xcoord}, {dt}\n")
            
            spike = False

        if(point[1] < threshold and not under):
            under = True

        prevpoint = point

    data.close()


fig = make_subplots(rows=1, cols=1)
fig.add_trace(go.Scatter(y=ys,x=xs,mode="markers", name="distribution"),row=1,col=1)
fig.write_html(f"{outputdir}/{meta[0]['options']['pid']}.html")

result.close()
    
