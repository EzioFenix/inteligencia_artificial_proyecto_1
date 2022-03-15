#include <iostream>
#include <map>
#include <list>
#include <string>
#include <fstream>
#include <cmath>

namespace travel{
	struct Ruta {
		std::map<int,std::string> secciones,recorrido;
		int ponderacion = 0;
		bool activo = true;
		Ruta() {}
		Ruta(std::map<int,std::string> herencia) {
			for (int i = 0; i < herencia.size(); i++)
				this->recorrido.insert(std::pair<int, std::string>(i, herencia.at(i)));
		}
		void anadirCiudad(std::string nombre) {
			this->recorrido.insert(std::pair<int, std::string>(this->recorrido.size(), nombre));
		}
		int anadirSector(std::string sector) {
			for (int i = 0; i < this->secciones.size(); i++)
				if (!this->secciones.at(i).compare(sector))
					return 1;
			this->secciones.insert(std::pair<int,std::string>(this->secciones.size(),sector));
			return 0;
		}
		bool verificarVisita(std::map<int,std::string> sectores) {
			if (sectores.size() != this->secciones.size()) //Para dar por terminado, se verifica si los tamaños son diferentes
				return true;
			activo = false; //Si son iguales, quiere decir que tiene ya todos los sectores ,pues son una colección
			return false;
		}
		void printRuta(){
			int i;
			for (i = 0; i < this->recorrido.size(); i++)
				std::cout << this->recorrido.at(i) << "->";
			for (i = this->recorrido.size() - 2; i > -1; i--)
				std::cout << this->recorrido.at(i) << "->";
			std::cout << "Fin" << std::endl << "Precio: " << (ponderacion * 2) << std::endl;
		}
	};
	struct Ciudad {
		std::string nombre,seccion;
		std::map<int, travel::Ciudad*> destinos;
		std::map<int, int> precios;
		travel::Ruta* rutaOptima;

		Ciudad(std::string nombre,std::string seccion){
			this->nombre = nombre;
			this->seccion = seccion;
			this->rutaOptima = new travel::Ruta();
		}

		std::map<int,travel::Ruta*> generarRutas(std::map<int,travel::Ruta*> lista){
			bool noVisitado; travel::Ciudad* ciudad;
			std::cout << "Iniciando Generacion de rutas de la ciudad: " << this->nombre << std::endl;
			std::cout << "Destinos disponibles: " << this->destinos.size() <<std::endl;
			if (this->rutaOptima->recorrido.empty())
				this->rutaOptima->anadirCiudad(this->nombre);
			for (int i = 0; i < this->destinos.size();i++) {
				ciudad = destinos.at(i); noVisitado = true;
				std::cout << "Operando con la ciudad: " << ciudad->nombre << std::endl;
				for (int j = 0; j < this->rutaOptima->recorrido.size();j++)//Verificando que no se haya visitado anteriormente
						if (!this->rutaOptima->recorrido.at(j).compare(ciudad->nombre)){
							std::cout << "La ciudad: "<< this->rutaOptima->recorrido.at(j) <<" ya fue visitada en esta ruta" << std::endl;
							noVisitado = false;
							break;
						}
				if (noVisitado) {//Si no se ha visitado
						//std::cout << "Esta ciudad: " << ciudad->nombre << " cumple para generar una ruta"<<std::endl;
						travel::Ruta* newRoad = new travel::Ruta(this->rutaOptima->recorrido), *lastRoad;//Se genera una nueva ruta a partir del origen
						newRoad->anadirSector(this->seccion);
						newRoad->ponderacion = this->precios.at(i) + this->rutaOptima->ponderacion; //Incluyendo el costo
						lastRoad = ciudad->visitarCiudad(newRoad); //Hacia el destino en cuestion
						if (lastRoad->recorrido.empty()) //Si no ha sido visitada por otra ruta
							lista.insert(std::pair<int,travel::Ruta*>(lista.size(),newRoad)); //Se añade a la lista de rutas
						else if (lastRoad->ponderacion > newRoad->ponderacion) //Si esta nueva ruta, fue más barata que la establecida
							eliminarDescendencia(lista, lastRoad); //Se eliminará la descendencia que esta hubiese tenido
				}
			}
			return lista;
		}
		travel::Ruta* visitarCiudad(travel::Ruta* nuevaRuta) {
			if (this->rutaOptima->recorrido.empty()) { //Si la ciudad no tiene una ruta aun
				this->rutaOptima = nuevaRuta; //Adoptará la nueva ruta
				this->rutaOptima->anadirCiudad(this->nombre);
				this->rutaOptima->printRuta(); //imprimir ruta
				this->rutaOptima->anadirSector(this->seccion);
				return new travel::Ruta();
			}
			if (this->rutaOptima->ponderacion > nuevaRuta->ponderacion) {//Si la nueva ruta es menor que la optimizada, entonces
				travel::Ruta* aux = this->rutaOptima;
				this->rutaOptima = nuevaRuta; //se añade esta ruta
				this->rutaOptima->anadirCiudad(this->nombre);
				this->rutaOptima->printRuta(); //imprimir ruta
				this->rutaOptima->anadirSector(this->seccion);
				return aux; //Y retorna la ruta anterior para su posterior descarte y descendencia
			}
			return nuevaRuta;
		}
		void eliminarDescendencia(std::map<int,travel::Ruta*> lista, travel::Ruta* objetivo) {
			for (int i = 0; i < lista.size(); i++)
				for (int j = 0; j < objetivo->recorrido.size(); j++)
					if (objetivo->recorrido.at(j).compare(lista.at(i)->recorrido.at(j)))
						break;
					else {
						lista.erase(i); i--;
					}
		}

