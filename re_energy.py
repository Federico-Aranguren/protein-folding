import pandas as pd
Data = {}
paso = 0
f = open('datos.txt','r')
iteracion = 0
for row in f:
    row = row.split()
    if row[0]=='Ms':
        paso +=1
        Data[f'Energia{paso}'] = {}
        iteracion = 0 
        a = True
    elif row[0] == 'X':
        Data[f'Penergia{paso}'] = {}
        iteracion =0
        a = False 
    else:
        iteracion += 1
        if (a == True):
            Data[f'Energia{paso}'][f'{iteracion}'] = {'Ms':row[0],'E':row[1]}
        else:
            if len(row) == 3:
                Data[f'Penergia{paso}'][f'{iteracion}'] = {'X':row[0],'Y':row[1],'Z':row[2]}
            else:
                Data[f'Penergia{paso}'][f'{iteracion}'] = {'X':row[0],'Y':row[1]}
for iteracion in Data.keys():
    Data[iteracion] = pd.DataFrame(Data[iteracion]).T
    Data[iteracion].to_csv(f'Datos/{iteracion}') 

        