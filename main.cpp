#include <iostream>
#include <map>
#include <list>
#include <string>
#include <fstream>
#include <cmath>

namespace travel{
	struct Ruta;

	struct Ciudad {
		std::string nombre,seccion;
		std::map<std::string, travel::Ciudad*> destinos;
		std::map<std::string, int> precios;

		Ciudad(std::string nombre,std::string seccion){
			this->nombre = nombre;
			this->seccion = seccion;
		}
		int insertarDestino(travel::Ciudad* destino, int costo) {
			std::string name = destino->nombre;
			if (name.compare(this->nombre)) {
				this->destinos.insert(std::pair<std::string, travel::Ciudad*>(name, destino));
				this->precios.insert(std::pair<std::string, int>(name, costo));
				return 0;
			}
			return 1;
		}
		int modificarDestino(std::string destino, int costo) {
			std::map<std::string, int>::iterator it = this->precios.find(destino);
			if (it != this->precios.end()) {
				it->second = costo;
				return 1;
			}else
				return 0;

		}
		void eliminarDestino(std::string destino) {
			this->destinos.erase(destino);
			this->precios.erase(destino);
		}
		void mostrarDestinos(){}

		std::string getString() {
			std::string data;
			data.append(this->nombre); data.append(":");
			std::map<std::string, travel::Ciudad*>::iterator it;
			for (it = this->destinos.begin(); it != this->destinos.end(); ++it) {
				data.append(it->first); data.append(","); data.append(std::to_string(precios.find(it->first)->second)); data.append(";");
			}
			data.append("\n");
			return data;
		}

	};
	struct Ruta {
		std::list<travel::Ciudad> recorrido;
		travel::Ciudad* ciudad = nullptr;
		int ponderacion;
		bool activo;

		void printRuta() {
			for (travel::Ciudad city : recorrido)
				std::cout << city.nombre << " -> ";
			std::cout << std::endl << "Precio: " << ponderacion << std::endl;
		}
	};
	struct Mapa {
		std::string nombre;
		std::map<std::string, travel::Ciudad*> ciudades;
		std::list<travel::Ruta> rutas;
		std::list<std::string> secciones;
		travel::Ciudad* inicio = nullptr;

		Mapa(std::string nombre) {
			this->nombre = nombre;
			this->secciones.push_front("sect_0");
		}

		void establecerInicio(std::string nombre) {
			this->inicio = this->ciudades.find(nombre)->second;
		}

		int anadirCiudad(std::string nombre, std::string seccion){
			std::map<std::string, travel::Ciudad*>::iterator it;
			for (it = this->ciudades.begin(); it != this->ciudades.end(); ++it)
				if (!it->second->nombre.compare(nombre))
					return 0;
			this->ciudades.insert(std::pair<std::string, travel::Ciudad*>(nombre,new Ciudad(nombre,seccion)));
			this->insertarSector(seccion);
		}
		int eliminarCiudad(std::string nombre){
			std::string sector = this->ciudades.find(nombre)->second->seccion;
			this->ciudades.erase(nombre);
			std::map<std::string, travel::Ciudad*>::iterator it;
			for (it = this->ciudades.begin(); it != this->ciudades.end(); ++it)
				if (!it->second->seccion.compare(sector))
					return 0;
			std::list<std::string>::iterator it1;
			for(it1 = this->secciones.begin(); it1 != this->secciones.end();++it1)
				if (it1->compare(sector)) {
					this->secciones.erase(it1);
					if(this->secciones.empty())
						this->insertarSector("sect_0");
					return 1;
				}
			return 2;
		}
		void mostrarCiudades() {
			std::map<std::string, travel::Ciudad*>::iterator it;
			for (it = this->ciudades.begin(); it != this->ciudades.end(); ++it)
				std::cout << it->first << std::endl;
		}

		int insertarSector(std::string sector) {
			for (std::string sect : this->secciones)
				if (!sect.compare(sector))
					return 1;
			this->secciones.push_back(sector);
			return 0;
		}
		int eliminarSector(std::string sector){
			this->insertarSector("sect_0");
			std::map<std::string, travel::Ciudad*>::iterator it;
			for (it = this->ciudades.begin(); it != this->ciudades.end(); ++it)
				if (!it->second->seccion.compare(sector))
					it->second->seccion = "sect_0";
			std::list<std::string>::iterator it1;
			for (it1 = this->secciones.begin(); it1 != this->secciones.end(); ++it1)
				if (it1->compare(sector)) {
					this->secciones.erase(it1);
					return 0;
				}
			return 1;
		}
		void mostrarSectores() {
			for (std::string sect : this->secciones)
				std::cout << sect << std::endl;
		}
		
