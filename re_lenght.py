import pandas as pd
Data = {}
paso = 0
f = open('datos.txt','r')
iteracion = 0
for row in f:
    row = row.split()
    if row[0]=='Ms':
        paso +=1
        Data[f'Longitud{paso}'] = {}
        iteracion = 0 
        a = True
    elif row[0] == 'X':
        Data[f'Plongitud{paso}'] = {}
        iteracion =0
        a = False 
    else:
        iteracion += 1
        if (a == True):
            Data[f'Longitud{paso}'][f'{iteracion}'] = {'Ms':row[0],'L':row[1]}
        else:
            if len(row) == 3:
                Data[f'Plongitud{paso}'][f'{iteracion}'] = {'X':row[0],'Y':row[1],'Z':row[2]}
            else:
                Data[f'Plongitud{paso}'][f'{iteracion}'] = {'X':row[0],'Y':row[1]}
for iteracion in Data.keys():
    Data[iteracion] = pd.DataFrame(Data[iteracion]).T
    Data[iteracion].to_csv(f'Datos/{iteracion}') 

        