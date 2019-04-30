#include <SoftwareSerial.h>
#include <Servo.h>
SoftwareSerial SerialESP8266(10,11); // RX, TX

Servo servoMotor;
int servoEstado;

//sensor de humedad
const int sensor = A0;

String server = "192.168.43.50";

String cadena="";
boolean flag_agua = false;
boolean flag_servo = false;


const int pin_bomba=11;
const int pin_servo =9;

void setup() {

//Servo config
  servoMotor.attach(9);
  servoMotor.write(150);

  //Humedad config
  pinMode(sensor, INPUT);
  //Serial.begin(9600);

  //Bomba config
  pinMode(pin_bomba,OUTPUT);

    //Serbo config
  pinMode(pin_servo,OUTPUT);
  
  SerialESP8266.begin(9600);
  Serial.begin(9600);
  SerialESP8266.setTimeout(2000);
  
  //Verificamos si el ESP8266 responde
  SerialESP8266.println("AT");
  if(SerialESP8266.find("OK"))
    Serial.println("Respuesta AT correcto");
  else
    Serial.println("Error en ESP8266");

  //-----Configuración de red-------//Podemos comentar si el ESP ya está configurado

    //ESP8266 en modo estación (nos conectaremos a una red existente)
    SerialESP8266.println("AT+CWMODE=1");
    if(SerialESP8266.find("OK"))
      Serial.println("ESP8266 en modo Estacion");
      
    //Nos conectamos a una red wifi 
    //SerialESP8266.println("AT+CWJAP=\"CLARO_f2838c\",\"EEEBbeBFBC\"");
    SerialESP8266.println("AT+CWJAP=\"Richi\",\"ahuelita\"");
    Serial.println("Conectandose a la red ...");
    SerialESP8266.setTimeout(10000); //Aumentar si demora la conexion
    if(SerialESP8266.find("OK"))
      Serial.println("WIFI conectado");
    else
      Serial.println("Error al conectarse en la red");
    SerialESP8266.setTimeout(2000);
    //Desabilitamos las conexiones multiples
    SerialESP8266.println("AT+CIPMUX=0");
    if(SerialESP8266.find("OK"))
      Serial.println("Multiconexiones deshabilitadas");
    
  //------fin de configuracion-------------------

  delay(1000);
  
}


