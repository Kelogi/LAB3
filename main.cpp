#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

void imprimir_arreglo_binario(int*ptr_arreglo_binarios){
    for(int au=0;au<64;au++){
        cout<<*(ptr_arreglo_binarios+au);
    }
}
int tam_file(){
    fstream archivo("file.txt");
    unsigned long long tam;
    tam=8;   //tam=archivo.tellg();
    archivo.close();
    return tam;
}

char* crear_arreglo_de_caracteres(int tamanio){
    fstream archivo("file.txt");

    char* ptr_caracteres;
    ptr_caracteres=new char[tamanio];

    char letra;
    for(int i=0;i<tamanio;i++){
        archivo>>letra;
        *(ptr_caracteres+i)=letra;
    }
    archivo.close();

    return ptr_caracteres;

}

int* num_a_binario_arreglo(int num){
    int *ptr_arre_num_en_bi;
    ptr_arre_num_en_bi=new int[8];
    for(int z=0;z<8;z++){
        *(ptr_arre_num_en_bi+z)=num%2;
        num=num/2;
    }
    return ptr_arre_num_en_bi;

}

int* crear_arreglo_numeros_bi(){
    fstream archivo("file.txt");

    int tam;
    tam=tam_file();

    char* ptr_caracteres;
    ptr_caracteres=crear_arreglo_de_caracteres(tam);

    int *ptr_arreglo_binarios;
    ptr_arreglo_binarios=new int[8*tam];

    int numero_ascci;
    int posicion_arrebi_general=0;

    for(int au=0;au<tam;au++){
        numero_ascci=int(*(ptr_caracteres+au));
        //transformamos el numero ascci a binario, y lo guardamos en un arreglo--->ptr_arre_num_bi;
        int* ptr_arreglo_num_en_bi;
        ptr_arreglo_num_en_bi=num_a_binario_arreglo(numero_ascci);
        int posicion_numero_ascci=0;
        for(int k=posicion_arrebi_general+7;k>=posicion_arrebi_general;k--){
            *(ptr_arreglo_binarios+k)=*(ptr_arreglo_num_en_bi+posicion_numero_ascci);
            posicion_numero_ascci+=1;
        }
        posicion_arrebi_general+=8;

    }

    archivo.close();
    return ptr_arreglo_binarios;
}

int* arreglo_cambiosXbloques(int *ptr_arreglo_numeros_binario,int semilla,int tam){
    int *ptr_arreglo_cambiosXbloques;
    ptr_arreglo_cambiosXbloques=new int[((tam*8)/(semilla))];
    *(ptr_arreglo_cambiosXbloques)=1;
    int posiciones_arreglo=1;
    int cantidad_0=0;
    int cantidad_1=0;
    for(int au=0;au<(tam*8);au++){
        if((au+1)%semilla==0){
            if((*(ptr_arreglo_numeros_binario+au))==1){
                cantidad_1+=1;
            }
            else{
                cantidad_0+=1;
            }

            if(cantidad_1==cantidad_0){
                *(ptr_arreglo_cambiosXbloques+posiciones_arreglo)=1;
            }

            else if(cantidad_1<cantidad_0){
                *(ptr_arreglo_cambiosXbloques+posiciones_arreglo)=2;
            }

            else if(cantidad_1>cantidad_0){
                *(ptr_arreglo_cambiosXbloques+posiciones_arreglo)=3;
            }
            posiciones_arreglo+=1;
            cantidad_0=0;
            cantidad_1=0;


        }

        else{
            if((*(ptr_arreglo_numeros_binario+au))==1){
                cantidad_1+=1;
            }
            else{
                cantidad_0+=1;
            }

        }
    }

    return ptr_arreglo_cambiosXbloques;

}

//aplicar cambios tipo 1 a un bloque;
void cambios_modo1(int*ptr_numeros_binarios,int indice1,int indice2){
    for(int au=indice1;au<=indice2;au++){
        if((*(ptr_numeros_binarios+au)==0)){
            *(ptr_numeros_binarios+au)=1;
        }
        else{
        *(ptr_numeros_binarios+au)=0;
        }
    }

}

//aplicar cambios tipo 2 a un bloque;
void cambios_modo2(int*ptr_numeros_binarios,int indice1,int indice2){
    int auxiliar=0;
    for(int au=indice1;au<=indice2;au++){
        auxiliar+=1;
        if(auxiliar%2==0){
            if(*(ptr_numeros_binarios+au)==1){
                *(ptr_numeros_binarios+au)=0;

            }
            else
                *(ptr_numeros_binarios+au)=1;
        }
    }
}
//aplicar cambios tipo 3 a un bloque;
void cambios_modo3(int*ptr_numeros_binarios,int indice1,int indice2){
    int auxiliar=0;
    for(int au=indice1;au<=indice2;au++){
        auxiliar+=1;
        if(auxiliar%3==0){
            if(*(ptr_numeros_binarios+au)==1){
                *(ptr_numeros_binarios+au)=0;

            }
            else
                *(ptr_numeros_binarios+au)=1;
        }
    }
}

void codificar_metodo1(int *ptr_numeros_binario,int *arreglo_cambiosXbloques,int semilla,int tam){
    cambios_modo1(ptr_numeros_binario,0,semilla-1);


    int posicion_arreglo_numeros_binarios=semilla;
    int _cambio_bloque;
    for(int i=1;i<tam;i++){
        _cambio_bloque=*(arreglo_cambiosXbloques+i);

        if(_cambio_bloque==1){
            cambios_modo1(ptr_numeros_binario,posicion_arreglo_numeros_binarios,(posicion_arreglo_numeros_binarios)+(semilla-1));
        }

        if(_cambio_bloque==2){
            cambios_modo2(ptr_numeros_binario,posicion_arreglo_numeros_binarios,(posicion_arreglo_numeros_binarios)+(semilla-1));
        }

        if(_cambio_bloque==3){
            cambios_modo3(ptr_numeros_binario,posicion_arreglo_numeros_binarios,(posicion_arreglo_numeros_binarios)+(semilla-1));
        }

        posicion_arreglo_numeros_binarios+=semilla;

    }

}

int* ejecutar_metodo1()
{

     cout<<"sin codificar"<<endl;
     int *ptr_arreglo_bin;
     ptr_arreglo_bin=crear_arreglo_numeros_bi();
     imprimir_arreglo_binario(ptr_arreglo_bin);
     int *ptr_cambiosXbloques;
     ptr_cambiosXbloques=arreglo_cambiosXbloques(ptr_arreglo_bin,4,((8*8)/(4)));//((tam*8)/(semilla))


    cout<<"codificado: "<<endl;
    codificar_metodo1(ptr_arreglo_bin,ptr_cambiosXbloques,4,16);
    imprimir_arreglo_binario(ptr_arreglo_bin);

    fstream archivo("file.codificado.txt",ios::out);
    int exponente;
    int numero_ascci;
    for(int au=7;au<64;au+=8){
        exponente=0;
        numero_ascci=0;
        for(int i=au;i>=(au)-7;i--){
            numero_ascci+=(*(ptr_arreglo_bin+i))*pow(2,exponente);
            exponente+=1;
        }

        cout<<endl;
        cout<<"ascci: "<<numero_ascci;
        archivo<<char(numero_ascci);

         cout<<"-->"<<char(numero_ascci);


    }

    archivo.close();

}

//-------------------------------------funciones decodificar------------------------------
int main()
{
    ejecutar_metodo1();

}

//---------------------------------------------------------------------------------------------



