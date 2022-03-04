from .ciudad import ciudad

class mapa:
    
    def __init__(self) -> None:
        self.nombre = str() # Nombre del mapa
        self.ciudades = list() # Ciudades que tine el mapa
        self.rutas = list() # 
        self.secciones = list() # Introduce la secciones 
        self.inicio:ciudad = None # Ciudad de origen

    def setSecciones(self,nombre:str,secciones: list):
        self.secciones=secciones.copy()
        self.nombre = nombre

    def anadirCiudad(self,nombre):
        self.ciudades.append(ciudad(nombre,0))
        for sector in self.sectores():
            if(ciudad.seccion == sector):
                return 0
        self.sectores.append(ciudad.sector)
        self.sectores.sort()
    def buscarCiudad(self,nombre: str):
        for city in self.ciudades:
            if(city.nombre == nombre):
                return city
        return None

    def quitarCiudad(self,nombre: str):
        n = 0
        for target in self.ciudades:
            if target.nombre == nombre:
                sect = target.seccion
                self.ciudades.pop(n)
                self.purgarSectores(sect)
                break
            else:
                n+=1

    def __repr__(self) -> str:
        secciones="secciones:" + ','.join([str(elem) for elem in self.secciones])
        return secciones
    def purgarSectores(self, sector: list):
        for city in self.ciudades:
            if(city.seccion == sector):
                return 0
        n = 0
        for seccion in self.sectores:
            if seccion == sector:
                self.sectores.pop(n)
                return 1
            else:
                n += 1
                
                
    #Se requiere de revision
    def Buscar(self):
        pass
    def ElimDes(self,ruta):
        n = 0
        for camino in self.PathList:
            pariente = False
            for city in camino.recorrido:
                for destino in ruta.recorrido:
                    if(destino.nombre != city.nombre):
                        n+=1
                        pariente = False
                        break
                    else:
                        pariente = True
                    if pariente:
                        self.PathList.pop(n)
