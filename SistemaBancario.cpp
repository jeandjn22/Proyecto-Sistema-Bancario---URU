#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <limits>
#include <cctype> 
#include <vector>

using namespace std;

void menu();
void lista_clientes();
void buscar_clientes();
void buscar_cliente_num_cuenta();
void buscar_cliente_nombre();
void buscar_cliente_ci();
void suspender_cuenta();
void reactivar_cuenta();
void transferencia();
void deposito();
void retiro();
void agregar_cliente();
void eliminar_cliente();
void seleccionar_transaccion();


//Funcion para Buscar los clientes
void buscar_clientes(){
    int opcion_buscar_clientes;
    do
    {
        cout<<"--------OPCIONES PARA BUSCAR AL CLIENTE---------"<<endl;
        cout<<"1. Buscar cliente por Numero de Cuenta: "<<endl;
        cout<<"2. Buscar cliente por Nombre: "<<endl;
        cout<<"3. Buscar cliente por Numero de Identificacion: "<<endl;
        cout<<"0. Regresar "<<endl;
        cout<<"Selecciona una opcion: "<<endl;
        cin>>opcion_buscar_clientes;

        switch(opcion_buscar_clientes){
            case 1: buscar_cliente_num_cuenta(); break;
            case 2: buscar_cliente_nombre(); break;
            case 3: buscar_cliente_ci(); break;
            case 0: cout<<" "<<endl; break;
            default: cout<<"Opcion incorrecta"<<endl;
        }
    }while(opcion_buscar_clientes!=0);
}

//Funcion para Buscar el Cliente por su Numero de Cuenta
void buscar_cliente_num_cuenta() {
    ifstream archivo("clients.csv", ios::in);

    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string numero_cuenta_buscar;

        cout << "Ingresa el numero de cuenta del cliente que desea buscar: ";
        cin >> numero_cuenta_buscar;

        bool numero_cuenta_existe = false;

        // Lee la primera línea (cabecera) y la descarta
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance, ';');

            if (numero_cuenta_buscar.compare(account_number) == 0) {
                numero_cuenta_existe = true;
                cout << "----------------------------------------------------" << endl;
                cout << "ID: " << ci << endl;
                cout << "Cliente: " << client << endl;
                cout << "Numero de cuenta: " << account_number << endl;
                cout << "Tipo de cuenta: " << account_type << endl;
                cout << "Suspender: " << suspend << endl;
                cout<<"Saldo Disponible: "<<balance<<endl;
                cout << "----------------------------------------------------" << endl;
            }
        }

        archivo.close();

        if (!numero_cuenta_existe) {
            cout << "El cliente con numero de cuenta: " << numero_cuenta_buscar << " no existe." << endl << endl;
        }
    }
}


//Funcion para buscar al cliente por su nombre
void buscar_cliente_nombre() {
    ifstream archivo("clients.csv");
    if (!archivo) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string nombre_cliente_buscar;

        cout << "Ingrese el nombre completo del cliente a buscar: ";
        cin.ignore(); // Ignorar el salto de línea anterior
        getline(cin, nombre_cliente_buscar);

        bool nombre_encontrado = false;

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance, ';');
            

            if (nombre_cliente_buscar.compare(client)==0) { // Se compara el nombre ingresado con el nombre del cliente registrado para ver si existe
                nombre_encontrado = true;

                cout<<"----------------------------------------------------" << endl;
                cout<<"ID: " << ci << endl;
                cout<<"Cliente: " << client << endl;
                cout<<"Numero de cuenta: " << account_number << endl;
                cout<<"Tipo de cuenta: " << account_type << endl;
                cout<<"Estado de Cuenta: " << suspend << endl;
                cout<<"Saldo Disponible: "<< balance <<endl;
                cout << "----------------------------------------------------" << endl;
            }
        }
        archivo.close();
        if (!nombre_encontrado) { // Verificar si el nombre no se encontró
            cout << "El cliente con el nombre: " << nombre_cliente_buscar << " no existe." << endl << endl;
        }
    }
}

