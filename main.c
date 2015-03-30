#include <stdio.h>
#include <stdlib.h>


typedef struct Cliente
{
    char nombre[50];
    int asiento;
    int tipoDeAsiento;
};

typedef struct
{
    struct Cliente clientes[30];
    int ultimocliente;
    char asientos[2][15];
    char Disponibles[2][15];
    int primeraClase;
    int cantidadDisponiblePrimeraClase;
    int cantidadDisponibleClaseEconomica;
    int destino;
    int inicio_primeraclase;
    int final_primeraclase;
    float precio_Economico;
    float precio_PrimeraClase;
} Avion;

Avion aviones[3];
float total= 0.0;
int AsientosPrimeraClase(int codigo_Avion, int limite_superior, int limite_inferior);
void mantenimientoDeOperaciones();
void InfoDeAerolinea();
void modificarPrecios();
void InfoDeAvion(int avion);
void ventaDeBoletos();
int tiposDeAsiento();
int checkearAsientos(int vuelo, int asiento, int tipo);
int comprarAsiento(int vuelo, int asiento, int tipo, struct Cliente cliente);
void generarFactura(int vuelo, struct Cliente cliente);
int cancelarBoleto(int vuelo, char nombre[50], int asiento);
void reportes();
void mostrarPasajeros(int vuelo);

int main()
{
    int i;
    for( i =0; i< 3 ; i++){
    aviones[i].destino = i+1;
    aviones[i].primeraClase=0;
    aviones[i].inicio_primeraclase= 0;
    aviones[i].final_primeraclase = 0;
    aviones[i].precio_Economico = 0.0;
    aviones[i].precio_PrimeraClase = 0.0;
    aviones[i].cantidadDisponibleClaseEconomica = 30;
    aviones[i].cantidadDisponiblePrimeraClase=0;
    aviones[i].ultimocliente = 0;
    int j;
    int z;
    for( j= 0; j<2;j++)
        for( z= 0; z<15 ;z++)
            aviones[i].asientos[j][z] = 'E';
   j=0;
   z=0;
    for( j= 0; j<2;j++)
        for( z= 0; z<15 ;z++)
            aviones[i].Disponibles[j][z] = 'D';
    }
    int destino = -1;
    char nombre[50];
    int numA = -1;
    printf("-----Menu-----\n");
          int salir = 0;
          int opcion = 0;
          while(salir!=1){
              printf("1. Mantenimiento de Operacion \n");
              printf("2. Venta de Boletos \n");
              printf("3. Cancelación de Boletos \n");
              printf("4. Reportes \n");
              printf("5. Salir del sistema \n");
              printf("Eleccion: ");
              scanf("%d",&opcion);
              system("cls");
              switch (opcion) {
              case 1:
                    mantenimientoDeOperaciones();
                  break;
              case 2:
                    ventaDeBoletos();
                  break;
              case 3:
                    printf("Ingrese el codigo del Destino: ");
                    scanf("%i",&destino);
                    printf("\n");
                    printf("Ingrese su nombre: ");
                    scanf("%s",nombre);
                    printf("Ingrese el numero de asiento: ");
                    scanf("%i",&numA);
                    cancelarBoleto(destino-1,nombre,numA);
                  break;
              case 4:
                    reportes();
                  break;
              case 5:
                  salir = 1;
                  printf("--SALIENDO DEL SISTEMA--");
                  exit(0);
                  break;
              default:
                  break;
              }
          }

    return 0;
}