		std::string getString() {
			std::string data;
			for (std::string sect : this->secciones) {
				data.append(sect); data.append(",");
			}
			data.append("\n");
			std::map<std::string, travel::Ciudad*>::iterator it;
			for (it = this->ciudades.begin(); it != this->ciudades.end(); ++it) {
				data.append(it->second->nombre); data.append(","); data.append(it->first); data.append("\n");
			}
			for (it = this->ciudades.begin(); it != this->ciudades.end(); ++it)
				data.append(it->second->getString());
			data.append("\n&"); data.append(this->inicio->nombre);
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
	travel::Mapa* mapa = new travel::Mapa(nombre);
	std::getline(archive, data);
	int begin = 0,size = 0;
	for (char a : data) //Secciones
		if (a == ',') {
			mapa->insertarSector(data.substr(begin, size));
			begin += size + 1; size = 0;
		}else size++;
	bool state = true;
	std::getline(archive, data); size = 0;
	while (!archive.eof() && state) {//Ciudades
		size = 0;
		for (char a : data) {
			if (a == ',')
					mapa->anadirCiudad(data.substr(0, size), data.substr(size + 1));
			else size++;
			if (a == '$')
				state = false;
		}
		std::getline(archive, data);
	}
	state = true;
	while (!archive.eof() && state) {//Enlaces
		begin = 0, size = 0; travel::Ciudad *city = nullptr,*destiny = nullptr;
		for (char a : data)
			if (a == ':') {
				city = mapa->ciudades.find(data.substr(0, size))->second;
				begin += size + 1; size = 0;
			}else if (a == ',') {
				destiny = mapa->ciudades.find(data.substr(begin, size))->second;
				begin += size + 1; size = 0;
			}else if (a == ';') {
				city->insertarDestino(destiny, toInt(data.substr(begin, size)));
				begin += size + 1; size = 0;
			}else if (a == '&') {
				mapa->establecerInicio(data.substr(1));
				state = false;
			} else size++;
		
		std::getline(archive, data);
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
	std::map<std::string, travel::Ciudad*>::iterator it;
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
			std::cout << "Elija una ciudad: "; std::cin >> nombre; it = mapaActual->ciudades.find(nombre);
			if (it != mapaActual->ciudades.end()) {
				std::cout << "\nInserte un precio de transito: "; std::cin >> precio;
				ciudad->insertarDestino(it->second, precio);
				it->second->insertarDestino(ciudad, precio);
			}
			else
				std::cout << "\nLa ciudad " << nombre << " no existe\n";
			break;
		case '2':
			std::cout << "Editando Destino...\Destinos Disponibles:\n"; ciudad->mostrarDestinos();
			std::cout << "Elija un destino: "; std::cin >> nombre; std::cout << "\nInserte un precio de transito: "; std::cin >> precio;
			if(ciudad->modificarDestino(nombre, precio))
				ciudad->destinos.find(nombre)->second->modificarDestino(ciudad->nombre, precio);
			break;
		case '3':
			std::cout << "Eliminando Destino...\Destinos Disponibles:\n"; ciudad->mostrarDestinos();
			std::cout << "Elija un destino: "; std::cin >> nombre;
			ciudad->destinos.find(nombre)->second->eliminarDestino(ciudad->nombre);
			ciudad->eliminarDestino(nombre);
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
		mapaActual = new travel::Mapa(nombre);
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
			MenuDeCiudad(mapaActual->ciudades.find(nombre)->second);
			break;
		case '2':
			std::cout << "Modificando Ciudad...\n";
			std::cout << std::endl << "Ciudades Disponibles"; mapaActual->mostrarCiudades(); std::cout << "Elija la Ciudad: "; std::cin >> nombre;
			MenuDeCiudad(mapaActual->ciudades.find(nombre)->second);
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
			break;
		case '7':
			std::cout << "Estableciendo inicio...\n";
			std::cout << std::endl << "Ciudades Disponibles:\n"; mapaActual->mostrarCiudades(); std::cout << "Elija la Ciudad: "; std::cin >> nombre;
			mapaActual->establecerInicio(nombre);
			break;
		case '8':
			std::cout << "Buscando...\n";
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