//Funcion para buscar al cliente por su numero de identificacion 
void buscar_cliente_ci() {
    ifstream archivo("clients.csv", ios::in);

    if (!archivo) {
        cout<<"No se puede abrir el archivo"<<endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string numero_cedula_buscar;

        cout<<"Ingresa el numero de identificacion del cliente que desea buscar: ";
        cin>>numero_cedula_buscar;

        bool numero_cedula_existe = false;

        // Lee la primera línea (cabecera) y la descarta
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance, ';');

            if (numero_cedula_buscar.compare(ci) == 0) { //Compara el numero de identificacion ingresado, con el numero de indetificacion registrado
                numero_cedula_existe = true;
                cout<<"----------------------------------------------------" << endl;
                cout<<"ID: " << ci << endl;
                cout<<"Cliente: " << client << endl;
                cout<<"Numero de cuenta: " << account_number << endl;
                cout<<"Tipo de cuenta: " << account_type << endl;
                cout<<"Estado de Cuenta: " << suspend << endl;
                cout<<"Saldo Disponible: "<<balance<<endl;
                cout << "----------------------------------------------------" << endl;
            }
        }

        archivo.close();

        if (!numero_cedula_existe) { //En caso de que el numero de identificacion no exista
            cout << "El cliente con numero de ID: " << numero_cedula_buscar << " no existe." << endl << endl;
        }
    }
}



void suspender_cuenta() {
    try {
        fstream archivo("clients.csv", ios::in | ios::out);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo");
        }

        string lineas, ci, client, account_number, account_type, suspend, balance;
        string num_ci_a_buscar;
        cout << "Ingrese el numero de identificacion del cliente a suspender: ";
        cin >> num_ci_a_buscar;
        cout << endl;

        bool clienteEncontrado = false;
        long posicion = archivo.tellg();

        while (getline(archivo, lineas)) {
            stringstream llave(lineas);
            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance);

            if (num_ci_a_buscar == ci && suspend == "false") {
                clienteEncontrado = true;

                cout << "ID: " << ci << endl;
                cout << "Cliente: " << client << endl;
                cout << "Numero de Cuenta: " << account_number << endl;
                cout << "Tipo de Cuenta: " << account_type << endl;
                cout << "Estado actual: " << suspend << endl;
                cout << "Saldo Disponible: " << balance << endl;
                cout << "Desea Suspender al Cliente? s/n : ";
                    
                char opcion;
                cin >> opcion;

                if (opcion == 's' || opcion == 'S') {
                    cout << endl;
                    cout << "Cliente Suspendido Correctamente!" << endl;

                    archivo.seekp(posicion);
                    archivo << ci << ';' << client << ';' << account_number << ';' << account_type << ';' << "true" << ';' << balance << '\n';

                    break;
                } else {
                    cout << endl;
                    cout << "Operacion Cancelada!!" << endl;
                    return;
                }
            }
            posicion = archivo.tellg();
        }

        archivo.close();

        if (!clienteEncontrado) {
            cout << "El cliente no fue encontrado. Por favor, revisa el numero de identificacion." << endl;
        }
    } catch (const exception& e) {
        cout << "Se ha producido un error: " << e.what() << endl;
    }
}

void reactivar_cuenta() {
    try {
        fstream archivo("clients.csv", ios::in | ios::out);
        if (!archivo) {
            throw runtime_error("Error al abrir el archivo");
        }

        string lineas, ci, client, account_number, account_type, suspend, balance;
        string num_ci_a_buscar;
        cout << "Ingrese el numero de identificacion del cliente a reactivar: ";
        cin >> num_ci_a_buscar;
        cout << endl;

        bool clienteEncontrado = false;
        long posicion = archivo.tellg();

        while (getline(archivo, lineas)) {
            stringstream llave(lineas);
            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance);

            if (num_ci_a_buscar == ci && suspend == "true") {
                clienteEncontrado = true;

                cout << "ID: " << ci << endl;
                cout << "Cliente: " << client << endl;
                cout << "Numero de Cuenta: " << account_number << endl;
                cout << "Tipo de Cuenta: " << account_type << endl;
                cout << "Estado actual: " << suspend << endl;
                cout << "Saldo Disponible: " << balance << endl;
                cout << "Desea Reactivar al Cliente? s/n : ";
                    
                char opcion;
                cin >> opcion;

                if (opcion == 's' || opcion == 'S') {
                    cout << endl;
                    cout << "Cliente Reactivado Correctamente!" << endl;

                    archivo.seekp(posicion);
                    archivo << ci << ';' << client << ';' << account_number << ';' << account_type << ';' << "false" << ';' << balance << '\n';

                    break;
                } else {
                    cout << endl;
                    cout << "Operacion Cancelada!!" << endl;
                    return;
                }
            }
            posicion = archivo.tellg();
        }

        archivo.close();

        if (!clienteEncontrado) {
            cout << "El cliente no fue encontrado. Por favor, revisa el numero de identificacion." << endl;
        }
    } catch (const exception& e) {
        cout << "Se ha producido un error: " << e.what() << endl;
    }
}