		int insertarDestino(travel::Ciudad* destino, int costo) {
			std::string name = destino->nombre;
			int size = this->destinos.size();
			if (name.compare(this->nombre)) {
				this->destinos.insert(std::pair<int, travel::Ciudad*>(size, destino));
				this->precios.insert(std::pair<int, int>(size, costo));
				return 0;
			}
			return 1;
		}
		int modificarDestino(std::string destino, int costo) {
			for(int i = 0; i < this->destinos.size();i++)
				if (destinos.at(i)->nombre.compare(destino)) {
					precios.at(i) = costo;
					return 0;
				}
			return 1;

		}
		int eliminarDestino(std::string destino) {
			for (int i = 0; i < this->destinos.size(); i++)
				if (destinos.at(i)->nombre.compare(destino)) {
					destinos.erase(i);
					precios.erase(i);
					return 0;
				}
			return 1;
		}
		void mostrarDestinos(){
			for (int i = 0; i < this->destinos.size(); i++)
					std::cout<<"\t"<<destinos.at(i)->nombre << " -> " << precios.at(i) << std::endl;
		}

		std::string getString() {
			std::string data;
			data.append(this->nombre); data.append(":");
			for (int i = 0; i < this->destinos.size(); i++) {
				data.append(this->destinos.at(i)->nombre); data.append(","); data.append(std::to_string(this->precios.at(i))); data.append(";");
			}
			data.append("\n");
			return data;
		}

	};	
	struct Mapa {
		std::string nombre;
		std::map<int, travel::Ciudad*> ciudades;
		std::map<int,travel::Ruta*> rutas;
		std::map<int, std::string> secciones;
		travel::Ciudad* inicio;

		Mapa(std::string nombre,bool nuevo) {
			this->nombre = nombre;
			if(nuevo)
				this->secciones.insert(std::pair<int,std::string>(0,"sect_0"));
		}

		void establecerInicio(std::string nombre){
			for(int i = 0; i < this->ciudades.size();i++)
				if(!this->ciudades.at(i)->nombre.compare(nombre))
					this->inicio = this->ciudades.at(i);
		}
		//Metodo Principal
		void buscarRuta(){
			rutas.clear();
			rutas = this->inicio->generarRutas(this->rutas);
			int i = 0;
			while (todoTerminado()) {
				std::cout << "Iniciando Ciclo\n";
				if(this->rutas.at(i)->activo)
					for (int j = 0; j < this->ciudades.size(); j++)
						if (!this->ciudades.at(j)->nombre.compare(this->rutas.at(i)->recorrido.at(this->rutas.at(i)->recorrido.size()-1))) {
							rutas = this->ciudades.at(j)->generarRutas(this->rutas);
							this->rutas.erase(i);
							break;
						}
				if (i >= this->rutas.size())
					i = 0;
				else
					i++;
			}
			if (this->rutas.empty())
				std::cout << "Ninguna ruta fue capaz de alcanzar todos los sectores del mapa\n";
			else {
				int min = this->rutas.at(0)->ponderacion;//Se establece un minimo
				std::cout << "Se encontraron las siguientes rutas disponibles: \n";
				for (i = 0; i < this->rutas.size(); i++) {//Descarte final en todas las rutas que cumplen con la condicion de todos los sectores
					if (min < this->rutas.at(i)->ponderacion) {
						this->rutas.erase(i); i--;
					}else if (min > this->rutas.at(i)->ponderacion) {
						min = this->rutas.at(i)->ponderacion; i = 0;
					}
				}
				for (i = 0; i < this->rutas.size(); i++) //Se imprimen los resultados
					this->rutas.at(i)->printRuta();
				
			}
		}

