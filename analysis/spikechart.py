
import csv
import sys
import json

import plotly.graph_objects as go
from plotly.subplots import make_subplots

metafile = sys.argv[1]
outputdir = sys.argv[2]

f = open(metafile,)
meta = json.load(f);
f.close()

dxs = []
dys = []

size = 0

for m in meta:

    xs = []
    ys = []

    data = open(m['file'])
    for line in data:

        point = line
        point = list(map(lambda x : float(x), point.split(',')))
        
        xs.append(point[0])
        ys.append(point[1])

    data.close()
    size += 1

    dxs.append(xs)
    dys.append(ys)

fig = make_subplots(rows=size, cols=1)
for i in range(size):
    fig.add_trace(go.Scatter(y=dys[i],x=dxs[i],mode="lines", name="v(t)"),row=i+1,col=1)

fig.write_html(f"{outputdir}/{meta[0]['options']['id']}.html")
