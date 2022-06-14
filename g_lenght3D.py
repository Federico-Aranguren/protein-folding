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
minz = 5000
maxz = -5000
ResultadosL = {}
ResultadosP = {}
for i in range(1,3):
    dataL = pd.read_csv(f'Datos/Longitud{i}',index_col=0)
    dataP = pd.read_csv(f'Datos/Plongitud{i}',index_col=0)
    if max(dataP.Y)>maxy:
        maxy=max(dataP.Y)
    if max(dataP.X)>maxx:
        maxx=max(dataP.X)
    if max(dataP.Z)>maxz:
        maxz=max(dataP.Z)
    if min(dataP.Y)<miny:
        miny=min(dataP.Y)
    if min(dataP.X)<minx:
        minx=min(dataP.X)
    if min(dataP.Z)<minz:
        minz=min(dataP.Z)
    ResultadosL[f'data{i}'] = dataL
    ResultadosP[f'data{i}'] = dataP
    print(i)

for file in ResultadosL.keys():
    i = int(file.replace('data',''))
    print(file)
    data = ResultadosL[file]
    plt.rcParams['figure.figsize'] = (20, 7)
    fig,ax = plt.subplots(1)
    fig.suptitle(f'Longitud vs. Ms')
    ax.plot(data.Ms,data.L,ls = '-',color = 'k',markersize=1)
    plt.xlabel('Montecarlo steps')
    plt.ylabel('Lenght')
    fig.savefig(f'Datos/Longitud{i}.png',bbox_inches='tight')
    plt.clf()
    plt.close('all')
for file in ResultadosP.keys():
    i = int(file.replace('data',''))
    print(file)
    fig = plt.figure()
    data = ResultadosP[file]
    ax = fig.add_subplot(111, projection='3d')
    fig.suptitle(f'Proteina')
    ax.plot(data.X,data.Y,data.Z,ls = '-',marker = 'o',color = 'k',markersize=3)
    ax.set_xlim(minx-0.5,maxx+0.5)
    ax.set_ylim(miny-0.5,maxy+0.5)
    ax.set_zlim(minz-0.5,maxz+0.5)
    fig.savefig(f'Datos/Proteina(L){i}.png',bbox_inches='tight')
    plt.clf()
    plt.close('all')
