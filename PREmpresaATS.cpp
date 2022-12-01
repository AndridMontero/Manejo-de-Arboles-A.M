#include <iostream>
using namespace std;

class Nodo {
    public:
        int valor;
        Nodo *izquierdo = nullptr;
        Nodo *derecho = nullptr;
        Nodo *padre = nullptr;
};

class Arbol {
    public:
        Nodo *raiz = nullptr;
        int cantidad = 0;

        bool insertar(int valor) {
            Nodo *nuevo = new Nodo();
            nuevo->valor = valor;

            if(raiz == nullptr) {
                raiz = nuevo;
            } else {
                Nodo *auxiliar = raiz;
                Nodo *padre;

                while(true) {
                    padre = auxiliar;

                    if(valor < auxiliar->valor) {
                        auxiliar = auxiliar->izquierdo;

                        if(auxiliar == nullptr) {
                            padre->izquierdo = nuevo;
                            nuevo->padre = padre;
                            return true;
                        }
                    } else if(valor >= auxiliar->valor) {
                        auxiliar = auxiliar->derecho;

                        if(auxiliar == nullptr) {
                            padre->derecho = nuevo;
                            nuevo->padre = padre;
                            return true;
                        }
                    }
                }
            }
            return false;
        }

        void preOrden(Nodo *auxiliar) {
            if(auxiliar != nullptr) {
                cout << auxiliar->valor << " ";
                preOrden(auxiliar->izquierdo);
                preOrden(auxiliar->derecho);
            }
        }

        void inOrden(Nodo *auxiliar) {
            if(auxiliar != nullptr) {
                inOrden(auxiliar->izquierdo);
                cout << auxiliar->valor << " ";
                inOrden(auxiliar->derecho);
            }
        }

        void postOrden(Nodo *auxiliar) {
            if(auxiliar != nullptr) {
                postOrden(auxiliar->izquierdo);
                postOrden(auxiliar->derecho);
                cout << auxiliar->valor << " ";
            }
        }

        Nodo *buscar(int valor, Nodo *auxiliar) {
            if(auxiliar != nullptr) {
                if(auxiliar->valor == valor) {
                    return auxiliar;
                }

                if(valor < auxiliar->valor) {
                    return buscar(valor, auxiliar->izquierdo);
                } else {
                    return buscar(valor, auxiliar->derecho);
                }
            } else {
                return nullptr;
            }
        }

        int contar(Nodo *auxiliar) {
            if(auxiliar != nullptr) {
                contar(auxiliar->izquierdo);
                contar(auxiliar->derecho);
                cantidad++;
            }

            return cantidad;
        }

        void verArbol(Nodo *auxiliar, int n) {
            if(auxiliar == nullptr) {
                return;
            }

            verArbol(auxiliar->derecho, n + 1);

            for(int i = 0; i < n; i++) {
                cout << "   ";
            }

            cout << auxiliar->valor << "\n";

            verArbol(auxiliar->izquierdo, n + 1);
        }

