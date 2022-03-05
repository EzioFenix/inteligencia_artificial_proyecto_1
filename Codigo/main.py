from http.client import NON_AUTHORITATIVE_INFORMATION
from typing import List
from json.tool import main
import clases.ciudad as ciudad
import clases.mapa as mapa
import clases.ruta as ruta


def introduciendoSecciones()-> List[int]:
    secciones=[]
    terminaste=False

    # Verifica si no esta en la lista entonces la agrega
    while not terminaste:
        print("introduce seccion: ")
        aux=input()
        aux=int(aux.strip())
        if not (aux in secciones):
            print ("Agregada")
            secciones.append(aux)
        else:
            print("La sección ya esta registrada")

        # Preguntamos si ya termino
        print("¿quieres seguir introduciendo? (s==si/n==no,default==si)?")
        aux=input()
        aux=aux.strip()
        if aux=="n":
            terminaste=True

    return secciones

def introduccionCiudades(secciones: List[int])-> List[ciudad.ciudad]:
    ciudades=List[ciudad.ciudad]
    

    # Auxiliares de verificacion
    nombreCiudades=[] # Auxiliar para verificar que los nombres no se repitan
    terminaste=False

    # Verifica si no esta en la lista entonces la agrega
    while not terminaste:
        # Variables auxiliares
        nombreCiudad = str()
        seccion=int()


        # Introduce el nombre de la ciudad
        while nombreCiudad=="":
            print("Introduce nombre: ")
            aux=input()
            aux=aux.strip()
            if not(aux in nombreCiudades):
                nombreCiudad=aux
            

        # Introduce la seccion a la que pertenece
        while seccion=="":
            print("introduce seccion: ")
            aux=input()
            aux=int(aux.strip())
            if  aux in secciones:
                seccion=aux
                secciones.append(aux)
            else:
                print("La sección no existe, vuelve a intentar")

        # Creamos la ciudad y la introudcimos a la lista
        nuevaCiudad=ciudad.ciudad(nombreCiudad,seccion)
        ciudades.append(nuevaCiudad)
            

        # Preguntamos si ya termino
        print("¿quieres seguir introduciendo ciudades? (s==si/n==no,default==si)?")
        aux=input()
        aux=aux.strip()
        if aux=="n":
            terminaste=True

    return ciudades

def introducirDirecciones(ciudades: List[ciudad.ciudad],nombreCiudades: List[str]):
    terminaste=False
    destinos=List[int]

    for ciudadNombre in nombreCiudades:
        print("Para " + ciudadNombre + " :")

        while not terminaste:
            nombreDestino=str()
            while nombreDestino=="":
                print("introduce ele nombre de la ciudad destino")
                nombreDestino=input()
                nombreDestino=nombreDestino.strip()
                if nombreDestino in nombreCiudades:
                    numeroDestino=nombreCiudades.index(nombreDestino)
                    pesoDestino= 0
                    while pesoDestino<1:
                        print("Introduce peso destino")
                        
                
                
    
    

def main():

    print("Creando mapa ...")
    mapaVar=mapa.mapa() # Mapa variable
    #print("Introduce la ciudad origen")

    
    print("Introduce las secciones")
    auxSecciones=introduciendoSecciones()
    mapaVar.setSecciones(auxSecciones)

    print("Introducir ciudades")


    print("introductir las direcciones")

    print("Este es el mapa")
    print(mapaVar)



if __name__ == "__main__":
    main()