void InfoDeAerolinea(){

}
int AsientosPrimeraClase(int codigo_Avion,int limite_superior, int limite_inferior){
   if(codigo_Avion<0 || codigo_Avion >=3 || limite_inferior >=30 || limite_inferior<0 || limite_superior >=30 || limite_superior<0)
       return -1;
    int direcciony = 0;
    aviones[codigo_Avion].inicio_primeraclase= limite_superior;
    aviones[codigo_Avion].final_primeraclase = limite_inferior;
    aviones[codigo_Avion].cantidadDisponiblePrimeraClase = limite_inferior;
    aviones[codigo_Avion].cantidadDisponibleClaseEconomica-= aviones[codigo_Avion].cantidadDisponiblePrimeraClase;
    int direccionx = 0;
    int aumento = 0;
    while(limite_superior<=limite_inferior){
              aviones[codigo_Avion].asientos[direcciony][direccionx] = 'P';
              if(direcciony==0)
                  direcciony = 1;
              else
                  direcciony = 0;
              aumento++;
              if(aumento%2==0)
                 direccionx+=1;
              limite_superior+=1;
    }

}
void InfoDeAvion(int avion){
    printf("-----Informacion De Avion-------\n");
    printf("Destino:");
    if(aviones[avion].destino==1)
    printf("Tegucigalpa\n");
    else if(aviones[avion].destino==2)
     printf("El Salvador\n");
    else
        printf("San Jose\n");
    if(aviones[avion].primeraClase==1)
    printf("Hay primera clase\n");
    else
         printf("No hay primera clase\n");
    printf("Precio Clase Economica: " );
    printf("%f",aviones[avion].precio_Economico);
    printf("\n");
    if(aviones[avion].primeraClase==1){
    printf("Precio Primera Clase: ");
    printf("%f",aviones[avion].precio_PrimeraClase);
     printf("\n");
   }
    printf("---------------------------------------\n");
    printf("Avion\n");
    printf("---------------------------------------\n");
    int i;
    int j;
    for( i = 0; i<2; i++){
        for(j= 0; j<15; j++){
           printf("%c",aviones[avion].asientos[i][j]);
        }
        printf("\n");
        printf("\n");
    }

    printf("----------------------------------------\n");
}
int tiposDeAsiento(){
    char decision  = 'n';
    int vuelo = -1;
    int finali = -1;
    printf("Desea Primera Clase en este avion? (S/N) \n");
    scanf("%s",&decision);
    system("cls");
    if(decision == 's'){
        printf("Escriba el codigo del vuelo \n");
                scanf("%d",&vuelo);
                vuelo-=1;
                InfoDeAvion(vuelo);
                aviones[vuelo].primeraClase = 1;
                printf("Escriba donde Finaliza primera clase \n");
                scanf("%d",&finali);
                AsientosPrimeraClase(vuelo,1,finali);
 }
    else
        return -1;
    InfoDeAvion(vuelo);
    system("pause");
    return 0;
}
void modificarPrecios(){
  int vuelo = -1;
  int clase =-1;
  float nuevoPrecio = 0.0;
  printf("Ingrese el vuelo a modificar\n");
    scanf("%i",&vuelo);
    vuelo-=1;
    system("cls");
    printf("1. Modificar Clase Economica \n");
    printf("2. Modificar Primera Clase \n");
    scanf("%i",&clase);
    system("cls");
    printf("Ingrese nuevo Precio: ");
    scanf("%f",&nuevoPrecio);
    switch (clase) {
    case 1:
        aviones[vuelo].precio_Economico = nuevoPrecio;
        break;
    case 2:
        aviones[vuelo].precio_PrimeraClase = nuevoPrecio;
        break;
    default:
        break;
    }
    InfoDeAvion(vuelo);
    system("pause");
}

void mantenimientoDeOperaciones(){
    int salir = 0;
    int opcion = 0;
    printf("Mantenimiento de Operaciones\n");
    while(salir!=1){
        printf("1. Tipos de Asiento \n");
        printf("2. Precios \n");
        printf("3. Salir\n" );
        scanf("%i",&opcion);
        system("cls");
        switch(opcion){
        case 1:
           tiposDeAsiento();
                break;
        case 2:
            modificarPrecios();
            break;
        case 3:
           salir = 1;
           break;
        default:
            break;
        }
    }
}
int checkearAsientos(int vuelo, int asiento,int tipo){
    int direcciony=0;
    int encontre = 0;
    char tipodeAsiento  = ' ';
    int direccionx = 0;
    if(asiento%2 == 0)
        direcciony = 1;
    if(direcciony==1)
        direccionx= (asiento/2)-1;
    else
            direccionx = (asiento-1)/2;

    if(tipo == 1)
        tipodeAsiento = 'E';
    else
        tipodeAsiento= 'P';
    if(aviones[vuelo].asientos[direcciony][direccionx] == tipodeAsiento){
         if(aviones[vuelo].Disponibles[direcciony][direccionx] == 'D')
        return 0;
    }else{
         printf("El Asiento no es del tipo que busca\n");
            system("pause");
            return -1;
         }
    int aumento = 0;
    while(direccionx<15){
            if(aviones[vuelo].Disponibles[direcciony][direccionx] == 'D' && aviones[vuelo].asientos[direcciony][direccionx] == tipodeAsiento){
                break;
                encontre= 1;
            }
             if(direcciony==0)
                direcciony = 1;
            else
                direcciony = 0;
            aumento++;
            if(aumento%2==0)
               direccionx+=1;
        }
    if(direccionx == 15){
        direccionx = 0;
        direcciony = 0;
        aumento =0;
        while(direccionx<15){
                if(aviones[vuelo].Disponibles[direcciony][direccionx] == 'D' && aviones[vuelo].asientos[direcciony][direccionx] == tipodeAsiento){
                   encontre = 1;
                    break;
                }
                if(direcciony==0)
                    direcciony = 1;
                else
                    direcciony = 0;
                aumento++;
                if(aumento%2==0)
                   direccionx+=1;
            }
    }
if(encontre == 1){
    if(direcciony == 0)
    return (direccionx*2)+1;
    else
        return(direccionx*2)+2;
}
return -10;
}
void generarFactura(int vuelo, struct Cliente cliente){
    float costo;
    printf("-------Factura--------\n");
    printf("Nombre: ");
     printf("%s",cliente.nombre);
      printf("\n");
    printf("Vuelo hacia: ");
    if(aviones[vuelo].destino == 1)
        printf("Tegucigalpa\n");
    else  if(aviones[vuelo].destino == 2)
             printf("El Salvador\n");
    else
        printf("San Jose\n");
    printf("Tipo de Asiento: ");
    if(cliente.tipoDeAsiento == 1){
         printf("Economico\n");
         costo = aviones[vuelo].precio_Economico;
    }else{
         printf("Primera Clase\n");
         costo = aviones[vuelo].precio_PrimeraClase;
    }
    printf("Numero de Asiento: ");
    printf("%i",cliente.asiento);
     printf("\n");
     printf("Costo: ");
     printf("%f",costo);
      printf("\n");
      aviones[vuelo].clientes[aviones[vuelo].ultimocliente] = cliente;
      aviones[vuelo].ultimocliente++;
      printf("-------------------------\n");
        system("pause");
        total+=costo;
}

