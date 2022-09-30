#include<stdio.h> 
#include<string.h>
typedef char string[31];
typedef struct registro
{
    int anio;
    string provincia;
    string causa;
}formato;

FILE *INCENDIOS;
formato Reg;
string prov[23]={"Buenos Aires", "Catamarca", "Chaco", "Chubut", "Cordoba", "Corrientes", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tierra del Fuego", "Tucuman" };
string causas[4]={"Negligencia", "Natural", "Desconocida", "Intencional"};
//todo lo anterior a esta linea es sacado el algoritmo de "Lab-C", (copiar/pegar)
int num_prov, num_causa;
void sobrescribir() 
{
    //abro el archivo con el modo "wb" solo porque quiero crearlo si no existe o sobrescribirlo
    INCENDIOS = fopen("INCENDIOS.dat", "wb"); 
    if (INCENDIOS!=NULL)
    {
        printf("Archivo creado/reescrito con exito\n");
        fclose(INCENDIOS);
    }
    else
    printf("No se pudo crear el archivo\n\n\n");    
}
int cargar()
{   
    int i, cant;
    string nom;
    INCENDIOS = fopen("INCENDIOS.dat", "ab"); //abro archivo en modo "ab" para siempre añadir en vez de sobrescribir
    if (INCENDIOS!=NULL)
    {
        printf("Archivo abierto con exito\n\n");
        fflush(stdin);
         
        printf("Ingrese el a%co del incendio (entre 2015 y 2019): ", 164); //pregunto el año
        scanf("%i", &Reg.anio);
        if (2015>Reg.anio || Reg.anio>2019) 
        {
            printf("dato erroneo, descartando registro\n");  //si el año no entra dentro de las especificaciones salta este aviso y te devuelve al "menu"
            return(1);
        } 
        printf("Ingrese el numero de la causa (0-negligencia, 1-natural, 2-desconocido, 3-intencional): ");  //pregunto la causa según un numero del 0 al 3
        scanf("%i", &num_causa);
        if (0>num_causa || num_causa>3)
        {
            printf("dato erroneo, descartando registro\n");  //si el numero entra dentro de las especificaciones salta este aviso y te devuelve al "menu"
            return(1);
        } 
        strcpy(Reg.causa, causas[num_causa]);
        printf("Ingrese el numero de la provincia (segun el orden alfabetico, empezando por 0 y terminando por el 22): ");  //pregunto la causa según un numero del 0 al 22 y un orden
        scanf("%i", &num_prov);
        if (0>num_prov || num_prov>22)
        {
            printf("dato erroneo, descartando registro\n"); //si el numero entra dentro de las especificaciones salta este aviso y te devuelve al "menu".
            return(1);
        } 
        strcpy(Reg.provincia, prov[num_prov]);
        printf("Ingrese la cantidad: "); //para facilitar la carga de varios registros identicos
        scanf("%d\n", &cant);
        
        fflush(stdin);
        for ( i = 0; i < cant; i++)
        {
            fwrite(&Reg,sizeof(formato),1,INCENDIOS); //se escribe el registro en el archivo cuantas veces el usuario desee
        }

        fclose(INCENDIOS);
        return(1);
    }
    else
    printf("No se pudo abrir el archivo\n");
}
void listar()
{
    int bandera = 0;
    INCENDIOS = fopen("INCENDIOS.dat", "rb"); //Abro el archivo en modo "rb" porque en esta funcion solo me intereza leer
    if (INCENDIOS!=NULL)
    {
        printf("\n\n");
        fread(&Reg,sizeof(formato),1,INCENDIOS);  
        while (!feof(INCENDIOS))   //listado
        {
            printf("Incendio producido en el a%co %d en la provincia de %s por causas %s\n", 164, Reg.anio, Reg.provincia, Reg.causa);
            bandera++;
            fread(&Reg,sizeof(formato),1,INCENDIOS);
        }
        if (!bandera)  //como el "0" es el equivalente a "falso" en "C", uso esto para verificar si el valor de la bandera es 0
        printf("Archivo vacio");  
        printf("\n\n");
        fclose(INCENDIOS);
    }
    else
    printf("No se pudo leer el archivo(puede que no exista)\n");
}
void Numprovincias()
{
    printf("Provincias: \n0-Buenos Aires | 1-Catamarca | 2-Chaco | 3- Chubut | 4- Cordoba | 5- Corrientes | 6- Entre Rios \n7- Formosa | 8- Jujuy | 9- La Pampa| 10- La Rioja | 11- Mendoza| 12- Misiones| 13- Neuquen| 14- Rio Negro| 15- Salta \n16- San Juan| 17- San Luis | 18- Santa Cruz | 19- Santa Fe | 20- Santiago del Estero | 21- Tierra del Fuego \n22- Tucuman\n\n");
}
void main()
{
    int opcion;
    do
    {
        //esto es un menu
        printf("1-Crear/sobrescribir el archivo.\n2-Agregar un registro al archivo.\n3-Listado de todo el archivo\n4-Enumerado de provincia\n5-Salir del programa.\n\nIngrese su opcion: ");
        scanf("%d", &opcion);
        switch (opcion)
        {
        case 1: sobrescribir(); //esta funcion crea o sobreescribe el archibo, pero no la usamos para escribir en el archivo
            break;
        case 2: cargar(); //esta funcio sirve para escribir en el archivo añadiendo en vez de sobrescribir
            break;
        case 3: listar(); //esta produce un listado de todos los registros (si hay mas de uno identicos no los va a agrupar, los va a mencionar uno por uno)
            break;
        case 4: Numprovincias(); //esta imprime la enumeracion de todas las provincias para ayudar al usuario
            break;
        case 5: printf("Cerrando programa..."); //al salir del switch esta vez tambien saldra del while y se termina el programa
            break;
        default: printf("Opcion invalida!!!!!!!\n\n"); //por si acaso
            break;
        }
    } while (opcion !=5);
}