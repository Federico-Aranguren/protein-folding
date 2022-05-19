import pandas as pd
Data = {}
paso = 0
f = open('datos.txt','r')
iteracion = 0
for row in f:
    row = row.split()
    if row[0]=='X':
        paso +=1
        Data[f'Iteracion{paso}'] = {}
        iteracion = 0
    else:
        iteracion += 1
        Data[f'Iteracion{paso}'][f'{iteracion}'] = {'X':row[0],'Y':row[1]}
for iteracion in Data.keys():
    Data[iteracion] = pd.DataFrame(Data[iteracion]).T
    Data[iteracion].to_csv(f'Datos/{iteracion}')