import pandas as pd
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import imageio.v2 as imageio
import os
import cv2

maxdata = max([int(file.replace('Iteracion','')) for file in os.listdir('Datos') if '.png' not in file])+1

img_array = []
minx = 5000
maxx =-5000
miny = 5000
maxy =-5000
minz = 5000
maxz = -5000
Resultados = {}
for i in range(1,maxdata):
    data = pd.read_csv(f'Datos/Iteracion{i}',index_col=0)
    if max(data.Y)>maxy:
        maxy=max(data.Y)
    if max(data.X)>maxx:
        maxx=max(data.X)
    if max(data.Z)>maxz:
        maxz=max(data.Z)
    if min(data.Y)<miny:
        miny=min(data.Y)
    if min(data.X)<minx:
        minx=min(data.X)
    if min(data.Z)<minz:
        minz=min(data.Z)
    Resultados[f'data{i}'] = data
    print(i)
for file in Resultados.keys():
    i = int(file.replace('data',''))
    print(file)
    fig = plt.figure()
    data = Resultados[file]
    ax = fig.add_subplot(111, projection='3d')
    # fig,ax = plt.subplots(1)
    fig.suptitle(f'Iteracion {i}')
    ax.plot(data.X,data.Y,data.Z,ls = '-',marker = 'o',color = 'k',markersize=3)
    ax.set_xlim(minx-0.5,maxx+0.5)
    ax.set_ylim(miny-0.5,maxy+0.5)
    ax.set_zlim(minz-0.5,maxz+0.5)
    #ax.axis('off')
    fig.savefig(f'Datos/Iteracion{i}.png',bbox_inches='tight')
    #plt.show()
    plt.close(fig)
    img = cv2.imread(f'Datos/Iteracion{i}.png')
    height, width, layers = img.shape
    size = (width,height)
    img_array.append(img)

out = cv2.VideoWriter('Proteina3D.mp4',cv2.VideoWriter_fourcc(*'mp4v'), 40, size)

for j in range(len(img_array)):
    out.write(img_array[j])
out.release()

