void abrir_techo(){

  // Vamos a tener dos bucles uno para mover en sentido positivo y otro en sentido negativo
  // Para el sentido positivo
  for (int i = 50; i <= 150; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    // Hacemos una pausa de 25ms
    delay(50);
  }
}

void cerrar_techo(){
  // Para el sentido negativo
  for (int i = 149; i > 50; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    // Hacemos una pausa de 25ms
    delay(50);
  
  }
}




void medirHumedad(){
  //Se hace la lectura analoga del pin A0 (sensor) y se pasa por la funcion
  //map() para ajustar los valores leidos a los porcentajes que queremos utilizar   
  int valorHumedad = map(analogRead(sensor), 0, 1023, 100, 0);
  Serial.print("Humedad: ");
  Serial.print(valorHumedad);
  Serial.println("%");
}