void transferencia() {
    fstream archivoClientes("clients.csv", ios::in);
    if (!archivoClientes) {
        cout << "Error al abrir el archivo de clientes" << endl;
        return;
    }

    vector<string> lineasClientes;
    string linea;
    while (getline(archivoClientes, linea)) {
        lineasClientes.push_back(linea);
    }
    archivoClientes.close();

    string cuentaOrigen, cuentaDestino;
    float montoTransferencia;
    cout << "Ingrese el numero de cuenta de origen: ";
    cin >> cuentaOrigen;
    cout << "Ingrese el numero de cuenta de destino: ";
    cin >> cuentaDestino;
    cout << "Ingrese el monto a transferir: ";
    cin >> montoTransferencia;

    bool cuentaOrigenEncontrada = false, cuentaDestinoEncontrada = false;
    float saldoOrigen, saldoDestino;
    for (auto& linea : lineasClientes) {
        stringstream ss(linea);
        string ci, nombre, numeroCuenta, tipoCuenta, suspendida, balanceStr;
        getline(ss, ci, ';');
        getline(ss, nombre, ';');
        getline(ss, numeroCuenta, ';');
        getline(ss, tipoCuenta, ';');
        getline(ss, suspendida, ';');
        getline(ss, balanceStr, ';');

        if (numeroCuenta == cuentaOrigen && suspendida == "false") {
            cuentaOrigenEncontrada = true;
            saldoOrigen = stof(balanceStr);
            if (montoTransferencia > saldoOrigen) {
                cout << "Fondos insuficientes para realizar la transferencia." << endl;
                return;
            }
        }

        if (numeroCuenta == cuentaDestino && suspendida == "false") {
            cuentaDestinoEncontrada = true;
            saldoDestino = stof(balanceStr);
        }
    }

    if (!cuentaOrigenEncontrada || !cuentaDestinoEncontrada) {
        cout << "Cuenta de origen o destino no encontrada o suspendida." << endl;
        return;
    }

    if(cuentaOrigen == cuentaDestino){
        cout<<"No se puede transferir a su mismo numero de cuenta."<<endl;
        return;
    }

    // Realizar la transferencia y actualizar los saldos
    for (auto& linea : lineasClientes) {
        stringstream ss(linea);
        string ci, nombre, numeroCuenta, tipoCuenta, suspendida, balanceStr;
        getline(ss, ci, ';');
        getline(ss, nombre, ';');
        getline(ss, numeroCuenta, ';');
        getline(ss, tipoCuenta, ';');
        getline(ss, suspendida, ';');
        getline(ss, balanceStr, ';');

        if (numeroCuenta == cuentaOrigen) {
            saldoOrigen -= montoTransferencia;
            stringstream balanceActualizado;
            balanceActualizado << saldoOrigen;
            linea = ci + ";" + nombre + ";" + numeroCuenta + ";" + tipoCuenta + ";" + suspendida + ";" + balanceActualizado.str();
        }

        if (numeroCuenta == cuentaDestino) {
            saldoDestino += montoTransferencia;
            stringstream balanceActualizado;
            balanceActualizado << saldoDestino;
            linea = ci + ";" + nombre + ";" + numeroCuenta + ";" + tipoCuenta + ";" + suspendida + ";" + balanceActualizado.str();
        }
    }

    // Actualizar archivo de clientes
    archivoClientes.open("clients.csv", ios::out | ios::trunc);
    for (const auto& lineaActualizada : lineasClientes) {
        archivoClientes << lineaActualizada << "\n";
    }
    archivoClientes.close();

    // Registrar la operación en el archivo de operaciones
    fstream archivoOperaciones("operaciones.csv", ios::app);
    if (!archivoOperaciones) {
        cout << "Error al abrir el archivo de operaciones" << endl;
        return;
    }
    archivoOperaciones << "Transferencia;" << cuentaOrigen << ";" << cuentaDestino << ";" << montoTransferencia << "\n";
    archivoOperaciones.close();

    cout << "Transferencia realizada exitosamente." << endl;
}


