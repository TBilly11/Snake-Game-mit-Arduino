//------------EingebundeneBibliotheken--------------------//
 #include <EEPROM.h>
 #include <LedControl.h>
 //-----------------------------------------------------------//
 //------------GlobaleVariablendefinieren-------------------//
 //-----------------------------------------------------------//
 //---------wirdzurAnsteuerungderMatrixbenötigt-----------//
 constintDIN=12;
 constintCS=10;
 constintCLK=11;
 constintnum=2;
 //ErzeugungeinesDisplay-Objekts
 LedControl lc=LedControl(DIN,CLK,CS,num);
 //---------VariablenfürdieSchlange---------------------//
 structlocation{
 intDisplay[128]={0};
 intx[128]={0};
 inty[128]={0};
 };
 structlocationsnake;
 intsnake_length=0;
 intgeschwindigkeit=0;
 
 //RichtungsvariablenzumsteuernderSchlange//
 intsnake_direction=0;
 intlast_snake_direction=0;
 constintup=1;
 constintright=2;
 constintleft=3;
 constintdown=4;
 
 //-------------VariablendasEssen--------------------//
 structPosition{
 intDisplay=0;
 intx =0;
 inty =0;
 };
 
struct Position food;
 
 // Variable zum Toggeln des Essens
 bool food_status = 0;
 
 //----------- Variablen zum Steuern der Schlange-------//
 int joystick_x; // x-Koordinate des Joysticks
 int joystick_y; // y-Koordinate des Joysticks
 
 //----- Zeitvariable für die "Delay" Funktion----------//
 unsigned long delay_time = 0;

 //------- Variable für die Spielzustände---------------//
 int game_status = 0;
 //------- Variablen für das Spielende------------------//
 int score = 0;
 int highscore = 0;
 
 //-------- Variablen für die Ausgabe des Punktestandes-----//
 int safe_score = 0;
 int digit_count = 0;
 int digit_0 = 0;
 int digit_1 = 0;
 const bool all_digits[11][8][8] = {
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’0’
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 1, 1, 1, 0},
 {0, 1, 1, 1, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’1’
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 0, 1, 1, 1, 0, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 1, 1, 1, 1, 1, 1, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’2’
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 1, 1, 0, 0},
 {0, 0, 1, 1, 0, 0, 0, 0},
 {0, 1, 1, 0, 0, 0, 0, 0},
 {0, 1, 1, 1, 1, 1, 1, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’3’
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 0, 0, 1, 1, 1, 0, 0},
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’4’
 {0, 0, 0, 0, 1, 1, 0, 0},
 {0, 0, 0, 1, 1, 1, 0, 0},
 {0, 0, 1, 0, 1, 1, 0, 0},
 {0, 1, 0, 0, 1, 1, 0, 0},
 {0, 1, 1, 1, 1, 1, 1, 0},
 {0, 0, 0, 0, 1, 1, 0, 0},
 {0, 0, 0, 0, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’5’
 {0, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 0, 0, 0, 0, 0},
 {0, 1, 1, 1, 1, 1, 0, 0},
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’6’
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 0, 0, 0},
 {0, 1, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’7’
 {0, 1, 1, 1, 1, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 1, 1, 0, 0},
 {0, 0, 0, 0, 1, 1, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0},
 {0, 0, 0, 1, 1, 0, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’8’
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’9’
 {0, 0, 1, 1, 1, 1, 0, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 1, 0},
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 1, 1, 0, 0, 1, 1, 0},
 {0, 0, 1, 1, 1, 1, 0, 0}
 },
 {
 {0, 0, 0, 0, 0, 0, 0, 0}, // ’/’
 {0, 0, 0, 0, 0, 1, 1, 0},
 {0, 0, 0, 0, 1, 1, 1, 0},
 {0, 0, 0, 1, 1, 1, 0, 0},
 {0, 0, 1, 1, 1, 0, 0, 0},
 {0, 1, 1, 1, 0, 0, 0, 0},
 {0, 1, 1, 0, 0, 0, 0, 0},
 {0, 0, 0, 0, 0, 0, 0, 0}
 }
 };
 
 //--------------------------------------------------------//
 //----------------------- Funktionen---------------------//
 //--------------------------------------------------------//
 
 //------- gibt die Schlange auf der Matrix aus--------//
 // siehe Abschnitt 3.2.1 der Dokumentation
 void print_snake(){
 // Schlange ausgeben
 
 for (int i = 0; i < snake_length; i++){
 lc.setLed(snake.Display[i], snake.y[i], snake.x[i], true);
 
 }
}
 
 //------- gibt das Essen auf der Matrix aus------//
 // siehe Abschnitt 3.2.2 der Dokumentation
 void print_food(){
 
 food_status = !food_status;
 lc.setLed(food.Display, food.y, food.x, food_status);
 }
 
 //------ bestimmt die Koordinaten des Essens------//
 // siehe Abschnitt 3.5.2 der Dokumentation
 void set_food(){
 bool check = false;
 while (check == false){
 // neue Koordinaten des Essens werden zufällig gewählt
 food.Display = random(0, 2);
 food.x = random(0, 8);
 food.y = random(0, 8);
 for (int i = 0; i < snake_length; i++){
  
 // Das Essen darf nicht die gleiche Position wie ein Element derSchlange haben
 
  if ((food.x == snake.x[i]) && (food.y == snake.y[i]) && (food.
   Display == snake.Display[i])){
   check = false;
 break;
 }
  else{
 check = true;
    }
   } 
  }
 }
 
 //----- legt die neuen Koordinaten der Schlange fest-----//
 // siehe Abschnitt 3.3 der Dokumentation
 void snake_movement(){

 // Verriegelung der Bewegungsrichtungen
 // siehe Abschnitt 3.3.6 der Dokumentation
 int sum_direction = last_snake_direction + snake_direction;
 if (sum_direction == 5){
 snake_direction = last_snake_direction;
 }
 
 // Festlegung der Koordinaten der Schlange bis auf den Schlangenkopf
 for (int i = snake_length- 1; i > 0; i--){
 snake.Display[i] = snake.Display[i- 1];
 snake.x[i] = snake.x[i- 1];
 snake.y[i] = snake.y[i- 1];
 }
 // Abfrage der Bewegungsrichtung
 switch (snake_direction){
 //Bewegung nach oben (Abschnitt 3.3.1)
 case up:
 snake.y[0]-= 1;
 if (snake.y[0] ==-1 && snake.Display[0] == 0){
 snake.y[0] = 7;
 snake.Display[0] = 1; // Wechsel des Displays
 }
 if (snake.y[0] ==-1 && snake.Display[0] == 1){
   snake.y[0] = 7;
   snake.Display[0] = 0; // Wechsel des Displays
 }
 break;
 //Bewegung nach unten (Abschnitt 3.3.2)
 case down:
 snake.y[0] += 1;
 if (snake.y[0] == 8 && snake.Display[0] == 0){
 snake.y[0] = 0;
 snake.Display[0] = 1; // Wechsel des Displays
 }
 if (snake.y[0] == 8 && snake.Display[0] == 1){
 snake.y[0] = 0;
 snake.Display[0] = 0; // Wechsel des Displays
 }
 break;
 //Bewegung nach links (Abschnitt 3.3.3)
 case left:
 snake.x[0]-= 1;
 if (snake.x[0] ==-1){
 snake.x[0] = 7;
 }
 break;
 //Bewegung nach rechts (Abschnitt 3.3.4)
 case right:
 snake.x[0] += 1;
 if (snake.x[0] == 8){
 snake.x[0] = 0;
 }
 break;
 }
 // Zwischenspeicherung der aktuellen Richtung
 last_snake_direction = snake_direction;
 }
 //----- Steuerung der Schlange via Joystick-----//
 // siehe Abschnitt 3.4 der Dokumentation

 void control_snake(){
 joystick_x = analogRead(A0);  // Auslesen des Wertes der x-Achse
 joystick_y = analogRead(A1);   // Auslesen des Wertes der y-Achse 
 
 // Neutrale Posotion des Sticks x = 508 & y = 510
 if (joystick_x < 300){
 snake_direction = up;
 }
 else if (joystick_x > 700){
 snake_direction = down;
 }
 else if (joystick_y < 300){
 snake_direction = right;
 }
 else if (joystick_y > 700){
 snake_direction = left;
 }
 delay(10);
 }

 
 //----- Erkennt ob das Essen gegessen wurde-----//
 // siehe Abschnitt 3.5 der Dokumentation
 void food_eaten(){
 
 // Wenn der Kopf der Schlange sich auf dem Essen befindet, ist
 Bedingung erfüllt
 if(snake.x[0] == food.x && snake.y[0] == food.y && snake.Display[0] == food.Display){

 // Vergrößerung der Schlange (Abschnitt 3.5.1)
 snake.Display[snake_length] = snake.Display[snake_length-1];
 snake.x[snake_length] = snake.x[snake_length- 1];
 snake.y[snake_length] = snake.y[snake_length- 1];
 snake_length ++;
 // Neusetzung des Essens (Abschnitt 3.5.2)
 set_food();
 
 // Erhöhung der Geschwindigkeit (Abschnitt 3.5.3)
 if (geschwindigkeit > 100){
 geschwindigkeit-= 10;
   }
  }
 }
 //----- Erkennt ob das Spiel zu Ende ist------//
 // siehe Abschnitt 3.6 der Dokumentation
 void game_over(){
 
 if (snake_length > 2){
 for (int i = 1; i < snake_length; i++){
 if (snake.x[0] == snake.x[i] && snake.y[0] == snake.y[i] && snake.Display[0] == snake.Display[i]){
 game_status = 2;
   }
  }
 }
 }
 
 
 //---- wird beim Starten des Spiels aufgerufen-----//
 // siehe Abschnitt 3.7 der Dokumentation
 void start_game(){
 
 Serial.println("Zum Spielstart bewege den Joystick nach oben!");
 
 // Es wird solange gewartet bis der Joystick nach oben gedrückt wurde
 while (snake_direction != up){
 control_snake();
 }
 // kurze Verzögerung, damit beim Spielstart der Joystick nicht mehr nach oben gedrückt ist
 delay(1000);
 if (snake_direction == up) {
 // zufälligen Seed erzeugen. Wird für die zufällige Generierung von
 Zahlen benötigt
 randomSeed(micros());
 clear_displays();
 Serial.println("Spiel wurde gestartet.");
 game_status = 1;
 snake_direction = 0;  // Schlange bewegt sich nicht
 
 snake_length = 1;     // Startlänge festlegen
 geschwindigkeit = 300; // und Startgeschwindigkeit

 // Startpunkt der Schlange zufällig festlegen (Abschnitt 3.2.1)
 snake.Display[0] = random(0, 2);
 snake.x[0] = random(0, 8);
 snake.y[0] = random(0, 8);
 
 // Startwert für das Essen wird zufällig festgelegt (Abschnitt 3.2.2)
 set_food();
  }
 }
 
 //----- wird beim Ende des Spiels aufgerufen------//
 // siehe Abschnitt 3.7 der Dokumentation
 void game_finish(){
 clear_displays(); 
 
 // Punktestand ermitteln
 score = snake_length- 1;
 Serial.print("\n");
 Serial.println("GAME OVER ");
 Serial.print("Ihr Score ist: ");
 Serial.println(score,DEC);
 
 // siehe Abschnitt 3.6.1
 print_digits(score);
 
 // aktueller Highscore aus EEPROM lesen
 highscore = EEPROM.read (0);
 
 if(score > highscore){
 highscore = score;
 Serial.println("Glückwunsch Sie haben einen neuen Highscore!");
 Serial.println("\n");

 // Highscore an die Stelle 0 im EEPROM speichern
 EEPROM.update (0, highscore);
 }
 else{
 Serial.print("Aktueller Highscore: ");
 Serial.println(highscore);
 Serial.println("\n");
 }
 // Variable auf 0 setzten, damit man wieder zum Spielanfang gelangt
 game_status = 0;
 // Richtung der Schlange auf 0 setzen (keine Bewegung)
 snake_direction = 0;
 }
 
 //----- zeigt den Score auf dem Display an-----//
 // siehe Abschnitt 3.6.1 der Dokumentation
 void print_digits(int score){
 
 digit_count = 0;
 digit_0 = 0;
 digit_1 = 0;
 safe_score = score;
 
 // Ziffernanzahl ermitteln
 while (safe_score > 0){
  safe_score /= 10;
  digit_count ++;
 }
 // Abspeichern der Ziffern
 if (digit_count > 2){
 digit_0 = 10;
 digit_1 = 10;
 }
 else {
 digit_0 = score / 10; // Ermittlung der ersten Ziffer
 digit_1 = score % 10; // Ermittlung der zweiten Ziffer
 }
 for (int i = 0; i < 8; i++){
   for (int j = 0; j < 8; j++){
     // Ausgabe der ersten Ziffer auf der Matrix mit der Nummer 0
     lc.setLed(0, i, j, all_digits[digit_0][i][j]);
     // Ausgabe der zweiten Ziffer auf der Matrix mit der Nummer 1
    lc.setLed(1, i, j, all_digits[digit_1][i][j]);
    }
   }
  }

