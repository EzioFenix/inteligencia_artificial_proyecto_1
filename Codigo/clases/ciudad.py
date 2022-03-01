class ciudad:
    nombre = ""
    optPath = None # Ruta optima
    destinos = list() # ciudades vecinas a las que estan 
    costo = list() # Costo por el destino, asociado a la lista destinos
    seccion = int()


    def _init_(self,nombre: str,seccion:int):
        self.nombre = nombre
        self.set_seccion(seccion)


        """_summary_
        """
    def anadirRuta(self,destino,costo:int):
        self.destinos.append(destino)
        self.costo.append(costo)


        """_summary_
        """
    def quitarRuta(self,nombre: str):
        n = 0
        for target in self.destinos:
            if target.nombre == nombre:
                self.destinos.pop(n)
                self.costo.pop(n)
                break
            else:
                n+=1

        

        """_summary_
        """
    def modCosto(self,nombre:str,costo):   
        n = 0
        for target in self.destinos:
            if target.nombre == nombre:
                self.costo.pop(n)
                self.costo.insert(n,costo)
                break
            else:
                n+=1

    """
    Establece el valor de la sección
    """         
    def setterSeccion(self, seccion: int):
        self.seccion = seccion
        
     #Se requiere de comprobación en grupo
        
    def GeneraRutas(self,lista):
	if (self.optPath == NONE):
		self.optPath = Ruta()
		self.optPath.recorrido.append(self)
	n = 0
	for destino in self.Destinos:
		noVisto = True
		for camino in self.optPath.recorrido:
			noVisto = noVisto and (destino != camino)
		if (noVisto):
			hijo = Ruta()
			hijo.recorrido = self.optPath
			hijo.pronderacion = self.precios.get(n) + self.optPath.ponderacion
			hijo.recorrido.append(destino)
			lista.append(hijo)
		n+=1

def InsertarRuta(self, ruta):
	if (self.optPath == NONE):
		self.optPath = ruta
		return NONE
	if(self.optPath.ponderacion > ruta.ponderacion)
		aux = self.optPath
		self.optPath = ruta
		return aux
	return ruta
