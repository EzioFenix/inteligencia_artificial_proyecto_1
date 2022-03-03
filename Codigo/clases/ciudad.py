from .ruta import ruta

class ciudad:
    nombre = 'city'
    optPath = None # Ruta optima
    destinos = list() # ciudades vecinas a las que estan 
    costo = list() # Costo por el destino, asociado a la lista destinos
    seccion = int()


    def _init_(self,nombre: str,seccion:int):
        self.nombre = nombre
        self.set_seccion(seccion)
	print ('Se ha creado exitosamente la ciudad: '+ self.nombre+'\n')


    def anadirDestino(self,destino:ciudad,costo:int):
        self.destinos.append(destino)
        self.costo.append(costo)
	print('Se ha anadido el destino: '+destino.nombre+'\tCoste: '+costo+'\n')

    def quitarDestino(self,nombre: str):
        n = 0
        for target in self.destinos:
            if target.nombre == nombre:
                self.destinos.pop(n)
                self.costo.pop(n)
                break
            else:
                n+=1
	print('Se ha removido el destino: '+nombre+'\n')

    def modCosto(self,nombre:str,costo):   
        n = 0
        for target in self.destinos:
            if target.nombre == nombre:
                self.costo.pop(n)
                self.costo.insert(n,costo)
                break
            else:
                n+=1
	print('Se ha modificado el coste al destino: '+nombre+' por '+'\n')
	
    def setterSeccion(self, seccion: int):
        self.seccion = seccion
        
    def GeneraRutas(self,lista):
    	if (self.optPath == None):
    		self.optPath = ruta()
    		self.optPath.recorrido.append(self)
		print ('Se insertara ruta a los orígenes\n')
    	n = 0
    	for destino in self.Destinos:
    		noVisto = True
    		for camino in self.optPath.recorrido:
    			noVisto = noVisto and (destino != camino)
    		if (noVisto):
    			hijo = ruta()
    			hijo.recorrido = self.optPath
    			hijo.pronderacion = self.precios.get(n) + self.optPath.ponderacion
    			hijo.recorrido.append(destino)
    			lista.append(hijo)
			print('El destino: '+destino.nombre+'no ha sido visitado anteriormente\n')
    		n+=1

def InsertarRuta(self, ruta):
	if (self.optPath == None):
		self.optPath = ruta
		print('La primera vez que esta ciudad es visitada en esta ruta\n')
		return None
	if(self.optPath.ponderacion > ruta.ponderacion):
		aux = self.optPath
		self.optPath = ruta
		print('La nueva ruta consiguió ser mejor que la establecida')
		return aux