void ventaDeBoletos(){
    char nombre[50];
    int vuelo = -1;
    int comprarotro= -1;
    struct Cliente cliente;
    printf("---------VENTA----------\n");
    printf("Ingrese el Codigo del Vuelo\n");
    scanf("%d",&vuelo);
    vuelo-=1;
    if(vuelo<0 || vuelo>2){
        printf("Codigo no Existe");
   }
        InfoDeAvion(vuelo);
    if(aviones[vuelo].precio_Economico <=0 && aviones[vuelo].precio_PrimeraClase<=0)
        return;
    printf("1. Clase Economica\n");
    printf("2. Primera Clase\n");
    scanf("%d",&cliente.tipoDeAsiento);
    if(cliente.tipoDeAsiento==1){

        if(aviones[vuelo].cantidadDisponibleClaseEconomica==0){
            printf("NO HAY ASIENTOS DISPONIBLES, PROXIMO VUELO EN 3HRS \n");
            return;
        }
   } else{
            if(aviones[vuelo].cantidadDisponiblePrimeraClase==0){
                printf("NO HAY ASIENTOS DISPONIBLES, PROXIMO VUELO EN 3HRS\n");
                return;
            }
    }
    printf("Ingrese Nombre Cliente:\n");
    scanf("%s",nombre);
    strcpy(cliente.nombre,nombre);
    printf("---------------------------------------\n");
    printf("Avion\n");
    printf("---------------------------------------\n");
    int i;
    int j;
    for( i = 0; i<2; i++){
        for( j= 0; j<15; j++){
           printf("%c",aviones[vuelo].Disponibles[i][j]);
        }
        printf("\n");
        printf("\n");
    }
    int comprar= 0;
    printf("Ingrese el numero de Asiento: ");
    scanf("%d",&cliente.asiento);
    int disp = checkearAsientos(vuelo,cliente.asiento,cliente.tipoDeAsiento);
    if(disp==0){
            comprarAsiento(vuelo,cliente.asiento,cliente.tipoDeAsiento,cliente);
    }else if(disp!=-1){
        printf("Asiento Ocupado, el siguiente disponible es: ");
        printf("%i",disp);
        printf("\n");
        printf("1.Comprarlo\n");
        printf("2.Salir\n");
        scanf("%i",&comprar);
        if(comprar==1)
            comprarAsiento(vuelo,disp,cliente.tipoDeAsiento,cliente);
        else
            return;
    }
    if(disp==-1)
        return;
    if(disp==-10){
        int acual = 0;
        int disponible = -1;
        if(cliente.tipoDeAsiento == 1){
        printf("No hay asientos de clase economica" );
        acual = 2;
      } else if(cliente.tipoDeAsiento == 2){
        printf("No hay asientos de primera clase " );
        acual = 1;
        }
        printf("1. Comprar de otra clase");
        printf("2. Salir");
        scanf("%i",&comprarotro);
        if(comprarotro == 1){
            cliente.tipoDeAsiento = acual;
            disponible = checkearAsientos(vuelo,1,cliente.tipoDeAsiento);
            comprarAsiento(vuelo,disponible,cliente.tipoDeAsiento,cliente);
        }

    }
    printf("---------------------------------------\n");
    printf("Avion\n");
    printf("---------------------------------------\n");
     i=0;
     j=0;
    for( i = 0; i<2; i++){
        for( j= 0; j<15; j++){
           printf("%c",aviones[vuelo].Disponibles[i][j]);
        }
        printf("\n");
        printf("\n");
    }
    system("pause");

}

