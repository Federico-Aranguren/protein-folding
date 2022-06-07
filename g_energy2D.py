import pandas as pd
from matplotlib import pyplot as plt
import imageio.v2 as imageio
import os


# for file in os.listdir('Datos'):
#     file.replace('Energia','')
#     file.replace('Penergia','')

# maxdata = max([int(file.replace('','')) for file in os.listdir('Datos/') if '.png' not in file])+1
minx = 5000
maxx =-5000
miny = 5000
maxy =-5000
ResultadosE = {}
ResultadosP = {}
for i in range(1,21):
    dataE = pd.read_csv(f'Datos/Energia{i}',index_col=0)
    dataP = pd.read_csv(f'Datos/Penergia{i}',index_col=0)
    if max(dataP.Y)>maxy:
        maxy=max(dataP.Y)
    if max(dataP.X)>maxx:
        maxx=max(dataP.X)
    if min(dataP.Y)<miny:
        miny=min(dataP.Y)
    if min(dataP.X)<minx:
        minx=min(dataP.X)
    ResultadosE[f'data{i}'] = dataE
    ResultadosP[f'data{i}'] = dataP
    print(i)

for file in ResultadosE.keys():
    i = int(file.replace('data',''))
    print(file)
    data = ResultadosE[file]
    fig,ax = plt.subplots(1)
    fig.suptitle('Energia vs. Ms')
    ax.plot(data.Ms,data.E,ls = '-',color = 'k',markersize=1)
    plt.xlabel('Montecarlo steps')
    plt.ylabel('Energy')
    fig.savefig(f'Datos/Energia{i}.png',bbox_inches='tight')
    plt.close(fig)
for file in ResultadosP.keys():
    i = int(file.replace('data',''))
    print(file)
    data = ResultadosP[file]
    fig,ax = plt.subplots(1)
    fig.suptitle(f'Proteina{i}')
    ax.plot(data.X,data.Y,ls = '-',marker = 'o',color = 'k',markersize=3)
    ax.set_xlim(minx-0.5,maxx+0.5)
    ax.set_ylim(miny-0.5,maxy+0.5)
    ax.axis('off')
    fig.savefig(f'Datos/Proteina{i}.png',bbox_inches='tight')
    plt.close(fig)