        bool eliminar(int valor) {
            Nodo *auxiliar = raiz;
            Nodo *padre = raiz;
            bool esIzquierdo = true;

            while(auxiliar->valor != valor) {
                padre = auxiliar;

                if(valor < auxiliar->valor) {
                    esIzquierdo = true;
                    auxiliar = auxiliar->izquierdo;
                } else {
                    esIzquierdo = false;
                    auxiliar = auxiliar->derecho;
                }

                if(auxiliar == nullptr) {
                    return false;
                }
            }

            if(auxiliar->izquierdo == nullptr && auxiliar->derecho == nullptr) {
                if(auxiliar == raiz) {
                    raiz = nullptr;
                } else if(esIzquierdo) {
                    padre->izquierdo = nullptr;
                } else {
                    padre->derecho = nullptr;
                }
            } else if(auxiliar->derecho == nullptr) {
                if(auxiliar == raiz) {
                    raiz = auxiliar->izquierdo;
                } else if(esIzquierdo) {
                    padre->izquierdo = auxiliar->izquierdo;
                } else {
                    padre->derecho = auxiliar->izquierdo;
                }
            } else if(auxiliar->izquierdo == nullptr) {
                if(auxiliar == raiz) {
                    raiz = auxiliar->derecho;
                } else if(esIzquierdo) {
                    padre->izquierdo = auxiliar->derecho;
                } else {
                    padre->derecho = auxiliar->derecho;
                }
            } else {
                Nodo *reemplazo = obtenerNodoReemplazo(auxiliar);

                if(auxiliar == raiz) {
                    raiz = reemplazo;
                } else if(esIzquierdo) {
                    padre->izquierdo = reemplazo;
                } else {
                    padre->derecho = reemplazo;
                }

                reemplazo->izquierdo = auxiliar->izquierdo;
            }
            return true;
        }

        Nodo *obtenerNodoReemplazo(Nodo *nodoReemplazo) {
            Nodo *reemplazarPadre = nodoReemplazo;
            Nodo *reemplazo = nodoReemplazo;
            Nodo *auxiliar = nodoReemplazo->derecho;

            while(auxiliar != nullptr) {
                reemplazarPadre = reemplazo;
                reemplazo = auxiliar;
                auxiliar = auxiliar->izquierdo;
            }

            if(reemplazo != nodoReemplazo->derecho) {
                reemplazarPadre->izquierdo = reemplazo->derecho;
                reemplazo->derecho = nodoReemplazo->derecho;
            }
            return reemplazo;
        }
};

int main() {
    Arbol arbol = Arbol();
    int opcion = 0;
    int valor = 0;

    while(opcion != 9) {
        cout << "\n\n\tEmpresa ATS\n\n";
        cout << "1. Insertar un Nodo\n";
        cout << "2. Mostrar Arbol\n";
        cout << "3. Cantidad de Nodos\n";
        cout << "4. Buscar un Elemento\n";
        cout << "5. Mostrar Recorrido PreOrden\n";
        cout << "6. Mostrar Recorrido InOrden\n";
        cout << "7. Mostrar Recorrido PostOrden\n";
        cout << "8. Eliminar un Elemento\n";
        cout << "9. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch(opcion) {
            case 1:
                cout << "\nValor del Nodo: ";
                cin >> valor;
                arbol.insertar(valor);
				cout<<"\n";
				system("pause");
				system("cls");
                break;
            case 2:
                arbol.verArbol(arbol.raiz, 0);
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 3:
                arbol.contar(arbol.raiz);
                cout << "\nCantidad de Nodos: " << arbol.cantidad;
                arbol.cantidad = 0;
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 4:
                cout << "\nValor a Buscar: ";
                cin >> valor;

                if(arbol.buscar(valor, arbol.raiz) != nullptr) {
                    cout << "\nEl valor " << valor << " existe en el Arbol";
                } else {
                    cout << "\nEl valor " << valor << " no existe en el Arbol";
                }
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 5:
                cout << "\nRecorrido PreOrden: ";
                arbol.preOrden(arbol.raiz);
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 6:
                cout << "\nRecorrido InOrden: ";
                arbol.inOrden(arbol.raiz);
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 7:
                cout << "\nRecorrido PostOrden: ";
                arbol.postOrden(arbol.raiz);
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 8:
                cout << "\nValor a Eliminar: ";
                cin >> valor;

                if(arbol.eliminar(valor)) {
                    cout << "\nEl valor ha sido removido del Arbol";
                } else {
                    cout << "\nEl valor no existe en el Arbol";
                }
				cout<<"\n \n";
				system("pause");
				system("cls");
                break;
            case 9:
				system("pause");
				system("cls");
                break;
            default:
                cout << "\nOpcion no valida";
                break;
        }
    }	
}
