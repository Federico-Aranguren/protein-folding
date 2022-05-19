import pandas as pd
from matplotlib import pyplot as plt
import imageio.v2 as imageio
import os
maxdata = max([int(file.replace('Iteracion','')) for file in os.listdir('Datos') if '.png' not in file])+1

giffile = 'CintiaSofiaPinillaPrada.gif'

Image_Data = []
minx = 5000
maxx =-5000
miny = 5000
maxy =-5000
Resultados = {}
for i in range(1,maxdata):
    data = pd.read_csv(f'Datos/Iteracion{i}',index_col=0)
    if max(data.Y)>maxy:
        maxy=max(data.Y)
    if max(data.X)>maxx:
        maxx=max(data.X)
    if min(data.Y)<miny:
        miny=min(data.Y)
    if min(data.X)<minx:
        minx=min(data.X)
    Resultados[f'data{i}'] = data
    print(i)
for file in Resultados.keys():
    print(file)
    data = Resultados[file]
    fig,ax = plt.subplots(1)
    fig.suptitle(f'Iteracion {i}')
    ax.plot(data.X,data.Y,ls = '-',marker = 'o',color = 'k',markersize=3)
    ax.set_xlim(minx-0.5,maxx+0.5)
    ax.set_ylim(miny-0.5,maxy+0.5)
    ax.axis('off')
    fig.savefig(f'Datos/Iteracion{i}.png',bbox_inches='tight')
    plt.close(fig)
    idata = imageio.imread('Datos/Iteracion'+str(i)+'.png')
    Image_Data.append(idata)
imageio.mimwrite(giffile, Image_Data, format= '.gif', fps = 250)