void deposito() {
    fstream archivo("clients.csv", ios::in);
    if (!archivo) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    vector<string> lineas;
    string linea;
    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }
    archivo.close();

    string cuentaDeposito;
    float montoDeposito;
    cout << "Ingrese el numero de cuenta para el deposito: ";
    cin >> cuentaDeposito;
    cout << "Ingrese el monto a depositar: ";
    cin >> montoDeposito;

    if (montoDeposito <= 0) {
        cout << "El monto a depositar debe ser mayor a 0." << endl;
        return;
    }

    bool cuentaEncontrada = false;
    for (auto& linea : lineas) {
        stringstream ss(linea);
        string ci, nombre, numeroCuenta, tipoCuenta, suspendida, balanceStr;
        getline(ss, ci, ';');
        getline(ss, nombre, ';');
        getline(ss, numeroCuenta, ';');
        getline(ss, tipoCuenta, ';');
        getline(ss, suspendida, ';');
        getline(ss, balanceStr, ';');

        if (numeroCuenta == cuentaDeposito && suspendida == "false") {
            cuentaEncontrada = true;
            float balance = stof(balanceStr);

            balance += montoDeposito;
            cout << "Deposito realizado. Titular: " << nombre << endl;
            stringstream balanceActualizado;
            balanceActualizado << balance;
            linea = ci + ";" + nombre + ";" + numeroCuenta + ";" + tipoCuenta + ";" + suspendida + ";" + balanceActualizado.str();
            break;
        }
    }

    if (!cuentaEncontrada) {
        cout << "Cuenta no encontrada o suspendida." << endl;
    } else {
        archivo.open("clients.csv", ios::out | ios::trunc);
        for (const auto& lineaActualizada : lineas) {
            archivo << lineaActualizada << "\n";
        }
        archivo.close();
    }
}


void retiro() {
    fstream archivo("clients.csv", ios::in);
    if (!archivo) {
        cout << "Error al abrir el archivo" << endl;
        return;
    }

    vector<string> lineas;
    string linea;
    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }
    archivo.close();

    string cuentaRetiro;
    float montoRetiro;
    cout << "Ingrese el numero de cuenta para el retiro: ";
    cin >> cuentaRetiro;
    cout << "Ingrese el monto a retirar: ";
    cin >> montoRetiro;

    if (montoRetiro <= 0) {
        cout << "El monto a retirar debe ser mayor a 0." << endl;
        return;
    }

    bool cuentaEncontrada = false;
    for (auto& linea : lineas) {
        stringstream ss(linea);
        string ci, nombre, numeroCuenta, tipoCuenta, suspendida, balanceStr;
        getline(ss, ci, ';');
        getline(ss, nombre, ';');
        getline(ss, numeroCuenta, ';');
        getline(ss, tipoCuenta, ';');
        getline(ss, suspendida, ';');
        getline(ss, balanceStr, ';');

        if (numeroCuenta == cuentaRetiro && suspendida == "false") {
            cuentaEncontrada = true;
            float balance = stof(balanceStr);
            if (montoRetiro > balance) {
                cout << "Fondos insuficientes para realizar el retiro." << endl;
                return;
            }

            balance -= montoRetiro;
            cout << "Retiro realizado. Titular: " << nombre << endl;
            stringstream balanceActualizado;
            balanceActualizado << balance;
            linea = ci + ";" + nombre + ";" + numeroCuenta + ";" + tipoCuenta + ";" + suspendida + ";" + balanceActualizado.str();
            break;
        }
    }

    if (!cuentaEncontrada) {
        cout << "Cuenta no encontrada o suspendida." << endl;
    } else {
        archivo.open("clients.csv", ios::out | ios::trunc);
        for (const auto& lineaActualizada : lineas) {
            archivo << lineaActualizada << "\n";
        }
        archivo.close();
    }
}



