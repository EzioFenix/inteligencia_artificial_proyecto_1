from .mapa import mapa
from .ciudad import ciudad
currMap = None
currCity = None

def inicio():
    print ('Algoritmo Eagle Guide by DynamicWare\n')
    opt = True
    while opt:
        print ('Ingrese el numero de la opcion:\n')
        print ('1.-Crear Mapa\n')
        print ('2.-Cargar Mapa\n')
        print ('3.-Salir')
        args=input()
        if args == '1':
            crearMapa()
        elif args == '2':
            pass
        elif args == '3':
            opt = False
        else:
            print ('No se reconocio opción: ' + args)
    print ('Programa Finalizado')

def crearMapa():
    print( 'Inserte el nombre del mapa')
    currMap = mapa(input())
    opt = True
    while opt:
        print ('Menu de Mapa:\nIngrese el numero de la opcion:\n')
        print ('1.-Crear Ciudad\n')
        print ('2.-Modificar Ciudad\n')
        print ('3.-Borrar Ciudad\n')
        print ('4.-Ver Ciudad\n')
        print ('5.-Ver Todo\n')
        print ('6.-Ajustar Ciudad Inicio\n')
        print ('7.-Retornar\n')
        args=input()
        if args == '1':
            nombre = input()
            currCity = currMap.buscarCiudad(nombre)
            if currCity != None:
                print('Se encontro una ciudad con ese nombre, se procede a editar\n')
            else:
                currCity = ciudad(nombre,0)
            editarCiudad()
        elif args == '2':
            print('Inserte nombre de la ciudad\n')
            currCity = currMap.buscarCiudad(input())
            if currCity == None:
                print('No se encontró esa ciudad\n')
            else:
                editarCiudad()
            
        elif (args == '7'):
            opt = False
        else:
            print ('No se reconocio opción: ' + args)


def editarCiudad():
    opt = True
    while opt:
        print ('Menu de Ciudad:\nIngrese el numero de la opcion:\n')
        print ('1.-Inserte Nombre\n')
        print ('2.-Inserte Destino\n')
        print ('3.-Editar Destino\n')
        print ('4.-Eliminar Destino\n')
        print ('5.-Insertar Seccion\n')
        print ('6.-Volver\n')
        args=input()
        if args == 1:
            print('Inserte nombre de la ciudad\n')
            currCity.nombre = input()
        elif args == 2:
            print('Inserte nombre de la ciudad a enlazar\n')
            cit = currMap.buscarCiudad(input())
            if cit == None:
                print ('Esa ciudad no existe\n')
            else:
                print('Inserte el costo\n')
                pond = input()
                currCity.anadirRuta(cit,pond)
                cit.anadirRuta(currCity,pond)
        elif args == 3:
            pass