		bool todoTerminado(){
			bool notFinish = false;
			if (this->rutas.empty())
				return notFinish;
			std::cout << "Antes de provocar un desborde, el tamanio es de: " << this->rutas.size() << std::endl;
			for (int i = 0; i < this->rutas.size(); i++) {  //Con que exista una ruta sin terminar, continuara el ciclo
				notFinish = notFinish || this->rutas.at(i)->verificarVisita(this->secciones);
				std::cout << "Ultimo visitado antes del desborde: " << i << std::endl;
			}
			return notFinish;
		}
		int anadirCiudad(std::string nombre, std::string seccion){
			for (int i = 0; i < this->ciudades.size(); i++)
				if (!this->ciudades.at(i)->nombre.compare(nombre))
					return 0;
			this->ciudades.insert(std::pair<int, travel::Ciudad*>(this->ciudades.size(),new Ciudad(nombre,seccion)));
			this->insertarSector(seccion);
			return 0;
		}
		int eliminarCiudad(std::string nombre){
			std::string seccion;
			for(int i = 0; i < this->ciudades.size();i++)
				if (!this->ciudades.at(i)->nombre.compare(nombre)) {
					seccion = this->ciudades.at(i)->seccion;
					this->ciudades.erase(i);
					break;
				}
			for (int i = 0; i < this->ciudades.size(); i++)
				if (!this->ciudades.at(i)->seccion.compare(seccion))
					return 0;
			for (int i = 0; i < this->secciones.size(); i++)
				if (!this->secciones.at(i).compare(seccion)) {
					this->secciones.erase(i);
					if(this->secciones.empty())
						this->secciones.insert(std::pair<int, std::string>(0, "sect_0"));
					return 1;;
				}
			return 2;
		}
		void mostrarCiudades() {
			for (int i = 0; i < this->ciudades.size(); i++) {
				std::cout << this->ciudades.at(i)->nombre <<" Destinos: " << std::endl;
				this->ciudades.at(i)->mostrarDestinos();
			}
		}

		int insertarSector(std::string sector) {
			for (int i = 0; i < this->secciones.size();i++)
				if (!this->secciones.at(i).compare(sector))
					return 1;
			this->secciones.insert(std::pair<int,std::string>(secciones.size(),sector));
			return 0;
		}
		int eliminarSector(std::string sector){
			this->insertarSector("sect_0");
			for (int i = 0; i < this->ciudades.size(); i++)
				if (!this->ciudades.at(i)->seccion.compare(sector))
					this->ciudades.at(i)->seccion = "sect_0";
			for (int i = 0; i < this->secciones.size(); i++)
				if (!this->secciones.at(i).compare(sector)) {
					this->secciones.erase(i); return 0;
				}
			return 1;
		}
		void mostrarSectores() {
			for (int i = 0; i < this->secciones.size(); i++)
				std::cout << this->secciones.at(i) << std::endl;
		}

		travel::Ciudad* obtenerCiudad(std::string nombre) {
			for (int i = 0; i < this->ciudades.size(); i++)
				if (!this->ciudades.at(i)->nombre.compare(nombre)) 
					return ciudades.at(i);
			return nullptr;
		}
		
		std::string getString() {
			std::string data;
			for (int i = 0; i < this->secciones.size();i++) {
				data.append(this->secciones.at(i)); data.append(",");
			}
			data.append("\n");
			for (int i = 0; i < this->ciudades.size(); i++) {
				data.append(this->ciudades.at(i)->nombre); data.append(","); data.append(this->ciudades.at(i)->seccion); data.append("\n");
			}
			for (int i = 0; i < this->ciudades.size(); i++)
				data.append(this->ciudades.at(i)->getString());
			data.append("\n&"); data.append(this->inicio->nombre);
			return data;
		}
	};
}

travel::Mapa* mapaActual;
int x10(int i) {
	int d = 1;
	while (i > 0) {
		d *= 10;
		i--;
	}
	return d;
}
int toInt(std::string args) {
	int n = 0, size = args.length();
	for (int i = 0; i < size; i++)
		n += (args[i] - 48) * x10(size - i-1);
	return n;
}