void seleccionar_transaccion() {
    int opcion;
    cout << "Seleccione la transacción que desea realizar:" << endl;
    cout << "1. Depositar" << endl;
    cout << "2. Retirar" << endl;
    cin >> opcion;

    switch(opcion) {
        case 1:
            deposito();
            break;
        case 2:
            retiro();
            break;
        default:
            cout << "Opción no válida" << endl;
            break;
    }
}






bool existe_cliente(const string& ci, const string& client, const string& account_number, ifstream& archivo) {
    string linea;
    while (getline(archivo, linea)) {
        stringstream llave(linea);
        string current_ci, current_client, current_account_number;
        getline(llave, current_ci, ';');
        getline(llave, current_client, ';');
        getline(llave, current_account_number, ';');
        if (!ci.empty() && ci == current_ci) {
            return true; // El cliente ya existe con el mismo ID
        }
        if (!client.empty() && client.compare(current_client) == 0) {
            return true; // El cliente ya existe con el mismo nombre
        }
        if (!account_number.empty() && account_number.compare(current_account_number) == 0) {
            return true; // El cliente ya existe con ese numero de cuenta
        }
    }
    return false; // El cliente no existe
}

//Funcion para que solo se acepten numeros en el ID
bool contiene_letras(const string& str) {
    for (char c : str) {
        if (isalpha(c)) {
            return true;
        }
    }
    return false;
}


void agregar_cliente() {
    ifstream lectura("clients.csv", ios::in);
    ofstream escritura("clients.csv", ios::app); // Abre el archivo en modo append

    if (!lectura || !escritura) {
        cout << "No se puede abrir el archivo" << endl;
    } else {
        string ci, name, account_number, account_type, suspend, balance;

        cout << "Ingrese su ID para registrarse: " << endl;
        cin.ignore();
        getline(cin, ci);

        // Verificar si el ID contiene solo números
        while (!ci.empty() && ci.find_first_not_of("0123456789") != string::npos) {
            cout << "El ID debe contener solo dígitos. Por favor, ingrese un ID válido:" << endl;
            getline(cin, ci);
        }

        if (existe_cliente(ci, "", "", lectura)) {
            cout << "Ya existe un cliente con ese ID. Por favor ingrese uno valido." << endl;
            return;
        }

        cout << "Ingrese su nombre completo: " << endl;
        getline(cin, name);

        if (existe_cliente("", name, "", lectura)) {
            cout << "Ya existe un cliente con ese nombre. Por favor ingrese uno valido." << endl;
            return;
        }

        cout << "Ingrese el tipo de cuenta (Cuenta Debito o Cuenta Credito): " << endl;
        cout << "Coloque 'current' o 'debit': " << endl;
        getline(cin, account_type);

        // Verificar si la entrada del usuario es válida
        while (account_type != "current" && account_type != "debit") {
            cout << "Tipo de cuenta no valido. Por favor, ingrese 'credit' o 'debit':" << endl;
            getline(cin, account_type);
        }

        if (existe_cliente("", "", account_number, lectura)) {
            cout << "Ya existe un cliente con ese numero de cuenta. Por favor ingrese uno valido." << endl;
            return;
        }

        cout<<"Pasos para crear su numero de cuenta: "<<endl;
        cout<<"1. Coloque principalmente 000."<<endl;
        cout<<"2. Seguido de 000 coloque su ID."<<endl;
        cout << "Ingrese su numero de cuenta: " << endl;
        getline(cin, account_number);

        while (!account_number.empty() && account_number.find_first_not_of("0123456789") != string::npos) {
            cout << "El numero de cuenta debe contener solo dígitos. Por favor, ingrese un valor valido:" << endl;
            getline(cin, account_number);
        }

        if (existe_cliente("", "", account_number, lectura)) {
            cout << "Ya existe un cliente con ese numero de cuenta. Por favor ingrese uno valido." << endl;
            return;
        }

        suspend = "false";
        balance = "500$";

        escritura << ci << ';' << name << ';' << account_number << ';' << account_type << ';' << suspend << ';'
                  << balance << '\n';

        cout << "El cliente ha sido registrado exitosamente." << endl;
    }

    lectura.close();
    escritura.close();
}


