from .ciudad import ciudad

class mapa:
    nombre = str()
    ciudades = list()
    rutas = list()
    sectores = 0
    inicio = None
    

    def anadirCiudad(self,ciudad:ciudad):
        self.ciudades.append(ciudad)
        
        
    def quitarCiudad(self,nombre: str):
        n = 0
        for target in self.ciudades:
            if target.nombre == nombre:
                self.ciudades.pop(n)
                break
            else:
                n+=1