travel::Mapa* cargarMapa(std::string nombre){
	std::ifstream archive;
	std::string data;
	nombre.append(".mapa");
	archive.open(nombre,std::ios::in);
	if (archive.fail()) {
		std::cout << "No se pudo abrir el archivo: " << nombre << std::endl;
		return nullptr;
	}
	travel::Mapa* mapa = new travel::Mapa(nombre,false);
	std::getline(archive, data);
	int begin = 0,size = 0;
	for (char a : data) //Secciones
		if (a == ',') {
			mapa->insertarSector(data.substr(begin, size));
			begin += size + 1; size = 0;
		}else size++;
	bool state = true;
	size = 0;
	while (!archive.eof() && state) {//Ciudades
		size = 0;
		std::getline(archive, data);
		for (char a : data) {
			if (a == ',') 
				mapa->anadirCiudad(data.substr(0, size), data.substr(size + 1));
			else size++;
			if (a == '$')
				state = false;
		}
	}
	state = true;
	while (!archive.eof() && state) {//Enlaces
		begin = 0, size = 0; travel::Ciudad *city = nullptr,*destiny = nullptr;
		std::getline(archive, data);
		for (char a : data)
			if (a == ':') {
				city = mapa->obtenerCiudad(data.substr(0, size));
				begin += size + 1; size = 0;
			}else if (a == ',') {
				destiny = mapa->obtenerCiudad(data.substr(begin, size));
				begin += size + 1; size = 0;
			}else if (a == ';') {
				city->insertarDestino(destiny, toInt(data.substr(begin, size)));
				begin += size + 1; size = 0;
			}else if (a == '#') {
				mapa->establecerInicio(data.substr(1));
				state = false;
			} else size++;
	}
	archive.close();
	return mapa;
}
int guardarMapa(travel::Mapa* mapa) {
	std::ofstream archive; std::string name = mapa->nombre; name.append(".mapa");
	archive.open(name, std::ios::out);
	if (archive.fail()) {
		std::cout << "No se pudo guardar el Mapa" << std::endl;
		return 1;
	}
	archive << mapa->getString();
	archive.close();
	return 0;
}