void eliminar_cliente(){

    ifstream archivo("clients.csv", ios::in);
    if(!archivo){
        cout<<"Error al abrir el archivo."<<endl<<endl;
    }else{
        vector<string> registros_no_eliminar;
        string linea;
        string ci, client, account_number, account_type, suspend, balance;
        string id_cliente_eliminar;
        cout<<"Ingrese el numero de ID del cliente a eliminar: "<<endl;
        cin>>id_cliente_eliminar;
        bool existe = false;

        while(getline(archivo, linea)){
            stringstream llave(linea);

            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance, ';');

            if(id_cliente_eliminar.compare(ci) == 0) existe = true;
            else registros_no_eliminar.push_back(linea);
        }//fin del while

        archivo.close();

        if(existe){//if(existe == true)
            ofstream nuevo("clients.csv");
            for(int i = 0; i < int(registros_no_eliminar.size()); i++){
                 nuevo<<registros_no_eliminar[i]<<endl;
            }
            nuevo.close();
            cout<<"Se elimino el cliente correctamente"<<endl<<endl;
        }else{
            cout<<"El cliente con numero de ID "<<id_cliente_eliminar<<
                  " no existe en el archivo"<<endl<<endl;
        }
    }

}


void lista_clientes() {
    ifstream archivo("clients.csv", ios::in);

    if (!archivo) {
        cout<<"No se puede abrir el archivo"<<endl;
    } else {
        string linea;
        string ci, client, account_number, account_type, suspend, balance;

        // Lee la primera línea (cabecera) y la descarta
        getline(archivo, linea);

        while (getline(archivo, linea)) {
            stringstream llave(linea);

            getline(llave, ci, ';');
            getline(llave, client, ';');
            getline(llave, account_number, ';');
            getline(llave, account_type, ';');
            getline(llave, suspend, ';');
            getline(llave, balance, ';');


            cout << "----------------------------------------------------" << endl;
            cout << "ID: " << ci << endl;
            cout << "Cliente: " << client << endl;
            cout << "Numero de cuenta: " << account_number << endl;
            cout << "Tipo de cuenta: " << account_type << endl;
            cout << "Estado de Cuenta: " << suspend << endl;
            cout<<"Saldo Disponible: "<<balance<<endl;
            cout << "----------------------------------------------------" << endl;
        }

        archivo.close();
    }
}



void menu(){
    int opcion;
    do
    {
        cout<<"------------------MENU-------------------"<<endl;
        cout<<"1. Visualizar Lista De Clientes "<<endl;
        cout<<"2. Buscar Clientes "<<endl;
        cout<<"3. Suspender cuenta a cliente "<<endl;
        cout<<"4. Realizar Transferencia a Cliente "<<endl;
        cout<<"5. Deposito o Retiro" <<endl;
        cout<<"6. Registrarse como cliente. "<<endl;
        cout<<"7. Eliminar informacion de un cliente."<<endl;
        cout<<"8. Reactivar cuenta a cliente."<<endl;
        cout<<"0. Salir"<<endl;
        cout<<"Selecciona una opcion: ";
        cin>>opcion;

        while (cin.fail() || opcion < 0) {
            cin.clear(); // Limpiar el estado de error
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Descartar el resto de la línea
            cout << "Opcion Invalida. Selecciona una correcta: ";
            cin >> opcion;
        }

        switch(opcion){
            case 1: lista_clientes(); break;
            case 2: buscar_clientes(); break;
            case 3: suspender_cuenta(); break;
            case 4: transferencia(); break;
            case 5: seleccionar_transaccion(); break;
            case 6: agregar_cliente(); break;
            case 7: eliminar_cliente(); break;
            case 8: reactivar_cuenta(); break;
            case 0: cout<<"GRACIAS POR USAR EL PROGRAMA!"<<endl; break;
            default: cout<<"Opcion invalida. Selecciona una correcta: "<<endl;
        }
    }while(opcion!=0);
    
}

int main() {
    
    menu();
    return 0;
}



