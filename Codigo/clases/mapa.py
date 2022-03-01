from .ciudad import ciudad

class mapa:
    nombre = str()
    ciudades = list()
    rutas = list()
    sectores = list()
    inicio = None
    

    def anadirCiudad(self,ciudad:ciudad):
        self.ciudades.append(ciudad)
        for sector in self.sectores():
            if(ciudad.seccion == sector):
                return 0
        self.sectores.append(ciudad.sector)
        self.sectores.sort()
        
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
