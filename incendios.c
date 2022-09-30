#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include<TIME.H>

typedef  char string[31];
typedef struct registro
{
    int anio;
    string provincia;
    string causa;
}formato;
int ArrEstadistico[24][5][6];
/*
24 filas= 23 provincias + subtotal por causa
5 columnas= 4 causas + subtotal por prvincias
6 profundidades= 5 años + totales generales(se acumulan aqui todos los datos si importar su año)
*/
void inicializar()
{
    int i, j, k;
    for ( i = 0; i < 23; i++)
        for (j = 0; j < 5; j++)
            for (k = 0; k < 6; k++)
                ArrEstadistico[i][j][k]=0;
}
int provincia(char Pal[])
{
    /*
        Esta funcion nos ayuda a identificar, según su provincia, la fila del arreglo que corresponde a este registro.
        Para hacer esto contamos con el arreglo "prov" que contiene los nombres de las provincias en orden alfabético
        (este mismo orden de provincias se aplicará al arreglo estadístico "ArrEstadistico").
    */
    string prov[23]={"Buenos Aires", "Catamarca", "Chaco", "Chubut", "Cordoba", "Corrientes", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tierra del Fuego", "Tucuman" };
    int  i;
    i=0;
    //busqueda con centinela de la provincia. Se da por hecho que no se recivirá un string que no coincida
    while (strcmp(Pal, prov[i])!=0)
        i++;
    return(i);
}
int causa(char M[])
{
    /*
        Esta funcion nos ayuda a identificar, según su causa, la columna del arreglo que corresponde a este registro.
        Para hacer esto contamos con el arreglo "causas" que contiene los nombres de las causas. 
        (este mismo orden de causas se aplicará al arreglo estadístico "ArrEstadistico").
    */
    string causas[4]={"Negligencia", "Natural", "Desconocida", "Intencional"};
    int  i;
    i=0;
    //busqueda con centinela de la causa. Se da por hecho que no se recivirá un string que no coincida
    while (strcmp(M, causas[i])!=0)
        i++;
    return(i);
}
int anios(int X) 
{
    //Esta funcion nos ayuda a identificar, según su año, la profundidad del arreglo que corresponde a este registro. 
    switch (X)
    {
    case 2015:
        return(0);
    case 2016:
        return(1);
    case 2017:
        return(2);
    case 2018:
        return(3);
    case 2019:
        return(4);
    }
}
void Acitividad1()  //1) Cantidad total de incendios por año.
{
    int anio, k;
    anio = 2015;
    for (k= 0; k < 5; k++, anio++)    
    printf("\nEn el a%co %d ocurrieron un total de %d incendios\n", 164, anio, ArrEstadistico[23][4][k]);
    printf("\n\n"); //doble salto de línea al final de una actividad
}
void Actividad2()   //2) Provincia con mayor cantidad de incendios en general.
{   
    //(Volví a declarar el mismo arreglo "prov" de la función "provincia" para lograr la escritura por pantalla).
    string prov[23]={"Buenos Aires", "Catamarca", "Chaco", "Chubut", "Cordoba", "Corrientes", "Entre Rios", "Formosa", "Jujuy", "La Pampa", "La Rioja", "Mendoza", "Misiones", "Neuquen", "Rio Negro", "Salta", "San Juan", "San Luis", "Santa Cruz", "Santa Fe", "Santiago del Estero", "Tierra del Fuego", "Tucuman" };
    int max= 0, bandera= 0, i, a;
    for ( i = 0; i < 23; i++)
    {
        if (ArrEstadistico[i][4][5]> max)
        {
            max= ArrEstadistico[i][4][5];
            a=i;
            bandera= 0;

        }else if (ArrEstadistico[i][4][5]==max)
            bandera= 1;
    }
    if (max==0)
        printf("No hubo incendios entre 2015 y 2019"); //Esto es un escenario aún más irreal, pero... por las dudas.  
    else if (bandera==0) //en el caso de que haya una sola provincia con la mayor cantidad de incendios.
        printf("%s es la Provincia con mayor cantidad de incendios entre 2015 y 2019 con %d incendios.\n", prov[a], max);
    else //en el caso en que sean multiples provincias con la mayor cantidad de incendios
    {
        printf("Las Provincias que sufrieron la mayor cantidad de incendios (%d incendios) entre 2015 y 2019 son:\n", max);
        for ( i = 0; i < 23; i++)
        {
            if (ArrEstadistico[i][4][5]==max)
                printf("%s.\n", prov[i]);
        }
    }
    printf("\n\n");  //doble salto de línea al final de una actividad
}
void Actividad3()   //3)Inmforme los subtotales generales de incendios según sus causas.
{
    //Extraigo los datos de la última profundidad del arreglo
    printf("Informe los totales generales de incendios segun sus causas: \n");
    printf("El total de incendios por negligencia es: %d \n", ArrEstadistico[23][0][5]);
    printf("El total de incendios por causas naturales es: %d \n", ArrEstadistico[23][1][5]);
    printf("El total de incendios por causas desconocidas es: %d \n", ArrEstadistico[23][2][5]);
    printf("El total de incendios intencionales es: %d \n", ArrEstadistico[23][3][5]);
    printf("\n\n");  //doble salto de línea al final de una actividad
}
void Actividad4()   //4)Informe los subtotales anuales según sus causas.
{
    int anio, k;
    anio=2015;
    printf("Subtotales anuales segun sus causas:\n");
    for ( k = 0; k < 5; k++, anio++)
    {
        printf("#%d:\n", anio);
        printf("Cantidad de incendios por negligencia de este a%co es: %d\n", 164, ArrEstadistico[23][0][k]);
        printf("Cantidad de incendios por causas naturales de este a%co es: %d\n", 164, ArrEstadistico[23][1][k]);
        printf("Cantidad de incendios por causas desconocidas de este a%co es: %d\n", 164, ArrEstadistico[23][2][k]);
        printf("Cantidad de incendios por causas intencionales de este a%co es: %d\n", 164, ArrEstadistico[23][3][k]);
        printf("\n\n");  //doble salto de línea al final de una actividad
    }
}
int main()
{
    FILE *INCENDIOS;
    formato Reg;
    int i, j, k;
    INCENDIOS= fopen("INCENDIOS.dat", "rb");
    inicializar();
    if (INCENDIOS==NULL)
    {
        printf("Error al abrir el archivo 'INCENDIOS.dat'. Verifique su existencia.\nCerrando programa...");
        return(1);
    }else
    {
        printf("Archivo abierto exitosamente.\n\n\n");
        //Proceso estadístico
        fread(&Reg,sizeof(formato),1,INCENDIOS);
        do
        {
            //Obtener la direccion que corresponde al registro
            i= provincia(Reg.provincia);
            j= causa(Reg.causa);
            k= anios(Reg.anio);
           
            //Cargo las 6 primeras profundidades del arreglo(subtotales anuales, totales del año).
            ArrEstadistico[23][j][k]++;  //subtotal del anual por causa.            
            ArrEstadistico[i][4][k]++; //subtotal del anual por provincia.
            ArrEstadistico[i][j][k]++;  //subtotal anual por provincia y por causa.
            ArrEstadistico[23][4][k]++; //total del anual.

            //Cargo la última profundidad del arreglo(subtotales generales, total general).
            //El uso de una profundidad extra para acumular los totales de las anteriores 6 profundidades nos facilita las actividades.  
            ArrEstadistico[i][4][5]++; //subtotal general por provincia.           
            ArrEstadistico[23][j][5]++; //subtotal general por causa.
            ArrEstadistico[i][j][5]++; // subtotal general por provincia y causa.           
            ArrEstadistico[23][4][5]++; //total general.

            fread(&Reg,sizeof(formato),1,INCENDIOS); 
        }while (!feof(INCENDIOS));

        fclose(INCENDIOS);
        printf("---------------INFORME DE INCENDIOS (2015-2019)---------------\n");
        Acitividad1();
        Actividad2();
        Actividad3();
        Actividad4();
        printf("-----------------------FIN DEL INFORME------------------------\n\n\n\n");
        system("pause");
    } 

    return(0);
 
}