//--- schaltet alle LEDs der Displays aus----//
 void clear_displays(){
 lc.clearDisplay(0);
 lc.clearDisplay(1);
 }
 
 // siehe Abschnitt 3.7 der Dokumentation
 void setup() {
   // Weckt das Display aus dem Energiespar-Modus
   lc.shutdown(0, false);
   lc.shutdown(1, false);
 
   // Helligkeit der LEDs festlegen
   lc.setIntensity(0, 7);
   lc.setIntensity(1, 7);
   
   // alle LEDs auf den Displays ausschalten
   clear_displays();
   // Für die Serielle Schnittstelle benötigt
   Serial.begin(9600);
   Serial.setTimeout (-1);
  // Analogpins A0 und A1 für den Joystick als Input festlegen
   pinMode(A0, INPUT);
   pinMode(A1, INPUT);

 }
 // siehe Abschnitt 3.7 der Dokumentation
 void loop() {
 
 if (game_status == 0){
 start_game();
 }
 
 if (game_status == 1){
  
 // gibt die Geschwindigkeit vor
 if (millis()- delay_time > geschwindigkeit){
 snake_movement();
 clear_displays();
 print_snake();
 food_eaten();
 print_food();
 game_over();
 delay_time = millis();
 }
 control_snake();
 }
 if (game_status == 2){
 game_finish();
 }
}
