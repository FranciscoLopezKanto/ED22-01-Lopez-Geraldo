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



int main(int argc, char** argv)
{
   
    Detector detector;
    Mat imagen;
    int cont = 0;
    int cont2 = 0;
    Tlista listaE = NULL;
    Tlista listaS = NULL;
   
    imagen = imread("/Users/felog/Desktop/opencvtest/images/image1679.png");
   
    
    detector.toggleMode();
    cout << detector.modeName() << endl;
    
    vector<Persona> found = detector.detect(imagen);
    for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
    {

        Persona &p = *i;
        cout << "(" << p.getXComienzo() << ", " << p.getYComienzo() << ")" << endl;
        //detector.adjustRect(r);
        rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 255, 0), 2);
        circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(0, 0, 255), 3);

//Contador y se agrega a una lista:
        //Si va desde arriba hacia abajo se le suma +1 al contador de entrantes
        if(p.getYCentro()<200 && p.getYCentro() >210 && p.getXCentro() > 0 && p.getXCentro()<800){
            cont = cont + 1;
            insertarInicio(listaE, cont);
        }
        //Si va desde abajo hacia arriba se le suma +1 al contador de salientes
        if(p.getYCentro()>200 && p.getYCentro() <190 && p.getXCentro()> 0 && p.getXCentro() <800){
            cont2 +=1;
            insertarInicio(listaS, cont2);
        }
    }   
    //redimensionamos la imagen para que siempre sea 800x400 y asi facilitar el dibujado de la linea
    resize(imagen,imagen,Size(800,400));

    //Texto que muestra el contador de personas entrantes y salientes
    char str[200];
        sprintf_s(str, "Total de entradas:" "%i",cont);
		putText(imagen, str, Point2f(33,365), FONT_HERSHEY_COMPLEX_SMALL, 0.7,  Scalar(0,0,0, 0.5), 1);
    char str2[200];
        sprintf_s(str2, "Total de salidas:" "%i",cont2);
		putText(imagen, str2, Point2f(33,385), FONT_HERSHEY_COMPLEX_SMALL, 0.7,  Scalar(0,0,255, 0.5), 1);   
    //linea encargada del paso 
    line(imagen, Point(0, 200) , Point(800,200), Scalar(0,0,255),2, 8, 0);
    imshow("People detector", imagen);
    waitKey(0);
    
    
    return 0;
}