void MenuDeCiudad(travel::Ciudad* ciudad) {
	char opcion; std::string nombre; int precio;
	travel::Ciudad* city;
	std::cout << std::endl;
	do {
		std::cout << "Menu de la ciudad \"" << ciudad->nombre << "\"\nSeleccione una opcion:\n"
			<< "1.- Insertar Destino\n"
			<< "2.- Editar Destino\n"
			<< "3.- Eliminar Destino\n"
			<< "4.- Establecer Seccion\n"
			<< "5.- Regresar\n";
		std::cin >> opcion;
		switch (opcion) {
		case '1':
			std::cout << "Insertando Destino...\nCiudades Disponibles:\n"; mapaActual->mostrarCiudades();
			std::cout << "Elija una ciudad: "; std::cin >> nombre; city = mapaActual->obtenerCiudad(ciudad->nombre);
			if (city != nullptr) {
				std::cout << "\nInserte un precio de transito: "; std::cin >> precio;
				ciudad->insertarDestino(city, precio);
				city->insertarDestino(ciudad, precio);
			}
			else
				std::cout << "\nLa ciudad " << nombre << " no existe\n";
			break;
		case '2':
			std::cout << "Editando Destino...\nDestinos Disponibles:\n"; ciudad->mostrarDestinos();
			std::cout << "Elija un destino: "; std::cin >> nombre; std::cout << "\nInserte un precio de transito: "; std::cin >> precio;
			city = mapaActual->obtenerCiudad(ciudad->nombre);
			if (city != nullptr)
				if(ciudad->modificarDestino(nombre, precio))
					city->modificarDestino(ciudad->nombre, precio);
			break;
		case '3':
			std::cout << "Eliminando Destino...\nDestinos Disponibles:\n"; ciudad->mostrarDestinos();
			std::cout << "Elija un destino: "; std::cin >> nombre;
			city = mapaActual->obtenerCiudad(ciudad->nombre);
			if (city != nullptr) {
				city -> eliminarDestino(ciudad->nombre);
				ciudad->eliminarDestino(nombre);
			}
			break;
		case '4':
			std::cout << "Estableciendo seccion...\n"; mapaActual->mostrarSectores();std::cout<< "Elija una seccion: "; std::cin >> nombre;
			ciudad->seccion = nombre; std::cout << std::endl;
			break;
		case '5':
			std::cout << "Regresando al Menu de Mapa...\n";
			break;
		default:
			std::cout << "No se reconoce la opcion: " << opcion << std::endl;
		}
	} while (opcion != '5');
}
int MenuDeMapa(bool protocole) {
	std::cout << "Inserte el nombre del mapa: "; std::string nombre, sector;
	std::cin >> nombre;
	if (protocole)
		mapaActual = new travel::Mapa(nombre,true);
	else {
		mapaActual = cargarMapa(nombre);
		if (mapaActual == nullptr)
			return 1;
	}
	char opcion;
	std::cout << std::endl;
	do {
		std::cout << "Menu del mapa \""<< nombre <<"\"\nSeleccione una opcion:\n"
			<< "1.- Nueva Ciudad\n"
			<< "2.- Modificar Ciudad\n"
			<< "3.- Eliminar Ciudad\n"
			<< "4.- Insertar Sector\n"
			<< "5.- Eliminar Sector\n"
			<< "6.- Ver Todo\n" 
			<< "7.- Establecer Inicio\n"
			<< "8.- Buscar\n" 
			<< "9.- Guardar Mapa\n"
			<< "0.- Regresar\n";
		std::cin >> opcion;
		switch (opcion) {
		case '1':
			std::cout << "Creando Nueva Ciudad...\nCiudades Existentes:\n"; mapaActual->mostrarCiudades();std::cout<<"Inserte el nombre de la Ciudad : ";
			std::cin >> nombre;  std::cout << std::endl << "Sectores Disponibles"; mapaActual->mostrarSectores(); std::cout << "Elija el sector: ";
			std::cin >> sector; 
			mapaActual->anadirCiudad(nombre, sector);
			MenuDeCiudad(mapaActual->obtenerCiudad(nombre));
			break;
		case '2':
			std::cout << "Modificando Ciudad...\n";
			std::cout << std::endl << "Ciudades Disponibles"; mapaActual->mostrarCiudades(); std::cout << "Elija la Ciudad: "; std::cin >> nombre;
			MenuDeCiudad(mapaActual->obtenerCiudad(nombre));
			break;
		case '3':
			std::cout << "Eliminando Ciudad...\n";
			std::cout << std::endl << "Ciudades Disponibles:\n"; mapaActual->mostrarCiudades(); std::cout << "Elija la Ciudad: "; std::cin >> nombre;
			mapaActual->eliminarCiudad(nombre);
			break;
		case '4':
			std::cout << "Creando Sector...\nSectores Existentes:\n"; mapaActual->mostrarSectores(); std::cout << "Inserte el nombre del sector : ";
			std::cin >> sector; mapaActual->insertarSector(sector);
			break;
		case '5':
			std::cout << "Eliminando Sector...\nSectores Existentes:\n"; mapaActual->mostrarSectores(); std::cout << "Inserte el nombre del sector : ";
			std::cin >> sector; mapaActual->eliminarSector(sector);
			break;
		case '6':
			std::cout << "Ciudades:\n";
			mapaActual->mostrarCiudades();
			std::cout << "\nSectores:\n";
			mapaActual->mostrarSectores();
			std::cout << "\nCiudad Inicial: " << mapaActual->inicio->nombre;
			break;
		case '7':
			std::cout << "Estableciendo inicio...\n";
			std::cout << std::endl << "Ciudades Disponibles:\n"; mapaActual->mostrarCiudades(); std::cout << "Elija la Ciudad: "; std::cin >> nombre;
			mapaActual->establecerInicio(nombre);
			break;
		case '8':
			std::cout << "Buscando...\n";
			mapaActual->buscarRuta();
			break;
		case '9':
			std::cout << "Guardando Cambios...\n";
			break;
		case '0':
			std::cout << "Regresando a Menu Principal...\n";
			break;
		default:
			std::cout << "No se reconoce la opcion: " << opcion << std::endl;
		}
	} while (opcion != '0');
	return 0;
}
int main() {
	char opcion;
	std::cout << "Eagle Guide by DynamicWare 2.1.13" << std::endl;
	do {
		std::cout << "Seleccione una opcion:\n" 
				  << "1.- Construir Nuevo Mapa\n"
				  << "2.- Cargar Nuevo Mapa\n"
			      << "3.- Salir\n";
		std::cin >> opcion;
		switch (opcion) {
			case '1':
				std::cout << "Construir un mapa...\n";
				MenuDeMapa(true);
				break;
			case '2':
				std::cout << "Cargando un mapa...\n";
				MenuDeMapa(false);
				break;
			case '3':
				std::cout << "Saliendo del programa..\n";
				break;
			default:
				std::cout << "No se reconoce la opcion: " << opcion << std::endl;
		}
	} while (opcion != '3');
	std::cout << "Programa Finalizado con Exito\n";
	return 0;
}
