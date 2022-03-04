from .ciudad import ciudad

class mapa:
    
    def __init__(self) -> None:
        self.nombre = str() # Nombre del mapa
        self.ciudades = list() # Ciudades que tine el mapa
        self.rutas = list() # 
        self.secciones = list() # Introduce la secciones 
        self.inicio:ciudad = None # Ciudad de origen

    def setSecciones(self,secciones: list):
        self.secciones=secciones.copy()

    def anadirCiudad(self,):
        self.ciudades.append(ciudad)
        
        
    def quitarCiudad(self,nombre: str):
        n = 0
        for target in self.ciudades:
            if target.nombre == nombre:
                self.ciudades.pop(n)
                break
            else:
                n+=1

    def __repr__(self) -> str:
        secciones="secciones:" + ','.join([str(elem) for elem in self.secciones])
        return secciones