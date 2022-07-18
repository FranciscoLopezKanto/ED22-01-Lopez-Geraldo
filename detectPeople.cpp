// This file is part of OpenCV project.
// It is subject to the license terms in the LICENSE file found in the top-level directory
// of this distribution and at http://opencv.org/license.html

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <opencv2\opencv.hpp>
#include "Detector.hpp"
#include "Persona.hpp"


using namespace cv;
using namespace std;

struct nodo{
       int nro;        // en este caso es un numero entero
       struct nodo *sgte;
};
 
typedef struct nodo *Tlista;
 
void insertarInicio(Tlista &lista, int valor)
{
    Tlista q;
    q = new(struct nodo);
    q->nro = valor;
    q->sgte = lista;
    lista  = q;
}


void delay(int secs) {
  for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

float calcularPH(int personas){
  //  Q = NumeroPersonas/Tiempo
  // CALCULO ES => (NumeroPersonas/MinutosVideo)x(60 Minutos/1 Hora)
  // tomando como premisa que el extracto de video que usamos dura 15 segundos, es decir 0.25 minutos, calcularemos el flujo con esto
  float Q;
  float x=personas/0.25; //nuestra cantidad de personas que entraran o saldran en nuestro video a analizar
  Q= x*60; //el total de personas por hora
  return Q;
}


void LecturaImagen(int P1, int P2,int opcion){
    Detector detector;
    int pos = 0;
    char *filepath = new char[200];

    
    for(int i = 1; i <= 96; i++){

        sprintf(filepath, "/Users/felog/Desktop/opencvtest/images/%d.jpg",i);
        Mat imagen = imread(filepath);
        Tlista listaE = NULL;
        Tlista listaS = NULL;

        //requerimiento 1
        vector<Persona> found = detector.detect(imagen);
        for (vector<Persona>::iterator j = found.begin(); j != found.end(); ++j){
            Persona p = *j;
           
            cout << "(" << p.getXCentro() << ", " << p.getYCentro() << ")" << endl;
            //detector.adjustRect(r);
            rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 255, 0), 2);
            circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(0, 0, 255), 3);
            circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
            circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);
            //Requerimiento 2
            //Si va desde arriba hacia abajo +1 al contador de entrantes
            if(p.getYCentro()<=145 && p.getYCentro() >=140 && p.getXCentro() > 0 && p.getXCentro()<800 && pos<p.getXComienzo()){
                P1 = P1 + 1;
                insertarInicio(listaE, P1);            
            }
            //Requerimiento 3
            //Si va desde abajo hacia arriba se le suma +1 al contador de salientes
            if(p.getYCentro()<=145 && p.getYCentro() >=140 && p.getXCentro()> 0 && p.getXCentro() <800 && pos>p.getXComienzo()){
                P2 +=1;
                insertarInicio(listaE, P2);
            }
            pos = p.getXComienzo();
        }
        //redimensionamos la imagen para que siempre sea 800x400 y asi facilitar el dibujado de la linea
            resize(imagen,imagen,Size(800,400));
            
            if(opcion==1){
                char str[200];
                sprintf_s(str, "Total de entradas:" "%i",P1);
		        putText(imagen, str, Point2f(33,365), FONT_HERSHEY_COMPLEX_SMALL, 0.7,  Scalar(0,0,0, 0.5), 1);
            
                char str2[200]; 
                sprintf_s(str2, "Total de salidas:" "%i",P2);
		        putText(imagen, str2, Point2f(33,385), FONT_HERSHEY_COMPLEX_SMALL, 0.7,  Scalar(0,0,255, 0.5), 1);     

                //linea encargada del paso 
                line(imagen, Point(0, 200) , Point(800,200), Scalar(0,0,255),2, 8, 0);
            }
            
            

        
        imshow("People detector", imagen);
        char c=(char)waitKey(25);

        if(c==27){
            break;
        }
        
       
    }
    if(opcion==1){
        cout << " Requerimiento 4" << endl;
        // requerimiento 4,(personas/hora) entradas
        printf("\n El flujo de personas que ENTRAN (personas/hora) es : " "%i",calcularPH(P1));
        // requerimiento 5,(personas/hora) salida
        cout << "\nRequerimiento 5" << endl;
        printf("\n El flujo de personas que SALEN (personas/hora) es: " "%i",calcularPH(P2));
    }
    
}


int Menu(){
    int PersonasEntradas = 0;
    int PersonasSalida = 0;
    int opcion;
    bool repetir = true;
    printf("\n Bienvenido al sistema de vigilancia de ACME");
    printf("\n Ingrese como desea entrar al sistema" );
    do {
        // Texto del menú que se verá cada vez
        
        cout << "\n 1. Guardia" << endl;
        cout << " 2. Administrador" << endl;
        cout << "\nIngrese una opcion: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                // Lista de instrucciones de la opción 1                  // requerimiento 1 ,rectangulo rojo
                cout << " Requerimiento 1" << endl;
                LecturaImagen(PersonasEntradas,PersonasSalida,opcion);     
                exit(1);
                
            case 2:
                // Lista de instrucciones de la opción 2  
                printf("\n obteniendo las imagenes que serán analizadas.......");
                delay(2);   
                LecturaImagen(PersonasEntradas,PersonasSalida,opcion);

                //Mostrar video solo con los centroides de las personas , sin contador ni nada
                
                exit(1);
            case 3:

                break;
            
        }        
    } while (repetir);
	 
    return 0;
}



int main(int argc, char** argv)
{
    Menu();
    return 0;
}


