![UCN](https://i.postimg.cc/KYxJMwds/Isologo-UCN-2018.png)


# Informe Técnico 
## Curso: Estructura de datos
### Detección y reidentificación de caras en secuencias de imágenes o video

**Alumnos:**


* Felipe Geraldo (Programador)
* Francisco Lopez (Programador)

## Resumen 

> La problemática que se nos planteó en este proyecto fue la detección y Re identificación de caras en secuencias de imágenes o video la cual como grupo abordamos de la manera más cómoda posible en cuanto a distribución de tiempos en cuanto a nuestra disponibilidad, para así lograr mayor eficiencia y eficacia en el trabajo. Logramos llegar a plasmar una idea de solución para posteriormente desarrollarla hasta obtener un resultado de nuestro agrado, todo esto apoyado desde las ayudantías brindadas por nuestro profesor y ayudante a cargo, las cuales nos ayudaron en cuanto a conocimientos que no teníamos respecto a este tipo de problemas. Posteriormente fuimos capaces de finiquitar las últimas partes de la primera parte de nuestro proyecto. Durante la realización del mismo informe como grupo nos retroalimentamos con todo el conocimiento que pasamos desapercibido, a grandes rasgos tenemos avances positivos lo cual nos favorece para finiquitar este proyecto.

## 1. Introducción

Actualmente en el mundo de la Informática se están realizando grandes avances en el tratamiento de imágenes y de la inteligencia artificial. Algo común para nosotros como lo es la detección y el poder contabilizar personas que están entrando y saliendo de un lugar solo dedicando un poco de atención.

La dificultad que nos conlleva es si una misma persona vuelve al lugar  y no sea contada dos veces, pero todo esto es más complicado de realizar mediante un ordenador . Este no tiene la capacidad de distinguir por sí mismo los objetos que no son útiles para nuestros requerimientos así mismo una cámara de última generación puede llegar a ver el mundo como nosotros pero no interpretarlo como nosotros. Siguiendo esta línea , este proyecto se basa en la detección de una persona y lograr un reconocimiento de esta, para darnos el análisis de estos datos obtenidos. 

Palabras clave: Informatica, reconocimiento, Detección, Ordenador


### 1.1 Descripción del problema

La detección de personas dentro de una imagen y el poder usar los datos del análisis de esta misma.


### 1.2 Objetivos 

**Objetivo General**

El fin que se desea llegar. (Comenzar con un verbo: "Construir un sistema...", "Desarrollar un sistema...", etc)

**Objetivos específicos**

1. Capturar la escena en la que encontramos las personas a identificar, mediante el los algoritmos
2. Procesar la imagen para quedarnos únicamente con los datos útiles. En este paso evitaremos errores de conteo en el caso que la misma persona ingrese o se retire en    múltiples ocasiones .
3. Implementar la estructura de datos mediante listas enlazadas.
4. Realizar e implementar una interfaz gráfica que muestre los resultados del conteo de personas


### 1.3 Solución propuesta

Esbozo de la solución propuesta, se espera que esta vaya evolucionando a medida que se avanza en el proyecto.

## 2. Materiales y métodos

Explicar brevemente como se espera desarrollar el trabajo de implementación.

### 2.1 Instalación

En el trabajo usamos openCv y visual studio code , todo esto nos fue muy facil de obtener debido a que el ayudante de la asignatura nos brindo tutoriales de como instalar la ide y sus respectivas librerias

### 2.2 Diseño 

Explicar los componentes (módulos o clases) utilizados para resolver el problema. Indicar arquitectura propuesta, diagrama de clases u otro artefacto que estime conveniente para explicar el diseño de su implimentación.

### 2.3 Implementación

Explicar brevemente algunos aspectos de implementación: Por ejemplo, detector de caras utilizado. Se pueden realizar pequeñas reseñas al código para indicar elementos importantes en el trabajo.

Por ejemplo, 

#### Detector de caras

El detector de caras utilizado fue xxx. Para utilizarlo se debe.... El código para detectar una cara en una imagen se muestra a continuación:

```c++
 int main(int argc, char** argv)
{
    
    Detector detector;
    Mat imagen;
    int cont = 0;
    int cont2 = 0;
   
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

//Contadores:
        //Si va desde arriba hacia abajo se le suma +1 al contador de entrantes
        if(p.getYCentro()<200 && p.getYCentro() >210 && p.getXCentro() > 0 && p.getXCentro()<800){
            cont = cont + 1;
        }
        //Si va desde abajo hacia arriba se le suma +1 al contador de salientes
        if(p.getYCentro()>200 && p.getYCentro() <190 && p.getXCentro()> 0 && p.getXCentro() <800){
            cont2 +=1;
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
```

## 3. Resultados obtenidos
[](ED22-01-Lopez-Geraldo/imagen_2022-06-24_161511837.png) 
## 4. Conclusiones
< Nuestro avances estan dirigiendose de forma positiva a nuestra meta propuesta y nuestro codigo esta llegando 

# Anexos

## Anexo A: Instalación librerías OpenCV
   [*] https://drive.google.com/file/d/136fquVeP-fY-pYgR3kPt6iioiovlodrn/view?usp=sharing
## Anexo B: Instalación de IDE y configuración librerías OpenCV
   [*] https://www.youtube.com/watch?v=Hu7ArOaFm2g
# Referecia

Indicar los libros, páginas web, documentos, etc. Utilizados en el trabajo. Por ejemplo:

[1] Adrian Rosebrock. OpenCV People Counter. https://pyimagesearch.com/2018/08/13/
opencv-people-counter/.
[2] Darkcrizt OpenCV una biblioteca para el reconocimiento de objetos en imágenes y cámaras https://blog.desdelinux.net/opencv-una-biblioteca-para-el-reconocimiento-de-objetos-en-imagenes-y-camaras/
[3] Gabriela Solano DETECCIÓN DE MOVIMIENTO (Con sustracción de imágenes) – OpenCV y Python https://omes-va.com/deteccion-de-movimiento-con-sustraccion-de-imagenes-opencv-y-python/#google_vignette

