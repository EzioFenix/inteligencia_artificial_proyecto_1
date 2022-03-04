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



def main():

    print("Creando mapa ...")
    mapaVar=mapa.mapa() # Mapa variable
    #print("Introduce la ciudad origen")

    
    print("Introduce las secciones")
    auxSecciones=introduciendoSecciones()
    mapaVar.setSecciones(auxSecciones)


    print("Este es el mapa")
    print(mapaVar)


if __name__ == "__main__":
    main()