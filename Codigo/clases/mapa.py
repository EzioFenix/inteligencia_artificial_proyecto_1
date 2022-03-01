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
            if(ciudad.seccion == sector)
                return 0
        self.sectores.append(ciudad.sector)
        self.sectores.sort()
        
    def quitarCiudad(self,nombre: str):
        n = 0
        for target in self.ciudades:
            if target.nombre == nombre:
                sect = target.seccion
                self.ciudades.pop(n)
                purgarSectores(sect)
                break
            else:
                n+=1
   def purgarSectores(self,sector):
        for ciudad in self.ciudades:
            if(ciudad.seccion == sector):
                return 0
        n = 0
        for seccion in self.sectores():
            if(seccion = sector)
                self.sectores.pop(n)
                return 1
            else
                n += 1