void loop() {
  
  //--- programa----------------------

    variable1=14;//analogRead(A0);
  
    //otras operaciones
    // . . . 
  
  
  //---------enviamos las variables al servidor---------------------
  
      //Nos conectamos con el servidor:
      
      SerialESP8266.println("AT+CIPSTART=\"TCP\",\"" + server + "\",80");
      if( SerialESP8266.find("OK"))
      {  
          Serial.println();
          Serial.println();
          Serial.println();
          Serial.println("ESP8266 conectado con el servidor...");             
    
          //Para mandar variables
          String peticionHTTP= "GET /wifi_arduino/funcion.txt";
          peticionHTTP=peticionHTTP+" HTTP/1.1\r\n";

          //String peticionHTTP= "GET /wifi_arduino/index.html?a=";
          
          //peticionHTTP=peticionHTTP+String(variable1)+" HTTP/1.1\r\n";
          
          peticionHTTP=peticionHTTP+"Host: "+server+"\r\n\r\n";
          Serial.println("Peticion lista");
          
          //Enviamos el tamaño en caracteres de la peticion http:  
          SerialESP8266.print("AT+CIPSEND=");
          SerialESP8266.println(peticionHTTP.length());
         // delay(500);
         //Imprimir la peticion en consola
          Serial.print("AT+CIPSEND=");
          Serial.println(peticionHTTP.length());
          Serial.println(SerialESP8266.read());
          Serial.println(SerialESP8266.read());
          Serial.println("Esperando <");
          //esperamos a ">" para enviar la petcion  http
          if(SerialESP8266.find(">")) // ">" indica que podemos enviar la peticion http
          {
            Serial.println("Enviando HTTP . . .");
            Serial.println("Peticion: "+peticionHTTP);
            SerialESP8266.println(peticionHTTP);
            
            if( SerialESP8266.find("SEND OK"))
            {  
              Serial.println("Peticion HTTP enviada:");
              Serial.println();
              Serial.println(peticionHTTP);
              Serial.println("Esperando respuesta...");
              
              boolean fin_respuesta=false; 
              long tiempo_inicio=millis(); 
              cadena="";
              
              while(fin_respuesta==false)
              {
                  while(SerialESP8266.available()>0) 
                  {
                      char c=SerialESP8266.read();
                      Serial.write(c);
                      cadena.concat(c);  //guardamos la respuesta en el string "cadena"
                  }
                  //Experimento



                  
                  Serial.println("Esta es la cadena");
                  Serial.println(cadena);
                  Serial.println("!!!!!!!!!!!!!");

              //////// Para buscar bomba //////
                  for(int i=0;i<cadena.length();i++){
                    if(cadena[i]=='a'){
                      if(cadena[i+1]=='s'){
                        if(cadena[i+2]=='i'){
                          Serial.println("Hay encendido");
                          flag_agua=true;
                          break;
                        }
                      }
                    }
                    if(cadena[i]=='a'){
                      if(cadena[i+1]=='n'){
                        if(cadena[i+2]=='o'){
                          Serial.println("Hay apagado");
                          flag_agua=false;
                          break;
                        }
                      }
                    }
                    else {
                      flag_agua=false;
                    }
                    
                  }


            ////// Para buscar motor /////////////////
                  for(int i=0;i<cadena.length();i++){
                    if(cadena[i]=='l'){
                      if(cadena[i+1]=='s'){
                        if(cadena[i+2]=='i'){
                          Serial.println("Hay encendido");
                          flag_bomba=true;
                          break;
                        }
                      }
                    }
                    if(cadena[i]=='l'){
                      if(cadena[i+1]=='n'){
                        if(cadena[i+2]=='o'){
                          Serial.println("Hay apagado");
                          flag_bomba=false;
                          break;
                        }
                      }
                    }
                    else {
                      flag_bomba=false;
                    }
                    
                  }
                  
                  //finalizamos si la respuesta es mayor a 500 caracteres
                  if(cadena.length()>50000) //Pueden aumentar si tenen suficiente espacio en la memoria
                  {
                    Serial.println("La respuesta a excedido el tamaño maximo");
                    
                    SerialESP8266.println("AT+CIPCLOSE");
                    if( SerialESP8266.find("OK"))
                      Serial.println("Conexion finalizada");
                    fin_respuesta=true;
                  }
                  if((millis()-tiempo_inicio)>10000) //Finalizamos si ya han transcurrido 10 seg
                  {
                    Serial.println("Tiempo de espera agotado");
                    SerialESP8266.println("AT+CIPCLOSE");
                    if( SerialESP8266.find("OK"))
                      Serial.println("Conexion finalizada");
                    fin_respuesta=true;
                  }
                  if(cadena.indexOf("CLOSED")>0) //si recibimos un CLOSED significa que ha finalizado la respuesta
                  {
                    Serial.println();
                    Serial.println("Cadena recibida correctamente, conexion finalizada");         
                    fin_respuesta=true;
                  }
              }
    
              
            }
            else
            {
              Serial.println("No se ha podido enviar HTTP.....");
           }            
          }
      }
      else
      {
        Serial.println("No se ha podido conectarse con el servidor");
      }

  //-------------

  int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
  Serial.print("Humedad: ");
  Serial.print(valorHumedad);
  Serial.println("%");

  if(flag_bomba){
    digitalWrite(pin_bomba,HIGH);
  }
  else{
    digitalWrite(pin_bomba,LOW);
  }

   
    
   if(flag_servo){
       for (int i = 149; i > 50; i--)
      {
        // Desplazamos al ángulo correspondiente
        servoMotor.write(i);
        // Hacemos una pausa de 25ms
        delay(50);
      
      }
  }
  else{


      for (int i = 50; i <= 150; i++)
      {
        // Desplazamos al ángulo correspondiente
        servoMotor.write(i);
        // Hacemos una pausa de 25ms
        delay(50);
      }
  }
  
  //-------------------------------------------------------------------------------
  
  delay(10000); //pausa de 10seg antes de conectarse nuevamente al servidor (opcional)

 

}