int comprarAsiento(int vuelo, int asiento, int tipo, struct Cliente cliente){
    int direcciony=0;
    int direccionx = 0;
    if(asiento%2 == 0)
        direcciony = 1;
    if(direcciony==1)
        direccionx= (asiento/2)-1;
    else
        direccionx = (asiento-1)/2;
    aviones[vuelo].Disponibles[direcciony][direccionx] = 'X';
    if(tipo==1)
    aviones[vuelo].cantidadDisponibleClaseEconomica--;
    else
         aviones[vuelo].cantidadDisponiblePrimeraClase--;
    generarFactura(vuelo,cliente);
    return 0;
}
int cancelarBoleto(int vuelo, char nombre[50], int asiento){
    int pos = -1;
  printf("\n");
  int i;
  for( i= 0; i<30 ; i++)
  if(strcmp(nombre,aviones[vuelo].clientes[i].nombre)==0)
      pos = i;

  if(pos!=-1){
      if(aviones[vuelo].clientes[pos].asiento == asiento){
          int direcciony=0;
          int direccionx = 0;
          if(asiento%2 == 0)
              direcciony = 1;
          if(direcciony==1)
              direccionx= (asiento/2)-1;
          else
              direccionx = (asiento-1)/2;
          aviones[vuelo].Disponibles[direcciony][direccionx] = 'D';
          if(aviones[vuelo].asientos[direcciony][direccionx]== 'E'){
              aviones[vuelo].cantidadDisponibleClaseEconomica++;
              total-= aviones[vuelo].precio_Economico;
          }else{
              aviones[vuelo].cantidadDisponiblePrimeraClase++;
               total-=aviones[vuelo].precio_PrimeraClase;
          }
        aviones[vuelo].ultimocliente--;
        printf("---------------------------------------\n");
        printf("Avion\n");
        printf("---------------------------------------\n");
        int i;
        int j;
        for( i = 0; i<2; i++){
            for( j= 0; j<15; j++){
               printf("%c",aviones[vuelo].Disponibles[i][j]);
            }
            printf("\n");
            printf("\n");
            printf("-------Se Cancelo el Boleto----------\n");
        }
        system("pause");
        return 0;
      }
  }
  printf("Numero de Asiento Incorrecto\n");
  system("pause");
  return -1;
}
void reportes(){
    int salir = -1;
    int opcion = -1;
    int vuelo = -1;
    while(salir!=1){
    printf("1. Reportes Ventas Totales\n");
    printf("2. Listado de Pasajeros\n");
    printf("3. Asientos Disponible\n");
    printf("4. Salir\n");
        scanf("%i",&opcion);
        switch (opcion) {
        case 1:
            printf("Ventas del Dia:");
            printf("%f",total);
            printf("\n");
            break;
        case 2:
            printf("Ingrese el Codigo del Vuelo: ");
            scanf("%i",&vuelo);
            mostrarPasajeros(vuelo-1);
            break;
        case 3:
            printf("Ingrese el Codigo del Vuelo: ");
            scanf("%i",&vuelo);
            InfoDeAvion(vuelo-1);
            printf("---------------------------------------\n");
            printf("Avion(Disponibles)\n");
            printf("---------------------------------------\n");
            int i;
            int j;
            for( i = 0; i<2; i++){
                for( j= 0; j<15; j++){
                   printf("%c",aviones[vuelo-1].Disponibles[i][j]);
                }
                printf("\n");
                printf("\n");
            }
            system("pause");
            break;
          case 4:
            salir=1;
            break;
        default:
            break;
        }
    }
}

void mostrarPasajeros(int vuelo){
    int i;
    for( i= 0; i<aviones[vuelo].ultimocliente;i++){
        printf("Nombre: ");
        printf("%s",aviones[vuelo].clientes[i].nombre);
        printf("\n");
        printf("Numero de Asiento: ");
        printf("%i",aviones[vuelo].clientes[i].asiento);
        printf("\n");
    }
}

